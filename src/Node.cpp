#include "Node.h"

const std::vector<float> Node::bet_sizes = {
  .25,.5, .75,1,1.25,2
};

float Node::bb = 1;
//float starting_stack1 = 100;
//float starting_stack2 = 100;

//setting this here manually for ease of use
Player Node::short_stack = STA;


//have static variable for short stack 
//i'm not handeling pot incrementing correctly
//nor the decrmenting of the short stack
//ALSO c_bet(curr_bet) should be p_bet (previous bet)
Node::Node(Node *prnt, Action act, Player p,
           Street s, float stk, float pot, float c_bet,
           int num_bets){
  parent = prnt; 
  action = act;
  player = p;
  street = s;
  min_stack= stk;
  potsize = pot;
  cur_bet= c_bet;

  if (act==FOLD){
    children= {};
  }
  else if (act == CALL &&  s == RIVER){
    potsize += c_bet;
    min_stack -= c_bet;
    children = {};
  }
  else if (act == ALLIN){
    make_terminal_nodes(act,p,s,stk,pot,c_bet);
  }
  else{
    Action b_act = BET;
    if (act == BET || act ==RAISE){
      b_act = RAISE; 
    }

    std::vector<float>child_bets = get_all_bets();
    //add all in and fold/check
    Action next__bet = FOLD;
    make_terminal_nodes(act,p,s,stk,pot,c_bet);
  }

}

void Node::make_terminal_nodes(Action a, 
                           Player plyr, Street str, float min,
                           float money, float last_best){
  
  Action next = a==CHECK ? CHECK : FOLD; 
  Player next_p = plyr == FTA ? STA : FTA;
  
  Node *tmp = new Node(this,next,next_p,str,min,money,0,0);
  children.push_back(tmp);
  tmp = new Node(this,ALLIN,next_p,str,min,money,0,0);

}

