/*
 *
 *
 *
 *
 * GOING TO have TO DO ONE CARD AT A TIME
 * THIS WILL PROBABLY REQUIRE YOU CONSTANTLY 
 * PASSING AN INDEX WHEN YOU GET THERE THIS 
 * WILL MAKE IT EASIER TO THREAD THOUGH AND KEEP 

 * TRACK OF ALL THE PROGRAMS SO EACH NODE WILL 
 * BE THE STRAT FOR ONE CARD AND ONE CARD ONLY 
 * FOR BOTH PLAYER ONE AND PLAYER 2
*/

#ifndef NODE_H
#define NODE_H 
#include <vector>
#include <utility>
#include "Card.h"
#include <string>


//using doubleVec = std::vector<std::vector<double>>;
//using pairVec = std::vector<std::pair<double, double>>;
  
//PREVIOUS ACTIONS:
//K = CHECK 
//B = BET 
//A = ALL_IN
//F = FOLD
//C = CALL
class Node{
  public:
    
    enum Action{
      CHECK,
      BET,
      CALL,
      FOLD,
      ALLIN};
    enum Street{
      DONE = -1,
      FLOP,
      TURN,
      RIVER};

    //DON'T WANT CONSTANT RERAISING SO NUM BETS IS 
    //HOW MANY BETS WE'VE HAD 
    
    //
    //You actually need both players stack sizes
    Node(bool p1,Street street, float prev_bet, float potsize, 
         std::pair<float,float> stacks, Action prev_act, 
         int num_bets, Node *parent);
    Node();
    
    //USE THIS ONE FOR THE FIRST NODE SINCE YOU HAVE NO PARENT 
    // you will have to determine how many nodes you will make before in order 
    // to make this 
    Node(bool p1, Street street, float prev_bet, float potsize, 
        std::pair<float,float> stacks,
        Action prev_act, int num_bets,Node *parent, float strat);
    static float blind;
    static std::vector<float> default_bet_sizes;
    std::vector<Node> children;
    inline void setblind(float b){Node::blind = b;}
    inline void set_strat(float s){strat=s;}
    friend Street operator+(Street s, int);
    
  //private:
    float potsize; //as a representation of bb's
    float stack; //number of bb's can have a fraction 
    float strat;
    float ev;
    Node *parent;
    Street get_next_street(Action prev, Action curr, Street street);
}; 

#endif 
