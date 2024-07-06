/*
 *NOTE THAT YOU WILL HAVE TO CHECK  
 */
#ifndef TREE_H 
#define TREE_H 
#include "Node.h"
#include "Card.h"
#include "Deck.h"
#include <utility>
#include "Head.h"

using hand_pairs = std::pair<std::pair<int, char>, std::pair<int,char>>;
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
  Tree(hand_pairs the_hand, 
       bool is_p1, float bb, float sb, std::vector<hand_pairs> p1_range,
       std::vector<hand_pairs> p2_range, Node::Street street,
        std::pair<float,float> stacks,  
        float last_bet, float potsize, Node::Action last_act,
        int num_bets,std::vector<std::pair<int,char>> dealt);

  
  //std::pair<std::pair<int,char>,std::pair<int,char>> hand;
  bool is_p1;
  float bb;
  float sb;
  std::vector<hand_pairs> p1_range;
  std::vector<hand_pairs> p2_range;

  Deck deck;

  std::pair<Card*,Card*> hand;
    std::vector<Card*> dealt_cards; //cards that have to be included
  std::vector<Card*> community;
  std::vector<std::pair<hand_pairs,hand_pairs>> matchups;
  std::vector<Head> head;
  

  //***NOTE****:
  // also initializes the machups vector
  //so you won't actually have to save the ranges they 
  //will be in the head node 
  //or you can save the 
  std::vector<Head> init_head(bool is_p1, Node::Street street, float last_bet, float potsize,
                 std::pair<float,float> stacks, Node::Action last_act,
                 int num_bets, float bb,std::vector<hand_pairs> p1_range,
                 std::vector<hand_pairs> p2_range);




};

#endif 
