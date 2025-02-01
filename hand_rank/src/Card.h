#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

struct Card {
  static const unsigned int primes[13];   
  static std::string card_array[52];   

  Card(unsigned int val, unsigned int suit);
  Card();
  Card(const Card& other);
  Card& operator=(const Card& other);
  Card(Card&& other) noexcept;
  Card& operator=(Card&& other) noexcept;

  unsigned int val;
  unsigned int suit;
  unsigned int prime;
  unsigned int short order;
  std::string card_str;
  inline void print_card(){std::cout<<card_str;}
};

