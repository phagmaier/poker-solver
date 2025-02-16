// remove player cards from the deck perminatley
// then we can remove all guranteed dealt cards
// i.e streets that already occured
// this saves time on time complexity
// cause then we can just keep shuffling

#pragma once
#include "Card.h"
#include <algorithm>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define DECK_NUM_CARDS 52
class Deck {
public:
  static std::unordered_map<std::string, unsigned int short> str_to_order;
  Deck();
  void shuffle();
  void reset();
  // when you are first getting player cards and current street cards
  Card get_specific_card(std::string &str);
  // for flop,turn,river
  Card deal_random() { return deck[deck_count++]; }

  // for removing player cards/streets that have already come
  void remove_specific_card(Card &card);

  unsigned int deck_count;
  std::vector<Card> deck;
  void make_order_map();

  // void sort();
};

bool deck_compare(Card &a, Card &b);

void make_card_order_map();
