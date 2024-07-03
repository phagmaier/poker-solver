#include "Head.h"

Head::Head(bool p1, Node::Street street, float prev_bet, float potsize, 
        std::pair<float,float> stacks, Node::Action prev_act, int num_bets, float blind){

    
std::vector<std::pair<float, Node::Action>> bets;
    float stack = p1 ? stacks.first : stacks.second;
    if (prev_act == Node::ALLIN){
      if (prev_bet >= stack){
        bets.push_back({stack, Node::ALLIN});
      }
      else{
        bets.push_back({prev_bet, Node::ALLIN});
      }
    }
    
    if (prev_act == Node::ALLIN || prev_act == Node::BET){
      bets.push_back({0, Node::FOLD});  
    }
    else{
      bets.push_back({0, Node::CHECK});
    }
    
    if (num_bets < 3){
      for (int i : Node::default_bet_sizes){
          float temp = i * potsize < stack;
        if (temp < stack && temp >= 2 * prev_bet && temp >=blind){
          bets.push_back({temp, Node::BET});
        }
      }
    } 
    if (prev_act != Node::ALLIN){
      bets.push_back({stack, Node::ALLIN});
    }
    if (prev_bet < stack && prev_act == Node::BET){
      bets.push_back({prev_bet, Node::CALL});
    }
    
    for (std::pair<float, Node::Action> const &i : bets){
      float bet = i.first;
      Node::Action action = i.second;
      Node::Street next = get_next_street(prev_act, action,street);
      if (next != Node::DONE){
        bool player = p1 ? false : true;
        //std::pair<float,float> myStack = p1 ? {stack, stacks.second} : {stacks.first, stack};
        std::pair<float,float> myStack;
        if (p1){
          myStack = {stack-bet, stacks.second};
        }
        else{
        myStack = {stacks.first, stack-bet};
        }
        num_bets = action == Node::BET ? num_bets +1 : 0;
        nodes.push_back(Node(player,next,bet, potsize+bet,
                                myStack,action, num_bets, NULL));
      }
    }
    float strat = (float)1/nodes.size();
    for (Node &i :nodes){
      i.set_strat(strat);
    }
}



Node::Street Node::get_next_street(Action prev, Action curr, 
                             Node::Street street){
    if ((street == RIVER && curr == prev) || curr == FOLD || 
        (curr==ALLIN && prev == ALLIN)){
      return DONE;
    }
    else if (curr == CALL || curr == prev){
        return street + 1;
      }
      return street;
}
