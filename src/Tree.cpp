#include "Tree.h"
//have to init deck in {} because if not it inits it 
//as a default deck and then destrpys it twice don't want 
//that happening

//have these for when we have to sort 
//our five cards
std::map<char,int> Tree::charDic = {{'A',14}, {'K',13},{'Q',12},
    {'J',10}, {'T',10},{'9',9},{'8',8},{'7',7},{'6',6},
    {'5',5},{'4',4},{'3',3},{'2',2}};

  std::map<char, int> Tree::suiteDic = {
      {'s',1}, {'c',2}, {'h',3}, {'d',4}
    };

Tree::Tree(hand_pairs the_hand, 
       bool is_p1, float bb, float sb, std::vector<hand_pairs> p1_range,
       std::vector<hand_pairs> p2_range, Node::Street street,
        std::pair<float,float> stacks,  
        float last_bet, float potsize, Node::Action last_act,
        int num_bets,std::vector<std::pair<int,char>> dealt,
        std::pair<float,float> player_bets) : is_p1{is_p1}, 
        bb{bb}, sb{sb}, p1_range{p1_range}, p2_range{p2_range},
        deck{Deck()},
        head{init_head(is_p1, street, last_bet, potsize,stacks,last_act, num_bets, bb, p1_range,p2_range, player_bets)}
{
  hand = {Card(the_hand.first.first, the_hand.first.second), Card(the_hand.second.first,the_hand.second.second)};
  num_dealt = 0;
  for (std::pair<int,char> &cards : dealt){
    dealt_cards.push_back(deck.deal_specfic(cards.first, cards.second));
    ++num_dealt;
  }
    make_community_cards();
    //rankings = gen_dic();
  }

//also Init's matchups
std::vector<Head> Tree::init_head(bool is_p1, Node::Street street, float last_bet,float potsize,
                 std::pair<float,float> stacks, Node::Action last_act,
                 int num_bets, float bb,std::vector<hand_pairs> p1_range,
                 std::vector<hand_pairs> p2_range,
                 std::pair<float,float> player_bets){
  std::vector<Head> heads;
  for (hand_pairs &i : p1_range){
    for (hand_pairs &j : p2_range){
      if (!((i.first.first == j.first.first && i.first.second == j.first.second)
            || i.second.first == j.second.first && i.second.second == j.second.second)){
        heads.push_back(Head(is_p1,street,last_bet,potsize,stacks,last_act,num_bets,
                             bb, player_bets));
        matchups.push_back({i,j});
      } 
    }
  }
  return heads;
}

//also init the 'winners' vec which just is true if it goes to 
//showdown who won the hand
void Tree::make_community_cards(){
  for (std::pair<hand_pairs, hand_pairs> &hands : matchups){
    std::vector<Card*> temp;
    std::pair<Card*,Card*> h1= {deck.deal_specfic(hands.first.first),
                    deck.deal_specfic(hands.first.second)};
    
    std::pair<Card*,Card*> h2 = {deck.deal_specfic(hands.second.first),
      deck.deal_specfic(hands.second.second)};
    
    //deck.deal_specfic(hands.first.first);
    //deck.deal_specfic(hands.first.second);
    //deck.deal_specfic(hands.second.first);
    //deck.deal_specfic(hands.second.second);
  
  for (Card *i : dealt_cards){
   temp.push_back(i);
    i->card_dealt();
  }

  for (int i=0; i<5 - num_dealt; ++i){
      temp.push_back(deck.deal());
    }
    community.push_back(temp);
    winners.push_back(did_p1_win(get_hand_strength(h1, temp),get_hand_strength(h2, temp)));
    deck.reset_deck();
  }

}

void Tree::init_cards(std::vector<Card*> &cards){
  for (Card *i : cards){
    i->card_dealt();
  }
}

//eventually will have to run this with
//like 1k different types of random sample 
//where you constantly regenerate community
//meaning you'll have to clear community
void Tree::cfrm(){
  for (std::vector<Card*> &cards : community){
    init_cards(cards);

  }
}

