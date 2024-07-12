//by the way have to make it so the solve 
//stack sizes must always be greater than or equal to 1
#ifndef NODE_H
#define NODE_H 

#include <vector>
#include <string>
#include <map>
#include "Card.h"
#include <stdexcept>
using doubleDic = std::map<std::pair<Card*,Card*>,std::map<std::pair<Card*,Card*>,float>>; 
using matchDic = std::map<std::pair<Card*,Card*>, std::vector<std::pair<Card*,Card*>>>;

enum Street{
  DONE = -1,
  FLOP,
  TURN,
  RIVER
};

enum Action{
  FOLD,
  CHECK,
  CALL,
  BET,
  ALLIN
};

Street& operator++(Street& s);
  

class Node{
  public:
    static std::map<Street, std::string> street_dic;
    static std::map<Action, std::string> action_dic;
    static std::map<std::pair<Card*,Card*>,float> num_iterations_1;
    static std::map<std::pair<Card*,Card*>,float> num_iterations_2;

    //for when head makes node 
    // won't know the number of children
    Node();
    Node(bool p1, Street street, Action action, std::vector<Node*> children,
         float potsize, float bet, float stack,int num_bets);

    inline void set_children(std::vector<Node*> childs){children = childs;}
    
    bool p1;
    Street street;
    Action action;
    float potsize;
    float bet;
    float stack;
    
    //arr of arr of nodes representing children 
    // need 2d becuase need it for Nodes that come 
    // after for each card need to be pointer 
    // cause AD will need child node for AC and so will 
    // other cards in range 
    std::vector<Node*> children;

    std::map<std::pair<Card*, Card*>,float> strats;
    std::map<std::pair<Card*, Card*>,float> strat_sum;
    //because cards that are conflicting with random board 
    //runnout are not included we need to count each time they 
    //are updated so at the end we can accuratley divide by 
    //the number of times it was updated
    //will have to sum all ev up and divide by total number
    doubleDic ev; 
    doubleDic actual; 
    std::map<std::pair<Card*,Card*>, float> regrets;
    std::map<std::pair<Card*,Card*>,std::vector<float>> final_strats;
    inline void set_strats(std::map<std::pair<Card*, Card*>,float> strat){strats=strat;}    
    

    void get_ev(matchDic &range1,
                matchDic &range2,
                std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p1_win,
                std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p2_win,
                std::map<std::pair<Card*,Card*>,float> prct1, 
                std::map<std::pair<Card*,Card*>,float> prct2);

    void get_leaf_ev(matchDic &range1,
                     matchDic &range2,
                    std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p1_win,
                    std::map<std::pair<Card*,Card*>, std::map<std::pair<Card*,Card*>,bool>> &p2_win,
                    std::map<std::pair<Card*,Card*>,float> prct1, 
                    std::map<std::pair<Card*,Card*>,float> prct2);

    void get_regret(std::vector<Node*> &nodes);
    void get_regret(std::vector<Node> &nodes);
    void save_strat(std::vector<Node*> nodes);
    void save_strat(std::vector<Node> nodes);
};
#endif
