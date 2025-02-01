#include "hand_evaluator.h"
#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <utility>

void deal_seven(Card *cards, Deck &deck){
  deck.reset();
  deck.shuffle();
  for (int i=0;i<7;++i){
    cards[i] = deck.deal();
  } 
}

void print_card(Card &card){
  card.print_card();
  std::cout << " ";
}

void print_cards(Card *cards){
  std::cout << "YOUR CARDS: ";
  print_card(cards[0]);
  print_card(cards[1]);
  std::cout << "\nCommunity Cards\n";
  for (int i=2;i<7;++i){
    print_card(cards[i]);
  }
  std::cout << "\n";
}

void print_rank(Rank rank){
  switch(rank) {
    case NOTHING:
      std::cout << "ERROR GOT NOTHING\n";
    break;
    case HIGH:
      std::cout << "HIGH CARD\n";
    break;
    case PAIR:
      std::cout << "PAIR\n";
    break;
    case TWO:
      std::cout << "TWO PAIR\n";
    break;

    case TRIPS:
      std::cout << "TRIPS\n";
    break;
    case STRAIGHT:
      std::cout << "STRAIGHT\n";
    break;
    case FLUSH:
      std::cout << "FLUSH\n";
    break;
    case FULL:
      std::cout << "FULL HOUSE\n";
    break;
    case QUADS:
      std::cout << "QUADS\n";
    break;
    case STRAIGHT_FLUSH:
      std::cout << "STRAIGHT FLUSH\n";
    break;
    default:
      std::cout << "ERROR THIS SHOULD NEVER PRINT ERROR PRINTING RANK\n";
  }
}

int main(){
  Deck deck = Deck();
  Card cards[7];
  for (int i=0;i<10000;++i){
    deal_seven(cards, deck);
    print_cards(cards);
    std::pair<Rank,unsigned int>result= hand_evaluator(cards);
    print_rank(result.first);
  }
  return 0;
}
