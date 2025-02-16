#include "Node.h"

const std::vector<float> Node::bet_sizes = {.25, .5, .75, 1, 1.25, 2};
const std::vector<float> Node::reRaiseSizes = {2, 3, 4, 5};
const float Node::bb = 1;
const float Node::starting_stack1 = 100;
const float Node::starting_stack2 = 100;
const bool Node::short_stack =
    Node::starting_stack1 > Node::starting_stack2 ? false : true;
unsigned int Node::a = 1;

// SETTING THE RANGES JUST FOR THIS EXAMPLE WE
// WILL ONLY BE PLAYING ACES AND KINGS
const std::vector<std::pair<Card, Card>> Node::range1 = {
    {Card(12, 0), Card(12, 1)}, {Card(11, 0), Card(11, 1)}};

const std::vector<std::pair<Card, Card>> Node::range2 = {
    {Card(12, 0), Card(12, 1)}, {Card(11, 0), Card(11, 1)}};

const unsigned int Node::range1_size = Node::range1.size();
const unsigned int Node::range2_size = Node::range2.size();

std::unordered_map<Action, std::string> Node::action_dic{
    {FOLD, "FOLD"},   {CHECK, "CHECK"},           {CHECKBACK, "CHECK BACK"},
    {CALL, "CALL"},   {CALLALLIN, "CALL ALL IN"}, {BET, "BET"},
    {RAISE, "RAISE"}, {ALLIN, "ALL IN"}};
std::unordered_map<Street, std::string> Node::street_dic{
    //{PREFLOP,"PREFLOP"},//MAYBE LATER ADD PREFLOP
    {FLOP, "FLOP"},
    {TURN, "TURN"},
    {RIVER, "RIVER"}};

Node::Node(Node *parent, Action action, bool player, Street street,
           float min_stack, float potsize, float cur_bet, int num_bets)
    : parent(parent), action(action), player(player), street(street),
      min_stack(min_stack), potsize(potsize), cur_bet(cur_bet),
      num_bets(num_bets) {
  Node::a++;
  if (!is_terminal_node()) {
    make_children();
  }
  int num_cards = !player ? Node::range1_size : Node::range2_size;
  for (int i = 0; i < num_cards; ++i) {
    total_ev.push_back(0.0f);
    total_av.push_back(0.0f);
    total_regrets.push_back(0.0f);
  }
  set_actions();
}

// SAY YOU START ON THE FLOP NO PREV ACTION TAKEN
// THEN YOU HAVE MULTIPLE HEAD NODES AND NEED TO SET ALL POSSIBLE ACTIONS
Node::Node(Action action, bool player, Street street, float min_stack,
           float potsize, float cur_bet, int num_bets, float uniform)
    : parent(nullptr), action(action), player(player), street(street),
      min_stack(min_stack), potsize(potsize), cur_bet(cur_bet),
      num_bets(num_bets) {
  Node::a++;

  if (!player) {
    for (int i = 0; i < Node::range1_size; ++i) {
      action_prcts1.push_back(uniform);
    }
    for (int i = 0; i < Node::range2_size; ++i) {
      action_prcts2.push_back(1);
    }

  } else {
    for (int i = 0; i < Node::range2_size; ++i) {
      action_prcts2.push_back(uniform);
    }
    for (int i = 0; i < Node::range1_size; ++i) {
      action_prcts1.push_back(1);
    }
  }

  if (!is_terminal_node()) {
    make_children();
  }
  int num_cards = !player ? Node::range1_size : Node::range2_size;
  for (int i = 0; i < num_cards; ++i) {
    total_ev.push_back(0.0f);
    total_av.push_back(0.0f);
    total_regrets.push_back(0.0f);
  }
}

