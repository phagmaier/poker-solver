#include "Node.h"

const std::vector<float> Node::bet_sizes = {.25,.5,.75,1,1.25,2};
//should probably have reraise sizes
const std::vector<float> Node::reRaiseSizes = {2,3,4,5};
const float Node::bb = 1;
const float Node::starting_stack1 = 100;
const float Node::starting_stack2 = 100;
const bool Node::short_stack = Node::starting_stack1 > Node::starting_stack2 ? false : true; 
unsigned int Node::a = 1;

//SETTING THE RANGES JUST FOR THIS EXAMPLE WE 
//WILL ONLY BE PLAYING ACES AND KINGS
const std::vector<std::pair<Card,Card>> Node::range1 = {
  {Card(12,0),Card(12,1)},{Card(11,0), Card(11,1)}
};

const std::vector<std::pair<Card,Card>> Node::range2 = {
  {Card(12,0),Card(12,1)},{Card(11,0), Card(11,1)}
};
std::unordered_map<Action, std::string> Node::action_dic{
  {FOLD,"FOLD"},
  {CHECK,"CHECK"},
  {CHECKBACK,"CHECK BACK"},
  {CALL, "CALL"},
  {CALLALLIN,"CALL ALL IN"},
  {BET,"BET"},
  {RAISE,"RAISE"},
  {ALLIN,"ALL IN"}
};
std::unordered_map<Street, std::string> Node::street_dic{
  //{PREFLOP,"PREFLOP"},//MAYBE LATER ADD PREFLOP
  {FLOP,"FLOP"},
  {TURN,"TURN"},
  {RIVER,"RIVER"}
};

Node::Node(Node *parent, Action action, bool player, Street street,
           float min_stack, float potsize, float cur_bet, int num_bets) :
parent(parent), action(action), player(player), street(street),
min_stack(min_stack), potsize(potsize), cur_bet(cur_bet), num_bets(num_bets)
{
  //std::cout << Node::a << "\n";
  Node::a++;
  if (!is_terminal_node()){
    make_children();
  }
  float uniform = 1.0f/(float)children.size();
  int num_cards = player ? Node::range1.size() : Node::range2.size();
  for (int i=0;i<num_cards;++i){
    total_ev.push_back(0.0f);
    total_av.push_back(0.0f);
    total_regrets.push_back(0.0f);
    for (int x=0;x<children.size();++x){
      children[x]->action_prcts.push_back(uniform);
    }
  }
}

//In the future please chnage this so it's not just a bunch of if statments it's 
//really shitty code 
void Node::make_children(){
  std::vector<float> sizes = get_valid_bet_sizes();
  
  //NOW I NEED TO MAKE ALL THE NON BETS
  //1. CALL
  //2. CHECK
  //3. CHECKBACK
  //4. CALLALLIN
  //5. ALLIN
  //6. FOLD
  
  if(action == BET || action ==RAISE){
    children.emplace_back(new Node(this,CALL,!player,
                          street,min_stack-cur_bet,
                          potsize+(cur_bet *2),0,0));
    children.emplace_back(new Node(this,FOLD,!player,
                          street,min_stack,
                          potsize,0,0));
    children.emplace_back(new Node(this,ALLIN,!player,
                          street,min_stack,
                          potsize,min_stack,0));
    for(float bet : sizes){
      children.emplace_back(new Node(this,RAISE,!player,street,min_stack,
                                potsize,bet,num_bets+1));
    }
  }
  else if(action == CHECK){
    children.emplace_back(new Node(this,CHECKBACK,!player,
                          street,min_stack,
                          potsize,0,0));
    children.emplace_back(new Node(this,ALLIN,!player,
                          street,min_stack,
                          potsize,min_stack,0));
    for(float bet : sizes){
      children.emplace_back(new Node(this,BET,!player,street,min_stack,
                                potsize,bet,1));
    }
  }

  else if(action == CHECKBACK){
    bool newP = !player ? player : !player;
    Street new_street = get_next_street();
    children.emplace_back(new Node(this,CHECK,newP,
                          new_street,min_stack,
                          potsize,0,0));
    children.emplace_back(new Node(this,ALLIN,newP,
                          new_street,min_stack,
                          potsize,min_stack,0));
    for(float bet : sizes){
      children.emplace_back(new Node(this,BET,newP,new_street,min_stack,
                                potsize,bet,1));
    }

  }
  else if(action ==CALL){
    bool newP = !player ? player : !player;
    Street new_street = get_next_street();
    children.emplace_back(new Node(this,CHECK,newP,
                          new_street,min_stack-cur_bet,
                          potsize + (cur_bet * 2),0,0));
    children.emplace_back(new Node(this,ALLIN,newP,
                          new_street,min_stack - cur_bet,
                          potsize+(cur_bet*2),min_stack-cur_bet,0));
    for(float bet : sizes){
      children.emplace_back(new Node(this,BET,newP,new_street,min_stack-cur_bet,
                                potsize+(cur_bet*2),bet,1));
    }
  }
  else if(action == ALLIN){
     children.emplace_back(new Node(this,FOLD,!player,
                          street,min_stack,
                          potsize,0,0));
    children.emplace_back(new Node(this,CALLALLIN,!player,
                          street,0,
                          potsize+(min_stack * 2),min_stack,0));
  }
  else{
    std::cout << "PRINTING IN MAKE CHILDREN\n";
    std::cout << "IF THIS IS PRINTING IDK WHY PROBABLY AN ERROR\n";
    std::cout << "IT'S PART WHERE I DO THE NON BETS CHECK LOGIC\n";
  }
}

Street Node::get_next_street(){
  if (action == CHECKBACK || action == CALL){
    //Street new_street;
    switch(street) {
      /*
      //REMOVING PREFLOP FOR NOW
      case PREFLOP:
        new_street = FLOP;
        break;
      */
      case FLOP:
        return TURN;
        break;
      case TURN:
        return RIVER;
        break;
      default:
        std::cerr << "THIS SHOULD NEVER PRINT PASSED A RIVER STREET\n"; 
    }
  }
  return street;
}

bool Node::is_terminal_node(){
  if (action == FOLD || action == CALLALLIN){
    return true;
  }
  if (street == RIVER && (action == CHECKBACK || action == CALL)){
    return true;
  }
  return false;
}

std::vector<float> Node::get_valid_bet_sizes(){
  if (num_bets >= 3 || action == ALLIN){
    return {};
  }
  std::vector<float> vec;
  float limit = min_stack *.85; //if 85% of stack just go all in so not valdid
  if (action != BET && action != RAISE){
    float pot = potsize ? potsize : Node::bb;
    for (const float i : Node::bet_sizes){
      float size = i * pot; 
      if (size >= Node::bb && size<limit){
        vec.push_back(size);
      }
    }
  }

  else{
    for (const float i : Node::reRaiseSizes){
      float size = i * cur_bet; 
      if (size < limit){
        vec.push_back(size);
      }
    }
  }
  return vec;
}

void Node::print_node(){
  std::cout << "STREET: " << Node::street_dic[street];
  std::cout << " ACTION: "<< Node::action_dic[action] << " ";
  std::cout << "BET SIZE: " << cur_bet << "\n";
}

Node::~Node(){
  //std::cout << "CALLING DESTRUCTOR\n";
  for (Node *node: children){
    if (node){
      delete node;
    }
  }
}


