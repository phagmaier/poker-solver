//YOU ARE CURRENTLY MAKING COPIES OF CARDS
//MAY BE SLIGHTLY FASTER / BETTER TO USE POINTERS
#ifndef DEALER_H 
#define DEALER_H
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <map>
#include "Card.h"

class Deck{
  
  public:
    Deck();
    inline void shuffle(){
      std::random_device rd;
      std::mt19937 g(rd());  
      std::shuffle(cards.begin(), cards.end(), g);
    }  
    
    inline void reset_deck(){
      cards.clear(); 
      cards.reserve(52);
      std::copy(og_deck.begin(), og_deck.end(), std::back_inserter(cards));
      counter = 0;
    }

    Card deal();
    inline void remove(int val, char suit){
      dead_cards.push_back(Card(val,suit));
    }
  inline std::vector<Card> get_deck(){
    return cards;
  }
      
  private:
  std::vector<Card> cards;
  std::vector<Card> og_deck;
  std::vector<Card> dead_cards;
  int counter;
  bool isSame(Card card);

};

#endif 
