#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Node.h"
#include "helperfunctions.h"
#include <utility>
#include <map>
#include <string>

void print_cards(std::vector<Card*> &vec){
  for (Card *i : vec){
    i->print_card();
  }
}

int main(){
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
  Deck deck = Deck();
  int p1_wins = 0;
  std::pair<Card*,Card*> hand1 = {deck.deal(), deck.deal()};
  std::pair<Card*,Card*> hand2 = {deck.deal(), deck.deal()};
  std::cout << "STARTING HAND P1:\n";
  std::cout << "-----------------------------\n";
  hand1.first->print_card();
  hand1.second->print_card();
  std::cout << "-----------------------------\n";
  std::cout << "STARTING HAND P1:\n";
  std::cout << "-----------------------------\n";
  hand2.first->print_card();
  hand2.second->print_card();
  std::cout << "-----------------------------\n";
  int iterations = 1000;
  for (int i=0; i<iterations; ++i){
    std::vector<Card*> comm;
    for (int x=0;x<5; ++x){
      comm.push_back(deck.deal());
      //comm[x]->print_card();
    }
    std::pair<handStrength, int> strnegth1 = get_hand_strength(hand1, comm);
    std::pair<handStrength, int> strnegth2 = get_hand_strength(hand2, comm);
    if (did_p1_win(strnegth1 ,strnegth2)){
      ++p1_wins;
    }
    deck.reset_deck();
    hand1.first->card_dealt();
    hand1.second->card_dealt();
    hand2.first->card_dealt();
    hand2.second->card_dealt();

  }

  float prct = (float)p1_wins/(float)iterations;
  std::cout << "hand percentage of win for p1 = " << prct << "\n";

  return 0;
}

