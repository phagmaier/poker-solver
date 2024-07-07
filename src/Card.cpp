#include "Card.h"


std::map<int, std::string> Card::val_dic{{14,"A"},{13,"K"},
  {12, "Q"}, {11, "J"}, {10, "T"}, {9, "9"}, {8, "8"},
  {7, "7"}, {6, "6"}, {5, "5"}, {4, "4"}, {3, "3"}, {2, "2"}
};
//std::map<int, char> Card::suit_dic;


Card::Card(int val, char suit) : val{val}, suit{suit}{
  dealt=false;
  //card_string = std::to_string(val) + suit;
  card_string = val_dic[val] + suit;
}
Card::Card() : val{-1}, suit{'N'} {
  dealt=false;
   //card_string = std::to_string(val) + suit; 
    card_string = val_dic[val] + suit;
}
