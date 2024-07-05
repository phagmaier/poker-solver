#include "Deck.h"

std::map<char,int> Deck::suit_dic = {{'c',0},{'d',13},{'h',26},{'s',39}};

Deck::Deck(){
  char suits[4] = {'c', 'd', 'h', 's'};
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

    std::cout << "deck destructor called.\n";
    std::cout << "DELETING CARDS\n";
    //for (Card *card : cards){
      for (int i=0; i< og_deck.size(); ++i){
      if (og_deck[i]){
        //delete card;
        delete og_deck[i];
        og_deck[i] = NULL;
        cards[i] = NULL;
      }
    }
  //cards = {};
  //og_deck = {};
  std::cout << "ALL CARDS DELETED SUCESFULLY\n";
  og_deck.clear();
  cards.clear();

  std::cout << "Deck construcor completed\n";
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

