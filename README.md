# POKER SOLVER

## Description
Poker solver written in c++  (work in progress).
Going to use a Tree structure to represent game state and will 
get the GTO (game theory optimal) strategy by using CFRM 
[(Counter Factual Regret Minimization)](https://proceedings.neurips.cc/paper_files/paper/2007/file/08d98638c6fcd194a4b1e6992063e944-Paper.pdf)

## FILES
1. Everything is in the SRC 
2. If you are just interested in the hand evaluator that calculates the rank of the hand is hand_rank
3. The file used to generate all unique possible runouts is in make_cards

## RUN
Not really a point in running since it's not done but I have a cmake file so
if you want to test it out go to the buid directory and type:
'''
cmake .. && make && ./runme 
'''

## GOAL
1. Have a poker solver with various sizes
2. Chose custom sizings 
3. Custom ranges
4. GUI

## NOTES
Still a work in progress just finished setting up the Node class
which represents the game state

## FINISHED
1. Game Tree
2. Fast hand evaluation

## WORK IN PROGRESS
1. The acual algo
    * Calculate regrets
    * Update nodes efficiently
2. Impliment threading 
3. Monte carlo
4. GUI (Will probably be really simple and written in raylib)

## CONTRIBUTE
If you would like to contribute please feel free to do so as this will
be a difficult and probably massive project.
I don't have a lot of experience writting GUI's so if you do and would like 
to write a GUI that would be incredibly helpful. GUI would need to be able to select 
Starting card ranges and current player cards what player is the hero and what street 
we are on and what cards have come out. Also be able to select bet sizes if you want to 
set custom bet sizes 
