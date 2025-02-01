#include "hand_evaluator.h"

constexpr unsigned int NUM_COMBOS = 21;
constexpr unsigned HANDS_WORSE_STRAIGHT = 5863;
constexpr unsigned int HIGH_CARD_NUM = 1287;
constexpr unsigned int ONE_PAIR_NUM= 2860 + HIGH_CARD_NUM;
constexpr unsigned int TWO_PAIR_NUM= 858 + ONE_PAIR_NUM;
constexpr unsigned int TRIPS_NUM = 858 + TWO_PAIR_NUM;
constexpr unsigned int FULL_HOUSE_NUM = 156 + TRIPS_NUM;
constexpr unsigned int QUADS_NUM = 156 + FULL_HOUSE_NUM;



std::unordered_map<unsigned int, unsigned int> pair_dic = make_pairs();
std::unordered_map<unsigned int, unsigned int> straights_dic = make_straights();
std::unordered_map<unsigned int, unsigned int> flush_dic = make_flushes();
std::vector<std::vector<unsigned int>> combos_dic = make_combos();

const unsigned int get_hash(Card *cards,std::vector<unsigned int> &indexes){

  return cards[indexes[0]].prime * cards[indexes[1]].prime * cards[indexes[2]].prime * cards[indexes[3]].prime * cards[indexes[4]].prime;
}

unsigned int check_flush(Card *cards, const unsigned int hash, std::vector<unsigned int> &indexes){
  if(cards[indexes[0]].suit & cards[indexes[1]].suit & cards[indexes[2]].suit & cards[indexes[3]].suit & cards[indexes[4]].suit){
    return flush_dic[hash];
  }
  return 0;
}

void set_best(std::pair<Rank, unsigned int> &cur, std::pair<Rank, unsigned int> &best){
  if (cur.first < best.first){
    return;
  }
  if (cur.first > best.first){
    best.first = cur.first;
    best.second = cur.second;
    return;
  } 
  if (cur.second > best.second){
    best.second = cur.second;
    return;
  }
  
}

Rank get_rank(const unsigned int val){
  if (val <= HIGH_CARD_NUM){
    return HIGH;
  }
  if (val <= ONE_PAIR_NUM){
    return PAIR;
  }
  if (val <= TWO_PAIR_NUM){
    return TWO;
  }
  if (val <= TRIPS_NUM){
    return TRIPS;
  }
  if (val <= FULL_HOUSE_NUM){
    return FULL;
  }
  return QUADS;
  
}

std::pair<Rank, unsigned int> hand_evaluator(Card *cards){
  std::pair<Rank,unsigned int> best = {NOTHING,0};
  for (int i=0; i<NUM_COMBOS; ++i){
    std::pair<Rank,unsigned int> cur= {NOTHING,0};
    std::vector<unsigned int> indexes = combos_dic[i];
    unsigned int hash =get_hash(cards,indexes);
    unsigned int flush = check_flush(cards,hash,indexes);
    unsigned int straight = straights_dic[hash];
    if (straight && flush){
      cur = {STRAIGHT_FLUSH,straight};
      set_best(cur,best);
      continue;
    }

    unsigned int val = pair_dic[hash];
    Rank rank = get_rank(val);
    if (flush){
      if (rank > FLUSH){
        cur = {rank,val};
      }
      else{
        cur = {FLUSH,flush};
      }
    }
    else if (straight){
      if (rank > STRAIGHT){
        cur = {rank,val};
      }
      else{
        cur = {STRAIGHT,straight};
      }
    }
    else{
      cur = {rank,val};
    }

    set_best(cur,best);
  }
  return best;
}

int get_p1_result(std::pair<Rank,unsigned int> &p1, std::pair<Rank,unsigned int> &p2){
  if (p1.first > p2.first){
    return 1;
  }
  if (p1.first < p2.first){
    return -1;
  } 
  if (p1.second > p2.second){
    return 1;
  }
  if (p1.second < p2.second){
    return -1;
  }
  //tie
  return 0;
}
