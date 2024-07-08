#include "Tree.h"

std::vector<float> bet_sizes = {.25, .5,.75,.85,1,1.5,2};

Tree::Tree(hand_pair hand,std::vector<std::pair<int,char>> dealt,std::vector<hand_pair> p1_range, 
           std::vector<hand_pair> p2_range, std::pair<float,float> stacks) : 
  hand{hand}, dealt{dealt},p1_range{p1_range}, p2_range {p2_range}, deck{Deck()}, stacks{stacks}
{
  make_matchups();
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

void Tree::make_matchups(){
  for (hand_pair &h2 : p2_range){
    std::pair<Card*,Card*> hand2 = {deck.deal_specific(h2.first),deck.deal_specific(h2.second)};
    matchups_p2[hand2] = {};
  }

  for (hand_pair &h1 : p1_range){
       std::vector<std::pair<Card*,Card*>> p1_vec;
    std::pair<Card*,Card*> hand1 = {deck.deal_specific(h1.first),deck.deal_specific(h1.second)};
    for (hand_pair &h2 : p2_range){
      if (are_cards_unique(h1,h2)){
        std::pair<Card*,Card*> hand2 = {deck.deal_specific(h2.first),deck.deal_specific(h2.second)};
        p1_vec.push_back(hand2);
        matchups_p2[hand2].push_back(hand1);
      }
    }
    matchups_p1[hand1] = p1_vec;
  }

}

void Tree::make_head(){
}
