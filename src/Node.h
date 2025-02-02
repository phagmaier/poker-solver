#pragma once
#include <vector>
#include "Card.h"
#include <utility>

/*
 * So my thought is you don't need to store things like
 * each cards ev for each decision because you'll be calulating
 * that at the same time like I don't need to store
 * the temporary regrets I'll just do that as I go right?
 * and once I calculate it for one I update it and i'm done
 * cause you do it 
*/

enum Player{
  FTA, //First to act
  STA //Second to act
};

enum Action{
  FOLD,
  CHECK,
  CALL,
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
  //manually put in all in and zero
  //zero will be a check or a fold
  const static std::vector<float> bet_sizes;
  static float bb;
  static std::vector<std::pair<Card,Card>> range1;
  static std::vector<std::pair<Card,Card>> range2;
  static Player short_stack;


  Node(Node *prnt, Action act, Player p,
           Street s, float stk, float pot, 
       float cur_bet, int num_bets);
  Node *parent;
  Action action;
  Player player;
  Street street;
  float min_stack;
  float potsize;
  float cur_bet;
  std::vector<std::vector<float>> action_prcts;

  std::vector<float> total_ev; 
  std::vector<float> total_av; 
  std::vector<std::vector<float>>total_regrets;

  std::vector<Node*> children;
private:
  std::vector<float> get_all_bets();
  void make_terminal_nodes(Action a, 
                           Player plyr, Street str, float min,
                           float money, float last_best);
};



