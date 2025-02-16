#include "Deck.h"
#include "Node.h"
#include "hand_evaluator.h"

void print_nodes(Node *node) {
  node->print_node();
  for (Node *n : node->children) {
    print_nodes(n);
  }
}

void print_nodes(Node &node) {
  node.print_node();
  for (Node *n : node.children) {
    print_nodes(n);
  }
}

bool is_equal(std::pair<Card, Card> &one, std::pair<Card, Card> &two,
              Card &check) {
  if (one.first.order == check.order) {
    return true;
  }
  if (one.second.order == check.order) {
    return true;
  }
  if (two.first.order == check.order) {
    return true;
  }
  if (two.second.order == check.order) {
    return true;
  }
  return false;
}

void get_hand(Deck &deck, Card *player) {
  player[0] = deck.deal_random();
  player[1] = deck.deal_random();
}
void get_comm(Deck &deck, Card *p1, Card *p2) {
  for (int i = 2; i < 7; ++i) {
    Card tmp = deck.deal_random();
    p1[i] = tmp;
    p2[i] = tmp;
  }
}

void print_result(std::pair<Rank, unsigned int> &rank) {
  switch (rank.first) {
  case NOTHING:
    std::cout << "NOTHING I.E ERROR\n";
    break;
  case HIGH:
    std::cout << "HIGH CARD: " << rank.second << "\n";
    break;
  case PAIR:
    std::cout << "PAIR: " << rank.second << "\n";
    break;
  case TWO:
    std::cout << "TWO PAIR: " << rank.second << "\n";
    break;
  case TRIPS:
    std::cout << "TRIPS: " << rank.second << "\n";
    break;
  case STRAIGHT:
    std::cout << "STRAIGHT: " << rank.second << "\n";
    break;
  case FLUSH:
    std::cout << "FLUSH: " << rank.second << "\n";
    break;
  case FULL:
    std::cout << "FULL HOUSE: " << rank.second << "\n";
    break;
  case QUADS:
    std::cout << "QUADS: " << rank.second << "\n";
    break;
  case STRAIGHT_FLUSH:
    std::cout << "STRAIGHT FLUSH: " << rank.second << "\n";
    break;

  default:
    std::cout << "ERROR\n";
  }
}

void print_hand(Card *cards, std::pair<Rank, unsigned int> &rank) {
  for (int i = 0; i < 7; ++i) {
    cards[i].print_card();
    std::cout << " ";
  }
  std::cout << "\n";
  print_result(rank);
}

void test(Deck &deck) {
  unsigned int c = 1;
  unsigned int wins = 0;
  unsigned int loses = 0;
  unsigned int ties = 0;
  unsigned int total = 1000000;
  Card p1[7];
  Card p2[7];
  for (unsigned int i = 0; i < total; ++i) {
    deck.reset();
    get_hand(deck, p1);
    get_hand(deck, p2);
    get_comm(deck, p1, p2);
    std::pair<Rank, unsigned int> one = hand_evaluator(p1);
    std::pair<Rank, unsigned int> two = hand_evaluator(p2);

    int result = get_p1_result(one, two);
    if (result == 1) {
      ++wins;
    } else if (result == -1) {
      ++loses;
    } else {
      ++ties;
    }
    /*
    #ifdef ((i + 1) % 100000 == 0) {
      std::cout << "-----------------------------------------------------\n";
      std::cout << "DISPLAY: " << c << "\n";
      std::cout << "PRINTING A RANDOM HAND\n";
      print_hand(p1, one);
      print_hand(p2, two);
      std::cout << "-----------------------------------------------------\n";
      ++c;
    }
    */
  }
  std::cout << "TOTAL PRINTED: " << c << '\n';
  float win_prct = (float)wins / (float)total;
  float tie_prct = (float)ties / (float)total;
  std::cout << "PERCENTAGE OF GAMES WON: " << win_prct * 100.0f << "\n";
  std::cout << "PERCENTAGE OF GAMES TIED: " << tie_prct * 100.0f << "\n";
}

int main() {
  /*
  Node root = Node(CHECK, true, FLOP,
                  100, Node::bb * 1.5, 0, 0,.3);
  //print_nodes(root);
  std::cout << Node::a << "\n";
  */

  Deck deck = Deck();
  std::string c1 = "AH";
  std::string c2 = "KD";
  std::string c3 = "2S";
  std::string c4 = "5C";
  test(deck);
  return 0;
}
