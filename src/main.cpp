/*
*
*
*/
#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Node.h"
#include "Tree.h"
#include "helperfunctions.h"
#include <utility>
#include <map>
#include <string>

using h_pair = std::pair<int,char>;
using range = std::vector<h_pair>;

int main(){
      hand_pairs hand = {{14,'h'},{2,'h'}};
      bool is_p1 = true;
      float bb = 1;
      float sb = .5;
      std::pair<int,char> c1_1 = {14, 'h'};
      std::pair<int, char> c2_1 = {2,'h'};
      std::vector<hand_pairs> p1_range = {{c1_1,c2_1}};
      std::pair<int,char> c1_2 = {3, 'h'};
      std::pair<int, char> c2_2 = {2,'d'};

      std::vector<hand_pairs> p2_range= {{c1_2,c2_2}};
      Node::Street street = Node::FLOP;
      std::pair<float,float> stacks = {100,100};
      float last_bet = 0;
      float potsize = 1.5;
      Node::Action last_act = Node::CHECK;
      int num_bets = 0;
      std::vector<std::pair<int,char>> flop = {{13,'h'}, {13,'c'}, {14,'h'}};
      Tree tree = Tree(hand,is_p1,bb,sb,p1_range,p2_range, street, stacks, last_bet,potsize,last_act,num_bets,flop);
      std::map<std::string, int> dic = gen_dic();
      std::cout << dic["2c2d2h2s3c"] << "\n";
      //std::map<std::string, int> *dic = gen_dic_ptr();
      //std::cout << (*dic)["2c-2d-2h-2s-3c"] << "\n";
      //std::cout << (*dic)["Ac-Ad-Ah-As-Ks"] << "\n";
      
      return 0;
}

