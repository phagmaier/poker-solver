#include "Tree.h"


Tree::Tree(std::pair<std::pair<int,char>,std::pair<int,char>> the_hand, 
       bool is_p1, float bb, float sb, std::vector<std::pair<int,char>> p1_range,
       std::vector<std::pair<int,char>> p2_range, Node::Street street,
        std::pair<float,float> stacks,  
        float last_bet, float potsize, Node::Action last_act,
        int num_bets,std::vector<std::pair<int,char>> dealt) : is_p1{is_p1}, 
        bb{bb}, sb{sb}, p1_range{p1_range}, p2_range{p2_range},
        head{init_head(is_p1, street, last_bet, potsize,stacks,last_act, num_bets, bb, p1_range,p2_range)}
{
  deck = Deck();

  hand = {deck.deal_specfic(the_hand.first.first, the_hand.first.second), 
          deck.deal_specfic(the_hand.second.first, the_hand.second.second)};
  
  for (std::pair<int,char> &cards : dealt){
    dealt_cards.push_back(deck.deal_specfic(cards.first, cards.second));
  }
  community = {};
    for (std::pair<int,char> &c1 : p1_range){
      for (std::pair<int,char> &c2 : p2_range){
        matchups.push_back({deck.deal_specfic(c1), deck.deal_specfic(c2)});
    }
  }
    }


std::vector<Head> Tree::init_head(bool is_p1, Node::Street street, float last_bet,float potsize,
                 std::pair<float,float> stacks, Node::Action last_act,
                 int num_bets, float bb,std::vector<std::pair<int,char>> p1_range,
                 std::vector<std::pair<int,char>> p2_range){
  for (std::pair<int,char> &i : p1_range){
    for (std::pair<int,char> &i : p2_range){

    }
  }
}

