#ifndef TREE_H
#define TREE_H

#include <vector>
#include "Node.h"
#include "Card.h"
#include "Deck.h"
#include <utility>
#include "helperfunctions.h"
#define ITERATIONS 10000
#define NUM_SAMPLES 1000

using hand_pair = std::pair<std::pair<int, char>, std::pair<int, char>>;
using card_pairs = std::pair<Card*, Card*>;
using matchups_dic = std::map<card_pairs, std::vector<card_pairs>>;
using boolDic = std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>>;
class Tree{
  public:
    Tree(hand_pair hand,float bb,float pot,std::vector<std::pair<int,char>> dealt_cards,std::vector<hand_pair> range1, 
         std::vector<hand_pair> range2, std::pair<float,float> stacks);
    static std::vector<float> bet_sizes;
    hand_pair hand;
    float bb;
    float pot;
    std::vector<Card*> dealt;
    //need to change this to be cards
    //you pass it as a <handpairs>
    // but ultimatley it's converted into cards
    std::vector<std::pair<Card*, Card*>> p1_range;
    std::vector<std::pair<Card*,Card*>> p2_range;
    std::pair<float,float> stacks;
    Deck deck; 

    void get_dealt(std::vector<std::pair<int,char>> &cards);
    std::map<std::pair<Card*, Card*>, std::vector<std::pair<Card*,Card*>>> matchups_p1;
    std::map<std::pair<Card*,Card*>, std::vector<std::pair<Card*,Card*>>> matchups_p2; //gives index of hands going against one another
    std::vector<Node> heads;
    std::vector<Card*> community;


    bool are_cards_unique(hand_pair &one, hand_pair &two);
    bool are_cards_unique(card_pairs &one, card_pairs &two);
    bool are_cards_unique(card_pairs &one, std::vector<Card*>&comm);
    bool are_cards_unique(card_pairs &one,card_pairs &two, std::vector<Card*>&comm);
    void make_matchups(std::vector<hand_pair> range1, std::vector<hand_pair> range2);
    void make_head();
  std::vector<Node*> make_children(bool player, Street prev_street,
                                   Action prev_action,float potsize,
                                    float prev_bet,std::pair<float,float>prev_stack, int num_bets);
  Street get_next_street(Action act, Action prev_act, Street street);
  
  std::pair<boolDic,boolDic> get_winners(matchups_dic &one);
  void deal_community();
  void get_head_regrets();
  bool are_cards_unique(card_pairs const &one,card_pairs &two, std::vector<Card*>&comm);
  void save_strat();
  //this function calls deal_community
  std::pair<matchups_dic,matchups_dic> get_monte_carlo(); //going to prune matchups 
  void save_head_strat();
  void CFRM();
};
#endif
