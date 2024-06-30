#include "helperfunctions.h"

std::tuple<int,int,int> get_three(std::map<int,int> &dic){
  int one=0;
  int two=0;
  int three = 0;
  for (auto &i : dic){
    if (i.second ==1){
      if (i.first > one){
        three = two;
        two = one;
        one = i.first;
      }
      else if (i.first > two){
        three = two;
        two = i.first;
      }
      else if (i.first > three){
        three = i.first;
      }
    }
  }
  return {one,two,three};
}

int get_top_five(std::vector<Card> sorted){
  int count =0;
  int scaler[] = {10000,1000,100,10,1};
  for (int i=0; i<5; ++i){
    count += sorted[i].get_val() * scaler[i];
  }
  return count;
}

std::pair<int,int> get_two(std::map<int,int> &dic){
  int one=0;
  int two=0;

  for (auto &i : dic){
    if (i.second == 1){
      if (i.first > one){
        two = one;
        one = i.first;
      }
      else if (i.first > two){
        two = i.first;
      }
    }
  }
  return {one,two};
}

int get_one(std::map<int,int> &dic){
  int one=0;

  for (auto &i : dic){
    if (i.second == 1){
      if (i.first > one){
        one = i.first;
      }
    }
  }
  return one;
}



std::tuple<int,int,int,int> get_four(std::map<int,int> &dic){
  int one=0;
  int two=0;
  int three = 0;
  int four = 0;
  for (auto &i : dic){
    if (i.second ==1){
      if (i.first > one){
        four = three;
        three = two;
        two = one;
        one = i.first;
      }
      else if (i.first > two){
        four = three;
        three = two;
        two = i.first;
      }
      else if (i.first > three){
        four = three;
        three = i.first;
      }
      else if (i.first > four){
        four = i.first;
      }
    }
  }
  return {one,two,three,four};
}

std::tuple<int,int,int,int,int> get_five(std::map<int,int> &dic){
  int one=0;
  int two=0;
  int three = 0;
  int four = 0;
  int five = 0;
  for (auto &i : dic){
    if (i.second ==1){
      if (i.first > one){
        five = four;
        four = three;
        three = two;
        two = one;
        one = i.first;
      }
      else if (i.first > two){
        five = four;
        four = three;
        three = two;
        two = i.first;
      }
      else if (i.first > three){
        five = four;
        four = three;
        three = i.first;
      }
      else if (i.first > four){
        five = four;
        four = i.first;
      }
      else if (i.first > four){
        five = i.first;
      }

    }
  }
  return {one,two,three,four,five};
}


std::pair<std::map<int,int>, std::map<char,int>> get_counts(std::pair<Card,Card> &hand, std::vector<Card> comm){
  std::map<int,int> pair_count;
  std::map<char, int> suit_count;
  pair_count[hand.first.get_val()] +=1;
  pair_count[hand.second.get_val()] +=1;
  
  suit_count[hand.first.get_suit()] +=1;
  suit_count[hand.second.get_suit()] +=1;

  for (Card &c : comm){
    pair_count[c.get_val()] +=1;
    suit_count[c.get_suit()] +=1;
  }
  return {pair_count, suit_count};

}


void swap_cards(std::vector<Card> &cards, int i1, int i2){
  Card temp = cards[i1];
  cards[i1] = cards[i2];
  cards[i2] = temp;
}

void quicksort(std::vector<Card> &cards, int front, int back){
  if (front >= back){
    return;
  }
  int val = cards[back].get_val();
  int i=front;
  int j=back-1;
  while (true){
    while(cards[i].get_val() > val && i<=j){
      ++i;
    }
    while(cards[j].get_val() < val && i<=j){
      --j;
  }
    if (i >=j){
      break;
    }
  swap_cards(cards, i,j);
    ++i;
    --j;
}
  swap_cards(cards, i,back);
  quicksort(cards,front, i-1);
  quicksort(cards, i+1, back);
}


