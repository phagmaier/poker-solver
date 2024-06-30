#ifndef TREE_H 
#define TREE_H 
#include "Node.h"
#include "Card.h"
#include "Deck.h"
#include <utility>
/*
bool p1,Street street, float prev_bet, float potsize, 
         std::pair<float,float> stacks, Action prev_act, 
         int num_bets, Node *parent
*/
//takes a vector of the street and the bet to determine 
//the ranges
//using histVec = std::vector<std::pair<Node::Street, float>>;
//DON'T THINK I ACTUALLY NEED THE ABOVE SINCE WE SOLVE FROM WHERE WE ARE 
class Tree{
  public:
  //The actual hand we have, which player, big blind, 
  //small blind, the range of hands P1 can have,
  //the range of hands p2 can have, 
  Tree(std::pair<Card,Card> hand, bool is_p1, float bb, 
       float sb, std::vector<std::pair<Card,Card>> range1,
       std::vector<std::pair<Card,Card>> range2, 
        std::pair<float,float> stacks, std::vector<Card> community, 
        float last_bet, float potsize, Node::Action last_act,
        int num_bets);
  
  std::pair<Card,Card> hand;
  bool is_p1;
  float bb;
  float sb;
  std::vector<std::pair<Card, Card>> range1;
  std::vector<std::pair<Card, Card>> range2;
  std::pair<float,float> stacks;
  std::vector<Card> community;
  Node head;

};

#endif 
