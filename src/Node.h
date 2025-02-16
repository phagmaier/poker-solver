#pragma once
#include <vector>
#include "Card.h"
#include <unordered_map>
#include <string>

enum Action{
  FOLD,
  CHECK,
  CHECKBACK,
  CALL,
  CALLALLIN,
  BET,
  RAISE,
  ALLIN
};

enum Street{
  //PREFLOP,//NOT GONNA DO PREFLOP ALREADY TOO BIG AS IS
  FLOP,
  TURN,
  RIVER
};

//might actually need to track both players
//ev and av but i'm not 100% sure
//or just use the greater size for both idk
class Node{
public:
  const static std::vector<float> bet_sizes;
  const static std::vector<float> reRaiseSizes;
  const static float bb;
  const static std::vector<std::pair<Card,Card>> range1;
  const static std::vector<std::pair<Card,Card>> range2;
  const static unsigned int range1_size;
  const static unsigned int range2_size;
  const static float starting_stack1;
  const static float starting_stack2;
  const static bool short_stack;
  static std::unordered_map<Action, std::string> action_dic;
  static std::unordered_map<Street, std::string> street_dic;
  static unsigned int a;

  Node(Node *parent, Action action, bool player, Street street,
           float min_stack, float potsize, float cur_bet, int num_bets);

  Node(Action action, bool player, Street street,
           float min_stack, float potsize, float cur_bet, int num_bets,float uniform);

  ~Node();
  Node *parent;
  Action action;
  bool player; //first to act is false sta is true
  Street street;
  float min_stack;
  float potsize;
  float cur_bet;
  int num_bets;

  //ALL THIS NEEDS TO BE SET BY THE PARENTS ONLY THE HEAD
  //NODES NEED TO BE SET MANUALLY
  //Head nodes the prct will be calculated the same way
  //only you take the number of head in the head vector
  std::vector<float> action_prcts1; //prct of taking the action for each card
  std::vector<float> action_prcts2; 
  std::vector<float> total_ev; //combine both cum1 and cum2
  std::vector<float> total_av; //combine only either cum1 or cum2
  std::vector<float>total_regrets;
  std::vector<Node*> children;
  //END OF WHERE THESE NEED TO BE SET BY PARENTS
  void print_node();
  void set_values();
  void set_head_actions(float uniofrm);

private:
  void make_children();
  Street get_next_street();
  bool is_terminal_node();
  std::vector<float> get_valid_bet_sizes();
  void set_actions();
  //can make parallel by either passing 
  //an index and having a thread update each card
  //or just giving each thread a node idk
  void update_actions();
};


