#include "Node.h"

const std::vector<float> Node::bet_sizes = {.25,.5, .75,1,1.25,2};
float Node::bb = 1;
float Node::starting_stack1 = 100;
float Node::starting_stack2 = 100;
bool Node::short_stack = Node::starting_stack1 > Node::starting_stack2 ? false : true; 

Node::Node(Node *parent, Action action, bool player, Street street,
           float min_stack, float potsize, float cur_bet, int num_bets) :
parent(parent), action(action), player(player), street(street),
min_stack(min_stack), potsize(potsize), cur_bet(cur_bet), num_bets(num_bets)
{
  if (!is_terminal_node()){
    make_children();
  }
}

//ONLY ADJUST THE MIN STACK AND POT ON CALLS
void Node::make_children(){
  std::vector<float> sizes = get_valid_bet_sizes();
  //are you raising or are you calling
  Action act = RAISE;
  if (action == CHECK || CALL || CHECKBACK){
    act = BET;
  }
  //setting all bets
  for(float bet : sizes){
    children.emplace_back(new Node(this,act,!player,street,min_stack,
                                potsize,bet,num_bets+1));
  }
  //NOW I NEED TO MAKE ALL THE NON BETS
  //1. CALL
  //2. CHECK
  //3. CHECKBACK
  //4. CALLALLIN
  //5. ALLIN
  //6. FOLD
  
  //CALL
  if(action == BET){
    //if you call as first to act player you go again next street
    bool new_player = !player ? player : !player;
    children.emplace_back(new Node(this,act,new_player,
                          street,min_stack-cur_bet,
                          potsize+(cur_bet *2),0,0));
    children.emplace_back(new Node(this,FOLD,!player,
                          street,min_stack,
                          potsize,0,0));
    children.emplace_back(new Node(this,ALLIN,!player,
                          street,min_stack,
                          potsize,min_stack,0));
  }
  else if()
}

Street Node::get_next_street(){
  if (action == CHECKBACK || action == CALL){
    Street new_street;
    switch(street) {
      case PREFLOP:
        new_street = FLOP;
        break;
      case FLOP:
        new_street = TURN;
        break;
      case TURN:
        new_street = RIVER;
        break;
   
      default:
        std::cerr << "THIS SHOULD NEVER PRINT PASSED A RIVER STREET\n"; 
    }
    return new_street;
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

/*
bool Node::get_next_player(){
  if (action == CALL && player == false){
    return player;
  }
  return (!player);
}
*/


//Need to fix this if potsize is 0 need the potsize to be the Node::bb
std::vector<float> Node::get_valid_bet_sizes(){
  if (num_bets >= 3){
    return {};
  }
  std::vector<float> vec;
  float min_bet = num_bets ? (cur_bet *2) : Node::bb;
  float pot = potsize ? potsize : Node::bb;
  float limit = min_stack *.85; //if 85% of stack just go all in so not valdid
  for (float i : Node::bet_sizes){
    float size = i * potsize; 

    if (size >= min_bet){
      if (size >= limit){
        return vec;
      }
      vec.push_back(size);
    }
  }
  return vec;
}

Node::~Node(){
  std::cout << "CALLING DESTRUCTOR\n";
  for (Node *node: children){
    if (node){
      delete node;
    }
  }
}
