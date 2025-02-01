#include "Card.h"

const unsigned int Card::primes[13] = {
  2,3,5,7,11,
  13,17,19,23,
  29,31,37,41
};

std::string Card::card_array[52] = {
  "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD", "KD", "AD",
  "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "TH", "JH", "QH", "KH", "AH",
  "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS", "JS", "QS", "KS", "AS",
  "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "TC", "JC", "QC", "KC", "AC"
};

Card::Card(unsigned int val, unsigned int suit) : 
  val(val), suit(1 << suit), prime(primes[val]),
  order(13 * suit + val), card_str(card_array[(13 * suit + val)])
{}

Card::Card() :
  val(100),suit(100), prime(100),order(100),card_str("")
{}

Card::Card(const Card& other) : 
  val(other.val), suit(other.suit), 
  prime(other.prime), order(other.order), 
  card_str(other.card_str) 
{}

Card& Card::operator=(const Card& other) {
  if (this != &other) {
    val = other.val;
    suit = other.suit;
    prime = other.prime;
    order = other.order;
    card_str = other.card_str;
  }
  return *this;
}

Card::Card(Card&& other) noexcept : 
  val(other.val), suit(other.suit), 
  prime(other.prime), order(other.order), 
  card_str(std::move(other.card_str)) {
  other.val = 0;
  other.suit = 0;
  other.prime = 0;
  other.order = 0;
  other.card_str.clear();
}

Card& Card::operator=(Card&& other) noexcept {
  if (this != &other) {
    val = other.val;
    suit = other.suit;
    prime = other.prime;
    order = other.order;
    card_str = std::move(other.card_str);
    
    // Reset the moved-from object to a valid state
    other.val = 0;
    other.suit = 0;
    other.prime = 0;
    other.order = 0;
    other.card_str.clear();
  }
  return *this;
}

