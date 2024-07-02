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
    ~Deck();
    static std::map<char,int> suit_dic;
    
     void shuffle();

    inline void reset_deck(){
      for (int i=0; i<counter; ++i){
        cards[i]->reset();
      }

      counter = 0;
      shuffle();
    }

    Card *deal();

    inline void remove(int val, char suit){
      og_deck[suit_dic[suit]+val-2]->card_dealt(); 
    }

    inline Card* deal_specfic(int val, char suit){
      og_deck[suit_dic[suit]+val-2]->card_dealt(); 
      return og_deck[suit_dic[suit]+val-2]; 
    }

  inline std::vector<Card*> get_deck(){
    return cards;
  }
      
  private:
  std::vector<Card*> cards;
  std::vector<Card*> og_deck;
  int counter;
};

#endif 
