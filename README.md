# POKER SOLVER 

## Work in progress. 

## What I have so far
1. CFRM to get the actual strategies is 
done for at least one iteration (not tested)
2. Some Basic GUI to select ranges/runouts and add custom ranges

## TO-DO 
1. TEST THE CFRM for exploitability
2. Threading 
3. pruning cards (Ace of clubs jack of clubs is same as as Ace of clubs jack of hearts so i shouldn't treat them as seperate cards this will reduce time to solve)
4. Cleanup GUI 
5. Actual user side GUI should send ranges to the solver
6. Add default ranges for each position against each position 
7. Currently it only solves the flop (one line change basically)
8. Some redundent inneficient code I can fix
9. rewrite so that it is better for threading (probably make each card it's own seperate tree)

## CONTRIBUTE?
If you feel you can improve the GUI or the algo 
I encourage you to contribute. 
My code is difficult to understand at the moment and 
it is disgusting and porrly written so i get this is a challenge 
so if you have any questions feel free to ask if you feel so 
inclined as to try and help me. I am a terrible at GUI so this 
is what I am looking for the most help in but obviously 
everything could use improvment.

## ALGO 
This solver uses CFRM. The summary of the algorithm is 
that we subtract the ACTUAL value from the EV. What i call 
the ACTUAL value is just the ammount of money we would win if 
we chose that option every time meaning when calculating this 
value we only consider the opponents percetnages of reaching this node. 
The EV is the value of our current percente chance of reaching a particular 
state combined with the opponents. the regret is the non negative 
difference between the actual and our current EV. This should be intuitive if we would have 
won more money performing action X every time then we regret not taking action X. this 
normalized regret is then our new strategy (percentage of taking this action).
After Y number of iterations we sum all of our passed strategies and this becomes 
our final strategy. Non terminal nodes sum up their childrens 
value. The current implimentation is a tree where a dictionary holds the ev 
and percentage of performing a certain action at each state given the particular card.
We do this to reduce the number of nodes and so we can just loop through all nodes
and calculate the EV and chance of winning against the other cards.
We randomly sample 1k runnouts and all non conflicting cards in the range are updated and 
the CFRM will run 10k times. We do this because we don't know what the cards to come are so we
solve 1k different runnouts given the range to get a good estimate of what our strategy should be. 
We also have to solve to the river because some cards may decide to bluff and we need to account 
for this otherwise we would just need to calculate if we have enough equity to continue


