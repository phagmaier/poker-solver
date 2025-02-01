#pragma once
#include "Card.h"
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <string>
class Deck{
public:
  Deck();
  void shuffle();
  void reset();
  Card get_card(std::string &str);
  Card deal();
  void sort();
  void remove_hand(Card &card);

private:
  std::vector<Card> deck;
  //std::vector<Card> dead_cards = {};

};


bool deck_compare(Card &a, Card &b);
