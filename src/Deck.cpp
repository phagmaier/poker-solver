#include "Deck.h"

Deck::Deck(){
  int count = 0;
  for (int i=0;i<13;++i){
    for (int x=0;x<4;++x){
      deck.emplace_back(Card(i,x));
      ++count;
    }
  }
}

Card Deck::deal(){
  Card tmp = deck[0];
  deck[0] = deck[deck.size()-1];
  deck.pop_back();
  //dead_cards.push_back();
  return tmp;
}

void Deck::shuffle(){
  static std::random_device rd;  
  static std::mt19937 gen(rd());
  std::shuffle(deck.begin(), deck.end(), gen);
} 


void Deck::sort(){
  std::sort(deck.begin(), deck.end(), deck_compare);
}

void Deck::reset(){
  deck.clear();
  for (int i=0;i<13;++i){
    for (int x=0;x<4;++x){
      deck.emplace_back(Card(i,x));
    }
  }
  //dead_cards.clear();
  //sort();
}

Card Deck::get_card(std::string &str){
  std::cout << "NOTE MAKE SURE DECK SORTED AND RESET BEFORE CALLING THIS\n";
  int val = str[0]- '0';
  int suit=0;
  switch(str[1]) {
    case 'D':
      suit = 0;
      break;
    case 'd':
      suit = 0;
      break;
    case 'H':
      suit= 1;
      break;
    case 'h':
      suit= 1;
      break;
    case 'S':
      suit= 2;
      break;
    case 's':
      suit = 2;
      break;
    case 'C':
      suit= 3;
      break;
    case 'c':
      suit = 3;
      break;
    default:
      std::cout << "THIS SHOULD NEVER PRINT IMROPER VALUE ENETERED GET CARD\n";
      suit=0;
  }
  int index = 13 * suit + val;
  if (index >= deck.size()){
    std::cout << "ASKING FOR A CARD THAT DOESN'T EXIST";
    std::cout << " EITHER BECAUSE INVALID ENTRY OR THAT CARD ALREADY DEALT\n";
    std::cout << "GOING TO GIVE YOU A JUNK CARD\n";
    return Card(0,0);
  }
  return deck[index];
}

void Deck::remove_hand(Card &card){
  std::cout << "MAKE SURE DECK FULL AND SORTED BEFORE REMOVING\n";
  if (card.order < deck.size()){
    deck[0] = deck[deck.size()-1];
    deck.pop_back();
  }
  else{
    std::cout << "CARD NOT IN RANGE SEE ABOVE\n";
  }
}


bool deck_compare(Card &a, Card &b){
  return a.order < b.order;
}


