#ifndef CARD_H 
#define CARD_H 
#include <iostream>
#include <map>
#include <string>
class Card{
  
  public:
    static std::map<int, std::string> val_dic;
    //static std::map<int, char> suit_dic;

    Card(int val, char suit);
    Card();
  
    inline int get_val(){
      return val;
    }
    
    inline char get_suit(){
      return suit;
    }

    inline void print_card(){
      std::cout << val << " " << suit << "\n";
  }

    inline bool get_dealt(){return dealt;}

    inline void card_dealt(){dealt=true;}
    inline void reset(){dealt=false;}
    inline std::string *get_string(){return &card_string;}

  inline bool operator==(const Card& other) const{return (this->val == other.val && this->suit == other.suit) ? true : false;}
  inline bool operator>(const Card& other) const{return (this->val*1000 + (int)this->suit > other.val*1000 + (int)other.suit) ? true : false;}
  inline bool operator<(const Card& other) const{return (this->val*1000 + (int)this->suit < other.val*1000 + (int)other.suit) ? true : false;}

  private:
    int val;
    char suit;
    bool dealt;
    std::string card_string;

};

#endif 
