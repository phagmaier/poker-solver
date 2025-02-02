#pragma once
#include "make_dics.h"
#include <utility>
#include "Card.h"

enum Rank{
  NOTHING,
  HIGH,
  PAIR,
  TWO,
  TRIPS,
  STRAIGHT,
  FLUSH,
  FULL,
  QUADS,
  STRAIGHT_FLUSH
};

const unsigned int get_hash(Card *cards,std::vector<unsigned int> &indexes);
unsigned int check_flush(Card *cards, const unsigned int hash, std::vector<unsigned int> &indexes);
void set_best(std::pair<Rank, unsigned int> &cur, std::pair<Rank, unsigned int> &best);
Rank get_rank(const unsigned int val);
std::pair<Rank, unsigned int> hand_evaluator(Card *cards);
int get_p1_result(std::pair<Rank,unsigned int> &p1, std::pair<Rank,unsigned int> &p2);
