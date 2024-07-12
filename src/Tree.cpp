#include "Tree.h"

std::vector<float> Tree::bet_sizes = {.25, .5,.75,.85,1,1.5,2};

Tree::Tree(hand_pair hand,float bb, float pot,std::vector<std::pair<int,char>> dealt_cards,std::vector<hand_pair> range1, 
           std::vector<hand_pair> range2, std::pair<float,float> stacks) : 
  hand{hand}, bb{bb},pot{pot}, deck{Deck()}, stacks{stacks}
{
  get_dealt(dealt_cards);
  make_matchups(range1,range2);
  make_head();
}

void Tree::get_dealt(std::vector<std::pair<int,char>> &cards){
  for (std::pair<int,char> &c : cards){
    dealt.push_back(deck.deal_specific(c));
  }
}


bool Tree::are_cards_unique(hand_pair &one, hand_pair &two){
  if (one.first.first == two.first.first && one.first.second == two.first.second){
    return false;
  }
  if (one.second.first == two.first.first && one.second.second == two.first.second){
    return false;
  }
if (one.first.first == two.second.first && one.first.second == two.second.second){
    return false;
  }
  if (one.second.first == two.second.first && one.second.second == two.second.second){
    return false;
  }
  return true;
}

bool Tree::are_cards_unique(card_pairs &one, card_pairs &two){
  if (one.first == two.first || one.first == two.second){
    return false;
  }
  if (one.second == two.first || one.second == two.second){
    return false;
  }
  return true;
}
bool Tree::are_cards_unique(card_pairs &one, std::vector<Card*>&comm){
  for (Card *c : comm){
    if (c == one.first || c == one.second){
      return false;
    }
  }
  return true;
}

bool Tree::are_cards_unique(card_pairs &one,card_pairs &two, std::vector<Card*>&comm){
  for (Card *c : comm){
    if (c == one.first || c == one.second || c == two.first || c == two.second){
      return false;
    }
  }
  return true;

}


void Tree::make_matchups(std::vector<hand_pair> range1, std::vector<hand_pair> range2){
  for (hand_pair &h2 : range2){
    std::pair<Card*,Card*> hand2 = {deck.deal_specific(h2.first),deck.deal_specific(h2.second)};
    if (are_cards_unique(hand2,community)){
      matchups_p2[hand2] = {};
      p2_range.push_back(hand2);
    }
  }

  for (hand_pair &h1 : range1){
       std::vector<std::pair<Card*,Card*>> p1_vec;
    std::pair<Card*,Card*> hand1 = {deck.deal_specific(h1.first),deck.deal_specific(h1.second)};
    if (are_cards_unique(hand1, community)){
      p1_range.push_back(hand1);
      for (std::pair<Card*,Card*> &h2 : p2_range){
        if (are_cards_unique(hand1,h2)){
          p1_vec.push_back(h2);
          matchups_p2[h2].push_back(hand1);
      }
    }
      matchups_p1[hand1] = p1_vec;
    }
  }
  
}


Street Tree::get_next_street(Action act, Action prev_act, Street street){
  if (prev_act == ALLIN || act == FOLD){
    return DONE;
  }
  if (act == CHECK && prev_act == CHECK){
    return ++street;
  }
  if (act == CALL){
    return ++street;
  }
  return street;
}

//will have to call function make node to get the 
//vector of children
void Tree::make_head(){
  std::vector<std::pair<Action,float>> bets= {{CHECK,0}, {ALLIN,stacks.first}};
  
  for (int i : bet_sizes){
    //gonna make bets whole numbers
    int bet_size = i * pot;
    if (bet_size >= bb && bet_size < stacks.first){
      bets.push_back({BET,(float)bet_size});
    }
  }
  std::map<card_pairs,float> dic1;
  float denom= bets.size();
   
  for (std::pair<Card*, Card*> &temp_hand : p1_range){
    dic1[temp_hand] = 1.0/denom;
  }
    
  int count = 0;
  for (std::pair<Action,float> &b : bets){
    float bet1 = bets[count].second;
    int num_bets = bets[count].first != CHECK ? 1 : 0;
    std::vector<Node*> child = make_children(false, FLOP,bets[count].first,
                                             pot+bet1,bet1,
                                             {stacks.first-bet1,stacks.second},num_bets);
    heads.push_back(Node(true, FLOP, b.first,child, 
                         pot+bet1,
                         bet1,stacks.first-bet1,num_bets));
    ++count;
  }
  for (Node &h : heads){
    h.set_strats(dic1);
    float temp_size = (float)h.children.size();
    std::map<card_pairs,float> dic2;
    for (std::pair<Card*, Card*> &temp_hand : p2_range){
        dic2[temp_hand] = 1.0/temp_size;
  }
    for (Node *n : h.children){
      n->set_strats(dic2);
    }
  }
}

