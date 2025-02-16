#include "Deck.h"
#include <unordered_map>

std::unordered_map<std::string, unsigned int short> Deck::str_to_order;

Deck::Deck() {
  deck_count = 0;
  int count = 0;
  for (int i = 0; i < 13; ++i) {
    for (int x = 0; x < 4; ++x) {
      deck.emplace_back(Card(i, x));
      ++count;
    }
  }
  make_order_map();
}

void Deck::shuffle() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::shuffle(deck.begin(), deck.end(), gen);
}

// void Deck::sort() { std::sort(deck.begin(), deck.end(), deck_compare); }

void Deck::reset() {
  shuffle();
  deck_count = 0;
}

Card Deck::get_specific_card(std::string &str) {
  std::cout << "NOTE MAKE SURE DECK SORTED AND RESET BEFORE CALLING THIS\n";
  std::cout << "AND THAT CARD VALUE (NUMBER OF CARD AKA IT'S RANK is passed as "
               "a single char)\n";
  int val = str[0] - '0';
  int suit = 0;
  switch (str[1]) {
  case 'D':
    suit = 0;
    break;
  case 'd':
    suit = 0;
    break;
  case 'H':
    suit = 1;
    break;
  case 'h':
    suit = 1;
    break;
  case 'S':
    suit = 2;
    break;
  case 's':
    suit = 2;
    break;
  case 'C':
    suit = 3;
    break;
  case 'c':
    suit = 3;
    break;
  default:
    std::cerr << "THIS SHOULD NEVER PRINT IMROPER VALUE ENETERED GET CARD "
                 "RETURNING JUNK VALUE\n";
    suit = 0;
  }
  int index = 13 * suit + val;
  if (index >= deck.size()) {
    std::cerr << "ASKING FOR A CARD THAT DOESN'T EXIST";
    std::cerr << " EITHER BECAUSE INVALID ENTRY OR THAT CARD ALREADY DEALT\n";
    std::cerr << "GOING TO GIVE YOU A JUNK CARD\n";
    return Card(0, 0);
  }
  return deck[index];
}

void Deck::remove_specific_card(Card &card) {
  unsigned int short order = card.order;
  for (int i = 0; i < deck.size(); ++i) {
    if (deck[i].order == order) {
      deck[i] = deck[deck.size() - 1];
      deck.pop_back();
      return;
    }
  }
}

void Deck::make_order_map() {
  std::string strs[52] = {"2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "TD",
                          "JD", "QD", "KD", "AD", "2H", "3H", "4H", "5H", "6H",
                          "7H", "8H", "9H", "TH", "JH", "QH", "KH", "AH", "2S",
                          "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS", "JS",
                          "QS", "KS", "AS", "2C", "3C", "4C", "5C", "6C", "7C",
                          "8C", "9C", "TC", "JC", "QC", "KC", "AC"};
  for (unsigned int short i = 0; i < 52; ++i) {
    Deck::str_to_order[strs[i] = i];
  }
}

bool deck_compare(Card &a, Card &b) { return a.order < b.order; }
