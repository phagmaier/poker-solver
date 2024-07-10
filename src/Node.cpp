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
  potsize = 0;
  bet = 0;
  stack = 0;
  children = {};
  strats = {};
  strat_sum = {};
}


Node::Node(bool p1, Street street, Action action, std::vector<Node*> children, 
           float potsize, float bet, float stack, int num_bets) : 
  p1{p1}, street{street}, action{action}, children{children},
  potsize{potsize}, bet{bet}, stack{stack}{}


Street& operator++(Street& s) {
    switch (s) {
        case DONE:
            throw std::runtime_error("Cannot increment DONE.");
        case FLOP:
            s = TURN;
            break;
        case TURN:
            s = RIVER;
            break;
        case RIVER:
            s = DONE;
            break;
    }
    return s;
}
