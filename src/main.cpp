#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Node.h"

int countTwo(Node *node){
    if (!node) return 0;

    int count = 1; // Count the current node
    for (Node &child : node->children){
        count += countTwo(&child);
    }
    return count;
}

int main(){
  Node node(true, Node::FLOP, 0, 1, {100,100}, Node::CHECK, 0, NULL);
  int x = countTwo(&node);
  std::cout << x << "\n";
  return 0;
}

