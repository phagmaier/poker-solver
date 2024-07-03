#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Node.h"
#include "Tree.h"
#include "helperfunctions.h"
#include <utility>
#include <map>
#include <string>



int main(){
  Deck deck = Deck();
  deck.deal_specfic(14,'D')->print_card();
    return 0;
}

