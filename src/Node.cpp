#include "Node.h"


std::map<Street, std::string> Node::street_dic = {
  {DONE, "DONE DON'T THINK THIS SHOULD EVER PRINT"},
  {FLOP, "FLOP"}, {TURN, "TURN"}, {RIVER, "RIVER"}
};

std::map<Action, std::string> Node::action_dic = {
  {FOLD, "FOLD"},{CHECK, "CHECK"}, {BET, "BET"}, {ALLIN, "ALLIN"}
};


Node::Node(){
  p1 = false;
  street = DONE;
  action = FOLD;
  children = {};
  strats = {};
  strat_sum = {};
}


Node::Node(bool p1, Street street, Action action, std::map<std::pair<Card*, Card*>,Node*> children, 
           std::map<std::pair<Card*, Card*>,Node*> strats, std::map<std::pair<Card*, Card*>,Node*>strat_sum) : 
  p1{p1}, street{street}, action{action}, children{children}, strats{strats},strat_sum{strat_sum} {}