//you use the size of p1 range and p2 range 
//to get the 
//only thing you are not passing to this function is the children 
std::vector<Node*> Tree::make_children(bool player,Street prev_street, Action prev_action,
                                      float potsize, float prev_bet,
                                       std::pair<float,float>prev_stack, int num_bets){
  
  //base case the node ahead of you is a terminal node
  if (prev_street==DONE){
    return {};
  }
  std::vector<Node*> new_children;

  float curr_stack;
  float opp_stack;
  std::vector<std::pair<Action,float>> bets;

  if(player){
    curr_stack = prev_stack.first;
    opp_stack = prev_stack.second;
    }
  else{
    curr_stack = prev_stack.second;
    opp_stack = prev_stack.first;

    }
  if (prev_action==ALLIN || prev_action == BET){
    bets.push_back({FOLD,0});
    if (prev_action == BET && prev_bet <curr_stack){
      bets.push_back({CALL,prev_bet});
    }
  }
  else{
    bets.push_back({CHECK,0});
  }
  if (prev_action == ALLIN || prev_bet >= curr_stack){
    bets.push_back({ALLIN,prev_bet});    
  }
  else{
   bets.push_back({ALLIN,curr_stack}); 
  } 
  //for now setting cap to three total bets 
  //so after getting raised you can only check call or go all in
  if (num_bets < 2){
  for (float b : bet_sizes){
    int my_bet = b * potsize;
    if (my_bet >= bb && my_bet < curr_stack){
      bets.push_back({BET,(float)my_bet});
    }
  }
  }

    std::map<card_pairs,float> my_strats;
    float bets_num = (float)bets.size();
    if (player){
     for (std::pair<Card*,Card*> &the_cards : p2_range){
        my_strats[the_cards] = 1.0/bets_num;
     } 
    }
    else{
      for (std::pair<Card*,Card*> &the_cards : p1_range){
        my_strats[the_cards] = 1.0/bets_num;
     } 
    }
  
  for (std::pair<Action,float> &data : bets){
    Action actC = data.first;
    float bet_size = data.second;
    bool new_p = !player;
    Street thisStreet = get_next_street(actC,prev_action,prev_street);
    std::pair<float,float> new_stack;
    float myStack;
    if (player){
      new_stack = {prev_stack.first-bet_size, prev_stack.second};
      myStack = new_stack.first;
    }
    else{
      new_stack = {prev_stack.first, prev_stack.second-bet_size};
      myStack = new_stack.second;
    }
    int c_num_bets = actC == BET ? num_bets +1 : num_bets;
    std::vector<Node*> my_child = make_children(new_p,thisStreet,actC,potsize+bet_size,bet_size,new_stack,c_num_bets);
    Node* temp_node = new Node(player,thisStreet,actC,my_child,potsize+bet_size,bet_size,myStack,c_num_bets);
    temp_node->set_strats(my_strats);
    new_children.push_back(temp_node);
  }
  return new_children;
}



//now when you are getting CFRM
//TO CHECK IF YOU CAN EVALUATE A 
//CERTAIN COMBO just check if any of the cards are
//dealt
void Tree::deal_community(){
  deck.reset_deck();
  for (Card *c : dealt){
    c->card_dealt();
    community.push_back(c);
  }
  int dealt_size = dealt.size(); 
  for (;dealt_size<5;++dealt_size){
    community.push_back(deck.deal());
  }
}
bool Tree::are_cards_unique(card_pairs const &one,card_pairs &two, std::vector<Card*>&comm){
  for (Card *c : comm){
    if (one.first == c || two.first == c || one.second == c || two.second == c){
      return false;
    }
  }
  return true;
}


std::pair<matchups_dic,matchups_dic> Tree::get_monte_carlo(){

  deal_community();
  matchups_dic matchups1;
  matchups_dic matchups2;
  for (auto &i : matchups_p1){
    std::vector<card_pairs> temp;
     for (card_pairs &h : i.second){
      if (are_cards_unique(i.first,h,community)){
        temp.push_back(h);
      }
    }
    if (temp.size()){
      matchups1[i.first] = temp;
    }
  }
  for (auto &i : matchups_p2){
    std::vector<card_pairs> temp;
     for (card_pairs &h : i.second){
      if (are_cards_unique(i.first,h,community)){
        temp.push_back(h);
      }
    }
    if (temp.size()){
      matchups2[i.first] = temp;
    }
  }

  return {matchups1,matchups2};
}


void Tree::get_head_regrets(){
  std::map<std::pair<Card*,Card*>,float> totals;
  for (Node &n : heads){
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
  for (Node &n : heads){
    for (auto &i : n.strats){
     i.second = n.regrets[i.first] / totals[i.first]; 
     n.strat_sum[i.first] += i.second;
    }
  }
}

std::pair<boolDic,boolDic> Tree::get_winners(matchups_dic &one){
  boolDic a;
  boolDic b;
  for (auto &i : one){
    std::pair<Card*,Card*> temp = i.first;
    for(std::pair<Card*,Card*> &x : i.second){
      a[i.first][x] = did_p1_win(get_hand_strength(temp,community), get_hand_strength(x,community));
      b[x][i.first] = ~a[i.first][x];
    }
  }
  return {a,b};
}


void Tree::save_head_strat(){
  std::map<std::pair<Card*,Card*>, float> totals;
  for (Node &n : heads){
    if(n.children.size()){
      n.save_strat(n.children);
    }
    for (auto &i : n.strat_sum){
      totals[i.first] += i.second;
    }
  }
  for (Node &n :heads){
    for (auto &i : n.strat_sum){
     n.final_strats[i.first].push_back(i.second/totals[i.first]); 
    }
  }
}


//remeber that you have to prune ranges for 
//the monte carlo runout so do that before calling this
//
void Tree::CFRM(){
  std::pair<matchups_dic,matchups_dic>my_matchups= get_monte_carlo();
  std::pair<boolDic,boolDic> winners = get_winners(my_matchups.first);
  std::map<std::pair<Card*,Card*>,float> prct1;
  std::map<std::pair<Card*,Card*>,float> prct2;
  for (auto &i : my_matchups.first){
    prct1[i.first] = 1;
  }
  for (auto &i : my_matchups.second){
    prct2[i.first] = 1;
  }

  //once you get the matchups you'll need to also call
  //a function to create a double dic of bools that says who won the hand
  for (Node &n : heads){
    //need to pass my_matchups first and my_matchups.second insted of p1_range_p2_range
    n.get_ev(my_matchups.first, my_matchups.second,winners.first,winners.second,prct1,prct2);
  }
  get_head_regrets();

}


