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

void Node::get_regret(std::vector<Node*> &nodes){
  std::map<std::pair<Card*,Card*>,float> totals;
  for (Node *n : nodes){
    n->regrets.clear();
    for (auto &i : n->ev){
      for (auto &x : i.second){
        n->regrets[i.first] += n->actual[i.first][x.first] - x.second;
      }
      if (n->regrets[i.first] < 0){
        n->regrets[i.first] = 0;
      }
      totals[i.first] += n->regrets[i.first];
    }
  }
  for (Node *n : nodes){
    for (auto &i : n->strats){
     i.second = n->regrets[i.first] / totals[i.first]; 
    }
  }
}

void Node::get_regret(std::vector<Node> &nodes){
  std::map<std::pair<Card*,Card*>,float> totals;
  for (Node &n : nodes){
    n.regrets.clear();
    for (auto &i : n.ev){
      for (auto &x : i.second){
        n.regrets[i.first] += n.actual[i.first][x.first] - x.second;
      }
      if (n.regrets[i.first] < 0){
        n.regrets[i.first] = 0;
        
      }
      totals[i.first] += n.regrets[i.first];
    }
  }
  for (Node &n : nodes){
    for (auto &i : n.strats){
     i.second = n.regrets[i.first] / totals[i.first]; 
    }
  }
}

void Node::get_leaf_ev(std::vector<std::pair<Card*,Card*>> &range1,std::vector<std::pair<Card*,Card*>> &range2,
                                          std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p1_win,
                                          std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p2_win,
                                          std::map<std::pair<Card*,Card*>,float> prct1, std::map<std::pair<Card*,Card*>,float> prct2){
  float winnings;
  if (action == FOLD){
    winnings = -(potsize-stack);
    if (p1){
      for(std::pair<Card*,Card*> &i : range1){
        for (std::pair<Card*,Card*> &x : range2){
          ev[i][x] = winnings * prct1[i] * prct2[x];
          actual[i][x] = winnings * prct2[x];

        }
      }
    }
    else{
      for(std::pair<Card*,Card*> &i : range2){
        for (std::pair<Card*,Card*> &x : range1){
          ev[i][x] = winnings * prct1[x] * prct2[i];
          actual[i][x] = winnings * prct1[x];
        }
      }

    }
    return;
    }
    if (p1){
      for(std::pair<Card*,Card*> &i : range1){
        for (std::pair<Card*,Card*> &x : range2){
          if (p1_win[i][x]){
            winnings = potsize - stack;
          }
          else{
            winnings = -(potsize - stack);
          }
          ev[i][x] = winnings * prct1[i] * prct2[x];
          actual[i][x] = winnings * prct2[x];

        }
      }
    }
    else{
      for(std::pair<Card*,Card*> &i : range2){
        for (std::pair<Card*,Card*> &x : range1){
          ev[i][x] = winnings * prct1[x] * prct2[i];
          actual[i][x] = winnings * prct1[x];
        }
      }

    }
}



//ranges here will have to only include valid cards
//meaning cards that don't conflict with monte carlo runout
//
//To eliminate if statments it would be nice if 
//instead of doing ranges 1 ranges 2 you just 
//put myRange, oppRange and just passed the correct range accordingly 
void Node::get_ev(std::vector<std::pair<Card*,Card*>> &range1,std::vector<std::pair<Card*,Card*>> &range2,
                                          std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p1_win,
                                          std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p2_win,
                                          std::map<std::pair<Card*,Card*>,float> prct1, std::map<std::pair<Card*,Card*>,float> prct2){
  if (!children.size()){
    if (p1){
      for (auto &i : prct1){
        i.second *= strats[i.first];
      }
    }
    else{
      for (auto &i : prct2){
        i.second *= strats[i.first];
      }
    }
    get_leaf_ev(range1,range2,p1_win,p2_win,prct1,prct2);
  }
  else{
    if (p1){
      for (std::pair<Card*,Card*> &h : range1){
       prct1[h] *=  strats[h]; 
      }
    }
    else{
      for (std::pair<Card*,Card*> &h : range2){
       prct2[h] *=  strats[h]; 
      }
    }
    ev.clear();
    for (Node *n : children){
      n->get_ev(range1, range2,p1_win,p2_win,prct1,prct2);
      if (p1){
        for (std::pair<Card*,Card*> &i : range1){
          for (std::pair<Card*,Card*> &x : range2){
            ev[i][x] -= n->ev[x][i];
            actual[i][x] -=n->actual[x][i] * strats[i];
            regrets[i] += -n->ev[x][i] - n->actual[x][i];
          }
        }
      }
      else{
        for (std::pair<Card*,Card*> &i : range2){
          for (std::pair<Card*,Card*> &x : range1){
            ev[i][x] -= n->ev[x][i] * strats[i];
            actual[i][x] -=n->actual[x][i];
          }
        }
      }
    }
    
  }
    get_regret(children); 
}
      


