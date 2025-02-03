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

void Node::make_children(){
  //Node *next_parent = this;
  bool next_player = get_next_player();
  Node *child_node = nullptr;

  //probably won't need this will handle
  //in the get valid bet sizes
  if (action==ALLIN){
    //this is wrong need to do all in update
    child_node = new Node(this, FOLD, next_player,street,
                          min_stack,potsize,0,0);
    children.push_back(child_node);
    child_node = new Node(this,CALLALLIN,next_player,street,
                          0,potsize+min_stack,min_stack,0);
    return;
  }
  std::vector<float> sizes = get_valid_bet_sizes();
  Action next_act = BET;
  if (action == BET || action == RAISE){
    next_act = RAISE;
  }
  for (float &i :sizes){

    //std::tie(next_act,next_bet) = i;
    Street next_street = get_next_street();
    float new_short = short_stack == next_player ? min_stack-i: min_stack;
    child_node = new Node(this, next_act, next_player,next_street,
                          new_short, potsize+i, i, num_bets+1);
    children.push_back(child_node);
  }

  //can always fold,check, or checkback
  //can also always go all in 
  if (action == BET || action == RAISE){
    //if the new player is the same as the min stack then decrease min stack
    int new_min_stack = (!player) == Node::min_stack ? min_stack - cur_bet : min_stack;
    child_node = new Node(this, CALL, !player,street,new_min_stack,potsize+cur_bet,0,0);

    children.push_back(child_node);
    child_node = new Node(this, FOLD, !player,street,
                          min_stack,potsize,0,0);
  }
  else{
    Action tmp = action == CHECK ? CHECKBACK : CHECK;
    child_node = new Node(this, tmp , !player,street,
                          min_stack,potsize,0,0);
  }
  children.push_back(child_node);
  child_node = new Node(this,ALLIN,!player,street,
                          min_stack,potsize+min_stack,min_stack,0);
  children.push_back(child_node);

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

bool Node::get_next_player(){
  if (action == CALL && player == false){
    return player;
  }
  return (!player);
}



std::vector<float> Node::get_valid_bet_sizes(){
  if (num_bets >= 3){
    return {};
  }
  std::vector<float> vec;
  float min_bet = num_bets ? (cur_bet *2) : Node::bb;
  float limit = min_stack *.85; //if 85% of stack just go all in so not valdid
  for (float i : Node::bet_sizes){
    float size = i * potsize; 

    if (size >= min_bet && size <limit){
      vec.push_back(size);
    }
  }
  return vec;
}

Node::~Node(){
  for (Node *node: children){
    if (node){
      delete node;
    }
  }
}
