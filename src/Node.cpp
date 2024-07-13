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
      n->strat_sum[i.first] += i.second;
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
      n.strat_sum[i.first] += i.second;
    }
  }
}

void Node::get_leaf_ev(matchDic &range1,
                       matchDic &range2,
                       std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p1_win,
                       std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p2_win,
                       std::map<std::pair<Card*,Card*>,float> prct1, 
                       std::map<std::pair<Card*,Card*>,float> prct2){
  ev.clear();
  actual.clear();
  float winnings;
  if (action == FOLD){
    winnings = -(potsize-stack);
    if (p1){
      //for(std::pair<Card*,Card*> &i : range1){
        //for (std::pair<Card*,Card*> &x : range2){
        for (auto &i : range1){
          for (std::pair<Card*,Card*> &x : i.second){
          ev[i.first][x] = winnings * prct1[i.first] * prct2[x];
          actual[i.first][x] = winnings * prct2[x];

        }
      }
    }
    else{
      for(auto &i : range2){
        for (std::pair<Card*,Card*> &x : i.second){
          ev[i.first][x] = winnings * prct1[x] * prct2[i.first];
          actual[i.first][x] = winnings * prct1[x];
        }
      }

    }
    return;
    }
    if (p1){
      for(auto &i : range1){
        for (std::pair<Card*,Card*> &x : i.second){
          if (p1_win[i.first][x]){
            winnings = potsize - stack;
          }
          else{
            winnings = -(potsize - stack);
          }
          ev[i.first][x] = winnings * prct1[i.first] * prct2[x];
          actual[i.first][x] = winnings * prct2[x];

        }
      }
    }
    else{
      for(auto &i : range2){
        for (std::pair<Card*,Card*> &x : i.second){
          if (p2_win[i.first][x]){
            winnings = potsize-stack;
          }
          else{
            winnings = -(potsize-stack);
          }
          ev[i.first][x] = winnings * prct1[x] * prct2[i.first];
          actual[i.first][x] = winnings * prct1[x];
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
void Node::get_ev(matchDic &range1,
                  matchDic  &range2,
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
      for (auto &h : range1){
       prct1[h.first] *=  strats[h.first]; 
      }
    }
    else{
      for (auto &h : range2){
       prct2[h.first] *=  strats[h.first]; 
      }
    }
      
    ev.clear();
    actual.clear();
    for (Node *n : children){
      n->get_ev(range1, range2,p1_win,p2_win,prct1,prct2);
      if (p1){
        for (auto &i : range1){
          for (std::pair<Card*,Card*> &x : i.second){
            ev[i.first][x] -= (n->ev[x][i.first]);
            actual[i.first][x] -=(n->actual[x][i.first]);
          }
        }
      }
      else{
        for (auto &i : range2){
          for (std::pair<Card*,Card*> &x : i.second){
            ev[i.first][x] -= (n->ev[x][i.first]);
            actual[i.first][x] -= (n->actual[x][i.first]);
          }
        }
      }
    }

    get_regret(children); 
        
  }

}

void Node::save_strat(std::vector<Node> nodes){
  std::map<std::pair<Card*,Card*>, float> totals;
  for (Node &n : nodes){
    if(n.children.size()){
      save_strat(n.children);
    }
    for (auto &i : n.strat_sum){
      totals[i.first] += i.second;
    }
  }
  for (Node &n :nodes){
    for (auto &i : n.strat_sum){
     n.final_strats[i.first].push_back(i.second/totals[i.first]); 
    }
  }
}

void Node::save_strat(std::vector<Node*> nodes){
  std::map<std::pair<Card*,Card*>, float> totals;
  for (Node *n : nodes){
    if(n->children.size()){
      save_strat(n->children);
    }
    for (auto &i : n->strat_sum){
      totals[i.first] += i.second;
    }
  }
  for (Node *n :nodes){
    for (auto &i : n->strat_sum){
     n->final_strats[i.first].push_back(i.second/totals[i.first]); 
    }
  }
}

