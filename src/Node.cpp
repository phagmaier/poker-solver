#include "Node.h"

float Node::blind = 1.0;
//check, 10%, 25% 50%, 75%, 85%, 100%, 150% 200% all in
std::vector<float> Node::default_bet_sizes = 
              {.25, .5,.75,.85,1,1.5,2};

std::vector<Card> Node::hand = {};

Node::Node(bool p1, Street street, float prev_bet, float potsize, 
           std::pair<float,float> stacks,
        Action prev_act, int num_bets, Node *parent) : 
        potsize{potsize}, parent{parent}{
    
    std::vector<std::pair<float, Action>> bets;
    stack = p1 ? stacks.first : stacks.second;
    if (prev_act == ALLIN){
      if (prev_bet >= stack){
        bets.push_back({stack, ALLIN});
      }
      else{
        bets.push_back({prev_bet, ALLIN});
      }
    }
    
    if (prev_act == ALLIN || prev_act == BET){
      bets.push_back({0, FOLD});  
    }
    else{
      bets.push_back({0, CHECK});
    }
    
    if (num_bets < 3){
      for (int i : default_bet_sizes){
          float temp = i * potsize < stack;
        if (temp < stack && temp >= 2 * prev_bet && temp >=blind){
          bets.push_back({temp, BET});
        }
      }
    } 
    if (prev_act != ALLIN){
      bets.push_back({stack, ALLIN});
    }
    if (prev_bet < stack && prev_act == BET){
      bets.push_back({prev_bet, CALL});
    }
    
    for (std::pair<float, Action> const &i : bets){
      float bet = i.first;
      Action action = i.second;
      Street next = get_next_street(prev_act, action,street);
      if (next != DONE){
        bool player = p1 ? false : true;
        //std::pair<float,float> myStack = p1 ? {stack, stacks.second} : {stacks.first, stack};
        std::pair<float,float> myStack;
        if (p1){
          myStack = {stack-bet, stacks.second};
        }
        else{
        myStack = {stacks.first, stack-bet};
        }
        num_bets = action == BET ? num_bets +1 : 0;
        children.push_back(Node(player,next,bet, potsize+bet,
                                myStack,action, num_bets, this));
      }
    }
  
}

Node::Street operator+(Node::Street s, int) {
    switch (s) {
    case Node::FLOP:
            return Node::TURN;
    case Node::TURN:
            return Node::RIVER;
    case Node::RIVER:
            return Node::DONE;
        default:
            return s; // This case is to handle DONE or any invalid input
    }
}


Node::Street Node::get_next_street(Action prev, Action curr, 
                             Street street){
    if ((street == RIVER && curr == prev) || curr == FOLD || 
        (curr==ALLIN && prev == ALLIN)){
      return DONE;
    }
    else if (curr == CALL || curr == prev){
        return street + 1;
      }
      return street;
}

Node::Node(){
  children = {};
  potsize = 0;
  stack = 0;
  prev_act = CHECK;
  strat = {};
  ev =  {};
  parent = NULL;

}
