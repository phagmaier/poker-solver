#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H 

#include "Card.h"
#include "Deck.h"
#include <utility>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <stdexcept>

enum handStrength{
  High=0,
  Pair,
  Two_pair,
  Trips,
  Straight,
  Flush,
  Full_house,
  Quads,
  Straight_flush,
  Royal_flush
};

void print_vec(std::vector<Card*> &vec);

//because i'm dumb i create new card cause of the ace
//i generate a new 
void free_sorted(std::vector<Card*> &sorted);


//SORTING STUFF  
void swap_cards(std::vector<Card*> &cards, int i1, int i2);
void quicksort(std::vector<Card*> &cards, int start, int end);
int partition(std::vector<Card*> &cards, int start, int end);
std::vector<Card*> sort_cards(std::vector<Card*> &cards, std::pair<Card*, Card*> &hand);

//determine what hand is strongest between two hands 
//that have been given their max level
inline std::pair<handStrength, int> get_max(std::pair<handStrength,int> &one, std::pair<handStrength,int> &two){
  if (one.first == two.first){
    return one.second > two.second ? one : two;
  }
  return static_cast<int>(one.first) > static_cast<int>(two.first) ? one : two;
}

inline bool did_p1_win(std::pair<handStrength,int> &one, std::pair<handStrength,int> &two){
  if (one.first == two.first){
    return one.second > two.second ? true : false;
  }
  return static_cast<int>(one.first) > static_cast<int>(two.first) ? true : false;
}



std::pair<std::map<int,int>, std::map<char,int>> get_counts(std::pair<Card*,Card*> &hand, std::vector<Card*> &comm);

//ARRAY NEEDS TO BE SORTED FIRST
int get_top_five(std::vector<Card*> &sorted);

//function just for determining if the hand class is better 
//basically a > < for hand_strength
inline bool hand_class_better(std::pair<handStrength,int> &one, std::pair<handStrength,int> &two){
  return static_cast<int>(one.first) > static_cast<int>(two.first) ? true : false;
}

//dumbe helper functions to get best non paired card(s)
int get_one(std::map<int,int> &dic);
std::pair<int,int> get_two(std::map<int,int> &dic);
std::tuple<int,int,int> get_three(std::map<int,int> &dic);
std::tuple<int,int,int,int> get_four(std::map<int,int> &dic);
std::tuple<int,int,int,int,int> get_five(std::map<int,int> &dic);

//Determine if there was a pair and what class of pair
//i.e. all the way up to full house to no pair
std::pair<handStrength,int> get_pair(std::map<int,int> &dic);
std::pair<handStrength, int> get_flush(std::map<char,int> &dic, std::vector<Card*> &sorted);
std::pair<handStrength, int> get_straight(std::vector<Card*> &sorted);


std::pair<handStrength, int> get_hand_strength(std::pair<Card*,Card*> &hand, std::vector<Card*> &community);

//Will pass it the deck as a pointer 
//each players hand and a vector of all cards that 
//need to be included in the flop
//returns prct of the first hand winnng 
//if p2 then just do 1 - result
float get_chance_of_winning(std::pair<Card*,Card*> hand1, std::pair<Card*,Card*> hand2, Deck &deck, std::vector<Card*> &cards);




#endif 
