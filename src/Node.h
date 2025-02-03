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

class Node{
public:
  const static std::vector<float> bet_sizes;
  const static std::vector<float> reRaiseSizes;
  const static float bb;
  const static std::vector<std::pair<Card,Card>> range1;
  const static std::vector<std::pair<Card,Card>> range2;
  const static float starting_stack1;
  const static float starting_stack2;
  const static bool short_stack;
  static std::unordered_map<Action, std::string> action_dic;
  static std::unordered_map<Street, std::string> street_dic;
  static unsigned int a;

  //also need to pass in the number of bets
  Node(Node *parent, Action action, bool player, Street street,
           float min_stack, float potsize, float cur_bet, int num_bets);
  ~Node();
  Node *parent;
  Action action;
  bool player; //first to act is false sta is true
  Street street;
  float min_stack;
  float potsize;
  float cur_bet;
  int num_bets;
  std::vector<std::vector<float>> action_prcts;

  std::vector<float> total_ev; 
  std::vector<float> total_av; 
  std::vector<std::vector<float>>total_regrets;
  std::vector<Node*> children;
  void print_node();
private:
  void make_children();
  Street get_next_street();
  bool is_terminal_node();
  //bool get_next_player();
  std::vector<float> get_valid_bet_sizes();
};



