#include "Deck.h"

Deck::Deck(){
  char suits[] = {'C', 'D', 'H', 'S'};
  for (char s : suits){ 
    for (int i=2; i<=14; ++i){
     og_deck.push_back(Card(i,s)); 
     cards.push_back(Card(i,s)); 
    }
  }
  counter = 0;
  shuffle();
  dead_cards = {};
}
 Card Deck::deal(){
  Card temp = cards[counter];
  bool same = isSame(temp);
  while (same){
    ++counter;
    temp = cards[counter];
    same = isSame(temp);
  }
  dead_cards.push_back(temp);
  ++counter;
  return temp;
}

bool Deck::isSame(Card card){
    for (Card &c : dead_cards){
      if (c.get_val() == card.get_val() && c.get_suit() == card.get_suit()){
          return true;
    }
  }
  return false;
}


