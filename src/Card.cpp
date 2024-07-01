#include "Card.h"

Card::Card(int val, char suit) : val{val}, suit{suit}{
  dealt=false;
}
Card::Card() : val{-1}, suit{'N'} {
  dealt=false;
}
