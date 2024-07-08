#ifndef NODE_H
#define NODE_H 

#include <vector>
#include <string>
#include <map>
#include "Card.h"

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

  

class Node{
  public:
    static std::map<Street, std::string> street_dic;
    static std::map<Action, std::string> action_dic;
    //for when head makes node 
    // won't know the number of children
    Node();
    Node(bool p1, Street street, Action action, std::map<std::pair<Card*, Card*>,Node*> children,
         std::map<std::pair<Card*, Card*>,Node*> strats, std::map<std::pair<Card*, Card*>,Node*> strat_sum);
    inline void set_children(std::map<std::pair<Card*, Card*>,Node*> childs){children = childs;}
    
    bool p1;
    Street street;
    Action action;
    
    //arr of arr of nodes representing children 
    // need 2d becuase need it for Nodes that come 
    // after for each card need to be pointer 
    // cause AD will need child node for AC and so will 
    // other cards in range 
    std::map<std::pair<Card*, Card*>,Node*> children;

    std::map<std::pair<Card*, Card*>,Node*> strats;
    std::map<std::pair<Card*, Card*>,Node*> strat_sum;
};

#endif
