Programming-Portfolio
=====================

This folder contains my programming exploits.

Brief Description of Each project:

1. SIMPLECLIENTSERVER - a project consisting of 4 miniature projects that built into 1 final thing (a simple client server interaction with the client having 3 available commands, and the server having a response for each command, and the ability to run commands from the client automatically from within the code). More information on how the folder is structured is in the readme for that project folder. The main point of the project was to explore how threads and processes work, and how socket/network programming works. 
2. 8-Puzzle Solver – a project consisting of methods to support the use of 3 different algorithms, one uninformed search (depth-first search), and two informed searches (a greedy algorithm and an a_star (A*)) with the heuristics of a Manhattan Distance, or a Similarity comparison between the goal/current states. Use of the program requires a GNU LISP compiler, and the input convention for the program is 
“(dfs ‘(1 2 3 4 5 6 7 8 0))” for depth-first search
“(greedy ‘(1 2 3 4 5 6 7 8 0) ‘heuristic-1)” for greedy
“(a_star ‘(1 2 3 4 5 6 7 8 0) ‘heuristic-1)” for a_star 
You may replace heuristic-1 with heuristic-2
You may also replace the list of numbers (the initial configuration of the puzzle) with a different order of the numbers. 
From the way depth_first search is built, it just doesn’t really work, even for easy puzzles. 
Greedy works with heuristic-2 for some puzzles. 
A_star with heuristic-1 works for some puzzles. 
A_star with heurisitic-2 should work for any feasible puzzle (i.e. where the initial config is within the possible state space of the goal state)
3. ConvexHull – a program that computes the convex hull of a set of points. In this particular case, the program is designed to compare Graham’s Scan, and Jarvis’s March, which are both clearly implemented in the .cpp file. This program runs several preset test cases to compare the two algorithms and run times. In general, Graham’s Scan is a little slower than Jarvis’s March, though Jarvis’s March has potential to be slower than Graham’s Scan depending on the size of the actual convex hull.  
