#ifndef HEAD_H
#define HEAD_H 

#include "Node.h"
#include <vector>

//for now head will just be the start of each street 
//i.e action will just be check eventually i guess you can
//filter shit but the problem is you'll then need to run an additional
//sim before the actual sim to determine what their range is that makes 
//that action which you can do but since you'll need to do this anyway to 
//determine that range just do this instead
class Head{
  public:
    Head(bool p1, Node::Street street, float prev_bet, float potsize, 
        std::pair<float,float> stacks, Node::Action prev_act, int num_bets, float blind);
    
    std::vector<Node> nodes;

    Node::Street get_next_street(Node::Action prev, Node::Action curr, 
                             Node::Street street);

};

  
#endif 
