#ifndef TREE_H
#define TREE_H

#include <vector>
#include "Node.h"
#include "Card.h"
#include "Deck.h"
#include <utility>

using hand_pair = std::pair<std::pair<int, char>, std::pair<int, char>>;
using card_pairs = std::pair<std::pair<Card*,Card*>, std::pair<Card*,Card*>>;
class Tree{
  public:
    Tree(hand_pair hand,std::vector<std::pair<int,char>> dealt,std::vector<hand_pair> p1_range, 
         std::vector<hand_pair> p2_range, std::pair<float,float> stacks);
    static std::vector<float> bet_sizes;
    hand_pair hand;
    std::vector<std::pair<int,char>> dealt;
    std::vector<hand_pair> p1_range;
    std::vector<hand_pair> p2_range;
    std::pair<float,float> stacks;
    Deck deck; 
    std::map<std::pair<Card*, Card*>, std::vector<std::pair<Card*,Card*>>> matchups_p1;
    std::map<std::pair<Card*,Card*>, std::vector<std::pair<Card*,Card*>>> matchups_p2; //gives index of hands going against one another
    std::map<std::pair<Card*,Card*>,Node> head;    

    bool are_cards_unique(hand_pair &one, hand_pair &two);
    bool are_cards_unique(card_pairs &one, card_pairs &two);
    void make_matchups();
    void make_head();
    void make_Nodes();
};
#endif
