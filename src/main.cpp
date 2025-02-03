#include "Node.h"

void print_nodes(Node *node){
  node->print_node();
  for (Node *n : node->children){
    print_nodes(n);
  }
}

void print_nodes(Node &node){
  node.print_node();
  for (Node *n : node.children){
    print_nodes(n);
  }
}



int main(){
  Node root = Node(nullptr, CHECK, true, FLOP, 
                  100, Node::bb * 1.5, 0, 0);
  //print_nodes(root);
  std::cout << Node::a << "\n";
  return 0;
}
