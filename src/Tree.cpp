#include "Tree.h"
//have to init deck in {} because if not it inits it 
//as a default deck and then destrpys it twice don't want 
//that happening


Tree::Tree(hand_pairs the_hand, 
       bool is_p1, float bb, float sb, std::vector<hand_pairs> p1_range,
       std::vector<hand_pairs> p2_range, Node::Street street,
        std::pair<float,float> stacks,  
        float last_bet, float potsize, Node::Action last_act,
        int num_bets,std::vector<std::pair<int,char>> dealt) : is_p1{is_p1}, 
        bb{bb}, sb{sb}, p1_range{p1_range}, p2_range{p2_range},
        deck{Deck()},
        head{init_head(is_p1, street, last_bet, potsize,stacks,last_act, num_bets, bb, p1_range,p2_range)}
{

  hand = {deck.deal_specfic(the_hand.first.first, the_hand.first.second), 
          deck.deal_specfic(the_hand.second.first, the_hand.second.second)};
  for (std::pair<int,char> &cards : dealt){
    dealt_cards.push_back(deck.deal_specfic(cards.first, cards.second));
  }
  
  community = {};
  }

//also Init's matchups
std::vector<Head> Tree::init_head(bool is_p1, Node::Street street, float last_bet,float potsize,
                 std::pair<float,float> stacks, Node::Action last_act,
                 int num_bets, float bb,std::vector<hand_pairs> p1_range,
                 std::vector<hand_pairs> p2_range){
  std::vector<Head> heads;
  for (hand_pairs &i : p1_range){
    for (hand_pairs &j : p2_range){
      if (!((i.first.first == j.first.first && i.first.second == j.first.second)
            || i.second.first == j.second.first && i.second.second == j.second.second)){
        heads.push_back(Head(is_p1,street,last_bet,potsize,stacks,last_act,num_bets,
                             bb));
        matchups.push_back({i,j});
      } 
    }
  }
  return heads;
}

