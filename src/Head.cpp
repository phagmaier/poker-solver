#include "Head.h"

Head::Head(bool p1, Node::Street street, float prev_bet, float potsize, 
        std::pair<float,float> stacks, Node::Action prev_act, int num_bets, float blind, 
           std::pair<float,float> player_bets){

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
      std::pair<float,float> new_bets;
      if (p1){
        new_bets.first = player_bets.first + bet;
        new_bets.second = player_bets.second;
      }
      else{
        new_bets.second = player_bets.second + bet;
        new_bets.second = player_bets.first;

      }
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
        

        /* PROPER NODE CONSTRUCTOR
        *bool p1, Street street, float prev_bet, float potsize, 
        std::pair<float,float> stacks,
        Action prev_act, int num_bets,Node *parent, float strat
        */
        nodes.push_back(Node(player,next,bet, potsize+bet,
                                myStack,action, num_bets, NULL, 0, new_bets));
      }
    }
    float strat = (float)1/nodes.size();
    for (Node &i :nodes){
      i.set_strat(strat);
    }
}



Node::Street Head::get_next_street(Node::Action prev, Node::Action curr, 
                             Node::Street street){
    if ((street == Node::RIVER && curr == prev) || curr == Node::FOLD || 
        (curr==Node::ALLIN && prev == Node::ALLIN)){
      return Node::DONE;
    }
    else if (curr == Node::CALL || curr == prev){
        return street + 1;
      }
      return street;
}
