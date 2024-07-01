#include "Deck.h"

std::map<char,int> Deck::suit_dic = {{'C',0},{'D',13},{'H',26},{'S',39}};

Deck::Deck(){
  char suits[4] = {'C', 'D', 'H', 'S'};
  int count = 0;
  for (char s : suits){ 
    for (int i=2; i<=14; ++i){
      Card *temp = new Card(i,s);
      og_deck.emplace_back(temp); 
      cards.push_back(temp); 
      ++count;
    }
  }
  counter = 0;
  shuffle();
}

Deck::~Deck(){
  int count = 0;
  for (Card *card : cards){
    delete card;
  }
  og_deck.clear();
  cards.clear();


}

Card *Deck::deal(){
  Card *temp = cards[counter];
  while (temp->get_dealt()){
    ++counter;
    temp = cards[counter];
  }
  temp->card_dealt();
  ++counter;
  return temp;
}

void Deck::shuffle(){
      std::random_device rd;
      std::mt19937 g(rd());  
      std::shuffle(cards.begin(), cards.end(), g);
    } 

