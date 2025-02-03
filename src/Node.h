#pragma once
#include <vector>
#include "Card.h"
#include <utility>

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
  PREFLOP,
  FLOP,
  TURN,
  RIVER
};

class Node{
public:
  const static std::vector<float> bet_sizes;
  static float bb;
  static std::vector<std::pair<Card,Card>> range1;
  static std::vector<std::pair<Card,Card>> range2;
  static float starting_stack1;
  static float starting_stack2;
  static bool short_stack;

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
private:
  void make_children();
  Street get_next_street();
  bool is_terminal_node();
  bool get_next_player();
  std::vector<float> get_valid_bet_sizes();
};



