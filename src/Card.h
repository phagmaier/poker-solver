#ifndef CARD_H 
#define CARD_H 
#include <iostream>
class Card{
  
  public:
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

  private:
    int val;
    char suit;
    bool dealt;

};

#endif 
