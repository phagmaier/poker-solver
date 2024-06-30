#include "Tree.h"

Tree::Tree(std::pair<Card,Card> hand, bool is_p1, float bb, 
       float sb, std::vector<std::pair<Card,Card>> range1,
       std::vector<std::pair<Card,Card>> range2, 
        std::pair<float,float> stacks, std::vector<Card> community, 
        float last_bet, float potsize, Node::Action last_act,
        int num_bets) : hand{hand}, is_p1{is_p1}, 
        bb{bb}, sb{sb},
        range1{range1}, range2{range2}, stacks{stacks},
        community{community}
{
  head = Node(is_p1, static_cast<Node::Street>(community.size()),
              last_bet, potsize, stacks, last_act, num_bets, NULL);
}