// In the future please chnage this so it's not just a bunch of if statments
// it's really shitty code
void Node::make_children() {
  std::vector<float> sizes = get_valid_bet_sizes();

  // NOW I NEED TO MAKE ALL THE NON BETS
  // 1. CALL
  // 2. CHECK
  // 3. CHECKBACK
  // 4. CALLALLIN
  // 5. ALLIN
  // 6. FOLD

  if (action == BET || action == RAISE) {
    children.emplace_back(new Node(this, CALL, !player, street,
                                   min_stack - cur_bet, potsize + (cur_bet * 2),
                                   0, 0));
    children.emplace_back(
        new Node(this, FOLD, !player, street, min_stack, potsize, 0, 0));
    children.emplace_back(new Node(this, ALLIN, !player, street, min_stack,
                                   potsize, min_stack, 0));
    for (float bet : sizes) {
      children.emplace_back(new Node(this, RAISE, !player, street, min_stack,
                                     potsize, bet, num_bets + 1));
    }
  } else if (action == CHECK) {
    children.emplace_back(
        new Node(this, CHECKBACK, !player, street, min_stack, potsize, 0, 0));
    children.emplace_back(new Node(this, ALLIN, !player, street, min_stack,
                                   potsize, min_stack, 0));
    for (float bet : sizes) {
      children.emplace_back(
          new Node(this, BET, !player, street, min_stack, potsize, bet, 1));
    }
  }

  else if (action == CHECKBACK) {
    bool newP = !player ? player : !player;
    Street new_street = get_next_street();
    children.emplace_back(
        new Node(this, CHECK, newP, new_street, min_stack, potsize, 0, 0));
    children.emplace_back(new Node(this, ALLIN, newP, new_street, min_stack,
                                   potsize, min_stack, 0));
    for (float bet : sizes) {
      children.emplace_back(
          new Node(this, BET, newP, new_street, min_stack, potsize, bet, 1));
    }

  } else if (action == CALL) {
    bool newP = !player ? player : !player;
    Street new_street = get_next_street();
    children.emplace_back(new Node(this, CHECK, newP, new_street,
                                   min_stack - cur_bet, potsize + (cur_bet * 2),
                                   0, 0));
    children.emplace_back(new Node(this, ALLIN, newP, new_street,
                                   min_stack - cur_bet, potsize + (cur_bet * 2),
                                   min_stack - cur_bet, 0));
    for (float bet : sizes) {
      children.emplace_back(new Node(this, BET, newP, new_street,
                                     min_stack - cur_bet,
                                     potsize + (cur_bet * 2), bet, 1));
    }
  } else if (action == ALLIN) {
    children.emplace_back(
        new Node(this, FOLD, !player, street, min_stack, potsize, 0, 0));
    children.emplace_back(new Node(this, CALLALLIN, !player, street, 0,
                                   potsize + (min_stack * 2), min_stack, 0));
  } else {
    std::cout << "PRINTING IN MAKE CHILDREN\n";
    std::cout << "IF THIS IS PRINTING IDK WHY PROBABLY AN ERROR\n";
    std::cout << "IT'S PART WHERE I DO THE NON BETS CHECK LOGIC\n";
  }
}

Street Node::get_next_street() {
  if (action == CHECKBACK || action == CALL) {
    // Street new_street;
    switch (street) {
    /*
    //REMOVING PREFLOP FOR NOW
    case PREFLOP:
      new_street = FLOP;
      break;
    */
    case FLOP:
      return TURN;
      break;
    case TURN:
      return RIVER;
      break;
    default:
      std::cerr << "THIS SHOULD NEVER PRINT PASSED A RIVER STREET\n";
    }
  }
  return street;
}

bool Node::is_terminal_node() {
  if (action == FOLD || action == CALLALLIN) {
    return true;
  }
  if (street == RIVER && (action == CHECKBACK || action == CALL)) {
    return true;
  }
  return false;
}

std::vector<float> Node::get_valid_bet_sizes() {
  if (num_bets >= 3 || action == ALLIN) {
    return {};
  }
  std::vector<float> vec;
  float limit = min_stack * .85; // if 85% of stack just go all in so not valdid
  if (action != BET && action != RAISE) {
    float pot = potsize ? potsize : Node::bb;
    for (const float i : Node::bet_sizes) {
      float size = i * pot;
      if (size >= Node::bb && size < limit) {
        vec.push_back(size);
      }
    }
  }

  else {
    for (const float i : Node::reRaiseSizes) {
      float size = i * cur_bet;
      if (size < limit) {
        vec.push_back(size);
      }
    }
  }
  return vec;
}

void Node::print_node() {
  std::cout << "STREET: " << Node::street_dic[street];
  std::cout << " ACTION: " << Node::action_dic[action] << " ";
  std::cout << "BET SIZE: " << cur_bet << "\n";
}

Node::~Node() {
  for (Node *node : children) {
    if (node) {
      delete node;
    }
  }
}

void Node::set_actions() {
  float uniform = 1.0f / (float)parent->children.size();
  if (!player) {
    for (float i : parent->action_prcts1) {
      action_prcts1.push_back(uniform * i);
    }
    action_prcts2 = parent->action_prcts2;
  } else {
    for (float i : parent->action_prcts2) {
      action_prcts2.push_back(uniform * i);
    }
    action_prcts1 = parent->action_prcts1;
  }
}



void Node::update_actions() {
  return;
  std::vector<float> regrets(Node::range1_size, 0.0f);
  if (!parent) {
    std::cerr << "UPDATE ACTION FUNC NOT  IMPLIMENTED FOR HEAD NODES YET\n";
    std::cerr << "THE TREE NEEDS TO TAKE CARE OF THIS\n";
    std::cerr << "TREE TAKES THE SUM OF \n";
    return;
  }
  if (!player) {
    for (Node *node : parent->children) {
      int regrets = 0;
      for (int hand = 0; hand < Node::range1_size; ++hand) {
        //regrets.push_back()
      }
    }

    return;
  }
  // do it for plyar i.e. second to act
}
