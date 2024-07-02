/*
 *NOTE ON PRUNING:
 *Because some hands are technically equivalent
 * i.e A H 10 H and A D 10 D
 * If you play suited hands of a variety you 
 * will only select one of the possible versions
 * so instead of all you may only chose one but 
 * this get's kinda complicated cause 
 * you have to include those in their hands and 
 * the off suit variet it becomes important what 
 * you take so for now maybe include them all but in 
 * the future you'll need to prune
 *
 */

/*
 *
 *SO THE TREE CAN ACTUALLY HAVE MULTIPLE HEAD NODES
 *WHERE EACH HEAD NODE REPRESENTS A DIFFERENT HAND 
 *THAT P1 CAN HAVE AS WELL AS P2 
 *SO YOUR TREE WILL ACTUALL HAVE ALL COMBINATION 
 *OF NODES I.E ACE JACK VS KING 10 ACE JACK VS AA
 * ACE TEN VS J 10 ETC...
 * 
 * can even have a vector representing the head nodes
 * for each specifc hand making it easier to actually 
 * get the ev for that specific hand
 */
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
  Tree(std::pair<std::pair<int,char>,std::pair<int,char>> the_hand, 
       bool is_p1, float bb, float sb, std::vector<std::pair<int,char>> range1,
       std::vector<std::pair<int,char>> range2, 
        std::pair<float,float> stacks, 
        float last_bet, float potsize, Node::Action last_act,
        int num_bets, std::vector<std::pair<int,char>> dealt);

  
  //std::pair<std::pair<int,char>,std::pair<int,char>> hand;
  bool is_p1;
  float bb;
  float sb;

  Deck deck;

  std::pair<Card*,Card*> hand;
  //std::vector<std::pair<int,char>> range1;
  //std::vector<std::pair<int,char>> range2;
  std::vector<Card*> dealt_cards;
  std::vector<Card*> community;
  std::vector<Node> head;

};

#endif 
