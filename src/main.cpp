#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Node.h"
#include "helperfunctions.h"
#include <utility>
#include <map>
#include <string>

int countTwo(Node *node){
    if (!node) return 0;

    int count = 1; // Count the current node
    for (Node &child : node->children){
        count += countTwo(&child);
    }
    return count;
}

int main(){
  //Node node(true, Node::FLOP, 0, 1, {100,100}, Node::CHECK, 0, NULL);
  //int x = countTwo(&node);
  Deck deck = Deck();
  deck.shuffle();
  std::pair<Card,Card> hand = {deck.deal(), deck.deal()};
  std::vector<Card> comm;
  for (int i=0; i<5; ++i){
    comm.push_back(deck.deal());
  }

   std::map<handStrength, std::string> myMap = {
        {High, "High Card"},
        {Pair, "Pair"},
        {Two_pair, "Two pair"},
        {Trips, "Trips"},
        {Straight, "Straight"},
        {Flush, "Flush"},
        {Full_house, "Full House"},
        {Quads, "Quads"},
        {Straight_flush, "Straight Flush"},
        {Royal_flush, "Royal Flush"}
    };
  
  std::pair<handStrength,int> strength = get_hand_strength(hand, comm);

  std::cout << "Your cards are:\n";
  std::cout << hand.first.get_val() << " " << hand.first.get_suit() << "\n";
  std::cout << hand.second.get_val() << " " << hand.second.get_suit() << "\n";
  std::cout << "Community cards\n";
  for (auto &i : comm){
    std::cout<< i.get_val() << " " << i.get_suit() << "\n";
  }


  std::cout << "Your hand strength: " << myMap[strength.first];
  std::cout << " " << strength.second << "\n";

  return 0;
}

