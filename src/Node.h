//by the way have to make it so the solve 
//stack sizes must always be greater than or equal to 1
#ifndef NODE_H
#define NODE_H 

#include <vector>
#include <string>
#include <map>
#include "Card.h"
#include <stdexcept>

enum Street{
  DONE = -1,
  FLOP,
  TURN,
  RIVER
};

enum Action{
  FOLD,
  CHECK,
  CALL,
  BET,
  ALLIN
};

Street& operator++(Street& s);
  

class Node{
  public:
    static std::map<Street, std::string> street_dic;
    static std::map<Action, std::string> action_dic;
    //for when head makes node 
    // won't know the number of children
    Node();
    Node(bool p1, Street street, Action action, std::vector<Node*> children,
         std::map<std::pair<Card*, Card*>,float> strats, 
         float potsize, float bet, float stack,int num_bets);

    inline void set_children(std::vector<Node*> childs){children = childs;}
    
    bool p1;
    Street street;
    Action action;
    float potsize;
    float bet;
    float stack;
    
    //arr of arr of nodes representing children 
    // need 2d becuase need it for Nodes that come 
    // after for each card need to be pointer 
    // cause AD will need child node for AC and so will 
    // other cards in range 
    std::vector<Node*> children;

    std::map<std::pair<Card*, Card*>,float> strats;
    std::map<std::pair<Card*, Card*>,float> strat_sum;
};

#endif
