#include "Tree.h"

Tree::Tree(std::pair<std::pair<int,char>,std::pair<int,char>> the_hand, 
       bool is_p1, float bb, float sb, std::vector<std::pair<int,char>> range1,
       std::vector<std::pair<int,char>> range2, 
        std::pair<float,float> stacks,  
        float last_bet, float potsize, Node::Action last_act,
        int num_bets,std::vector<std::pair<int,char>> dealt) : is_p1{is_p1}, 
        bb{bb}, sb{sb}
{
  //head = Node(is_p1, static_cast<Node::Street>(community.size()),
              //last_bet, potsize, stacks, last_act, num_bets, NULL);
  deck = Deck();
  hand.first = deck.deal_specfic(the_hand.first.first, the_hand.first.second);
  hand.second = deck.deal_specfic(the_hand.second.first, the_hand.second.second);
  for (std::pair<int,char> &cards : dealt){
    dealt_cards.push_back(deck.deal_specfic(cards.first, cards.second));
  }
}
