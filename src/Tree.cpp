#include "Tree.h"

std::vector<float> bet_sizes = {.25, .5,.75,.85,1,1.5,2};

Tree::Tree(hand_pair hand,float bb, float pot,std::vector<std::pair<int,char>> dealt,std::vector<hand_pair> range1, 
           std::vector<hand_pair> range2, std::pair<float,float> stacks) : 
  hand{hand}, bb{bb},pot{pot},dealt{dealt}, deck{Deck()}, stacks{stacks}
{
  make_matchups(range1,range2);
  make_head();
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

void Tree::make_matchups(std::vector<hand_pair> range1, std::vector<hand_pair> range2){
  for (hand_pair &h2 : range2){
    std::pair<Card*,Card*> hand2 = {deck.deal_specific(h2.first),deck.deal_specific(h2.second)};
    matchups_p2[hand2] = {};
    p2_range.push_back(hand2);
  }

  for (hand_pair &h1 : range1){
       std::vector<std::pair<Card*,Card*>> p1_vec;
    std::pair<Card*,Card*> hand1 = {deck.deal_specific(h1.first),deck.deal_specific(h1.second)};
    p1_range.push_back(hand1);
    for (std::pair<Card*,Card*> &h2 : p2_range){
      if (are_cards_unique(hand1,h2)){
        //std::pair<Card*,Card*> hand2 = {deck.deal_specific(h2.first),deck.deal_specific(h2.second)};
        p1_vec.push_back(h2);
        matchups_p2[h2].push_back(hand1);
      }
    }
    matchups_p1[hand1] = p1_vec;
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
  float num_cards1 = p1_range.size();
  std::map<card_pairs,float> dic2;
  float num_cards2 = p2_range.size();
  
  for (std::pair<Card*, Card*> &temp_hand : p1_range){
    dic1[temp_hand] = 1.0/num_cards1;
  }
  for (std::pair<Card*, Card*> &temp_hand : p2_range){
    dic2[temp_hand] = 1.0/num_cards2;
  }
  
  int count = 0;
  for (std::pair<Action,float> &b : bets){
    float bet1 = bets[count].second;
    int num_bets = bets[count].first != CHECK ? 1 : 0;
    std::vector<Node*> child = make_children(false, FLOP,bets[count].first,
                                             dic1,dic2,pot+bet1,bet1,
                                             {stacks.first-bet1,stacks.second},num_bets);
    heads.push_back(Node(true, FLOP, b.first,child, 
                         dic1,pot+bet1,
                         bet1,stacks.first-bet1,num_bets));
    ++count;
  }
}

//you use the size of p1 range and p2 range 
//to get the 
//only thing you are not passing to this function is the children 
std::vector<Node*> Tree::make_children(bool player,Street prev_street, Action prev_action,
                                      std::map<card_pairs,float> strats1,
                                      std::map<card_pairs,float> strats2,
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
  
  for (std::pair<Action,float> &data : bets){
    Action actC = data.first;
    float bet_size = data.second;
    bool new_p = !player;
    Street thisStreet = get_next_street(actC,prev_action,prev_street);
    std::pair<float,float> new_stack;
    std::map<card_pairs,float> my_strats;
    float myStack;
    if (player){
      new_stack = {prev_stack.first-bet_size, prev_stack.second};
      my_strats = strats1;
      myStack = new_stack.first;
    }
    else{
      new_stack = {prev_stack.first, prev_stack.second-bet_size};
      my_strats = strats2;
      myStack = new_stack.second;
    }
    int c_num_bets = actC == BET ? num_bets +1 : num_bets;
    std::vector<Node*> my_child = make_children(new_p,thisStreet,actC,strats1,strats2,potsize+bet_size,bet_size,new_stack,c_num_bets);
    new_children.push_back(new Node(player,thisStreet,actC,my_child,my_strats,potsize+bet_size,bet_size,myStack,c_num_bets));
  }
  return new_children;
}



