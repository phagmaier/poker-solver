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
using hand_pairs = std::pair<h_pair,h_pair>;
using range = std::vector<h_pair>;

void dumb(std::vector<Node*> nodes){
  std::cout << "ABOUT TO PRINT some STRATS\n";
  std::cout << "\n\n\n";
  for (Node* i: nodes){
  std::cout << "\n\n\n";
    for (auto x : i->strats){
      std::cout << "-----------------------\n";
      x.first.first->print_card();
      x.first.second->print_card();
      std::cout << x.second << "\n";
      std::cout << "-----------------------\n";
    }
  }
}

void dumb(std::vector<Node> nodes){
  std::cout << "ABOUT TO PRINT some STRATS\n";
  std::cout << "\n\n\n";
  for (Node &i: nodes){
  std::cout << "\n\n\n";
    for (auto x : i.strats){

      std::cout << "-----------------------\n";
      x.first.first->print_card();
      x.first.second->print_card();
      std::cout << x.second << "\n";
      std::cout << "-----------------------\n";
    }
  }
}


int counting(const Node* node) {
    int count = 1;
    for (const Node* n : node->children) {
        count += counting(n);
    }
    return count;
}

void count(const std::vector<Node>& heads) {
    int count = 0;
    for (const Node& n : heads) {
        count += counting(&n);
    }
    std::cout << count << "\n";
}

/*
int counting(Node* node){
  int count = 1;
  for (Node* n : node->children){
    count += counting(n);
  }
  return count;
}

void count(std::vector<Node> heads){
  int count = heads.size();
  for (Node n : heads){
    for (Node *child : n.children){
      count += counting(child); 
    }
  }
  std::cout << count << "\n";
}
*/



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
      Street street = FLOP;
      std::pair<float,float> stacks = {100,100};
      float last_bet = 0;
      float potsize = 1.5;
      Action last_act = CHECK;
      int num_bets = 0;
      std::vector<std::pair<int,char>> flop = {{13,'h'}, {13,'c'}, {14,'h'}};
      Tree tree = Tree(hand,2,3,flop,p1_range,p2_range,{100,100});
      //std::map<std::string, int> dic = gen_dic();
      //std::cout << dic["2c2d2h2s3c"] << "\n";
      //std::cout << dic["Ah10d3c3s2s"] << "\n";
      //std::cout << dic["2s3c3sTdAh"] << "\n";
      //std::map<std::string, int> *dic = gen_dic_ptr();
      //std::cout << (*dic)["2c-2d-2h-2s-3c"] << "\n";
      //std::cout << (*dic)["Ac-Ad-Ah-As-Ks"] << "\n";
      //count(tree.heads); 
      tree.CFRM();
      std::cout << "hello world\n";      
      //dumb(tree.heads);
      //dumb(tree.heads[0].children);
      //dumb(tree.heads[0].children[0]->children);
      
      
      return 0;
}