std::vector<Card> sort_cards(std::vector<Card> &cards, std::pair<Card, Card> &hand){
  std::vector<Card> new_cards;
  new_cards.push_back(hand.first);
  new_cards.push_back(hand.second);
  for (Card &c : cards){
    if (c.get_val() == 14){
      new_cards.push_back(Card(1,c.get_suit()));
    }
    new_cards.push_back(c);
  }
  quicksort(new_cards,0,new_cards.size()-1);
  return new_cards;
}

//you actually need to account for all 5 cards 
//because they have have the same flush as you
std::pair<handStrength, int> get_flush(std::map<char,int> &dic, std::vector<Card> &sorted){
  bool flush = false;
  char suit;
  for (auto &i : dic){
    if (i.second >= 5){
      flush = true;
      suit = i.first;
      break;
    }
      }
  
  if (!flush){
      return {High, 0};
    }

  std::vector<Card> same_suit;
  for (Card &i : sorted){
    if (i.get_suit() == suit){
      same_suit.push_back(i);
    }
  }

  quicksort(same_suit, 0, same_suit.size()-1);

      std::pair<handStrength, int> straight = get_straight(same_suit);
  if (straight.first){
    if (same_suit[0].get_val() == 14){
      return {Royal_flush, 0};
    }
    else {
      return {Straight_flush, straight.second};
  }
  }
  //get top 5 gives sum of 
  return {Flush, get_top_five(same_suit)};
  
}

std::pair<handStrength, int> get_straight(std::vector<Card> &sorted){
  for (int i=0; i<=sorted.size()-5;++i){
    int high = sorted[i].get_val();
    int prev = high;
    bool straight = true;
    for (int j=i+1; j<i+5; ++j){
     if (prev-1 != sorted[j].get_val()){
        straight = false;
        break;
      }
      --prev;
    }
    if (straight){
      return {Straight, high};
    }
  }
  return {High, 0};
}


std::pair<handStrength, int> get_hand_strength(std::pair<Card,Card> &hand, std::vector<Card> &community){
  std::pair<handStrength,int> strength;
  std::pair<std::map<int,int>,std::map<char, int>> maps = get_counts(hand, community);
  std::pair<handStrength,int> pair_val= get_pair(maps.first);
  std::vector<Card> sorted = sort_cards(community,hand);
  std::pair<handStrength, int> flush= get_flush(maps.second, sorted);
  strength = get_max(pair_val, flush);
  std::pair<handStrength, int> straight = get_straight(sorted);
  strength = get_max(strength,straight);
  return strength;    
}


std::pair<handStrength,int> get_pair(std::map<int,int> &dic){
  int pair1 = 0;
  int pair2 = 0;
  int trips = 0;
  int quads = 0;
  for (auto &c : dic){
    if (c.second == 4){
      return {Quads, c.first};
    }
    else if (c.second == 3 && c.first > trips){
      trips = c.first;
    }
    //could have bored with 2 trips so have to do >=
    else if (c.second >= 2){
      if (c.first > pair1){
        pair2 = pair1;
        pair1 = c.first;
      }
      else if(c.first > pair2){
        pair2 = c.first;
      }
    }
  }

  if (trips && pair1){

    return {Full_house, trips * 100 + pair1*10};
  }
  if (trips){
    std::pair<int,int> temp = get_two(dic);
    return {Trips, trips *100 + temp.first * 10 + temp.second};
  }
  if(pair1 && pair2){
    return {Two_pair, pair1 * 100 + pair2 * 10 + get_one(dic)};
  }
  if (pair1){
    auto[one,two,three,four] = get_four(dic);
    return {Pair, pair1*10000 + one * 1000 + two * 100 + three * 10 + four};
  }
   auto[one,two,three,four,five] = get_five(dic); 
  return {High, one*10000+two*1000+three*100+four*10+five};
}
