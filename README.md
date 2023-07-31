# Modified Game of Life
John Conway’s Game of Life is a zero-player game where an initial configuration of cells is created & its evolution at each step in time under a set of rules is observed. The original rules are as follows:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.

2. Any live cell with two or three live neighbours lives on to the next generation.

3. Any live cell with more than three live neighbours dies, as if by overpopulation.

4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

This is a C++ implementation of Life with modified rules to account for a very simplified idea of population lifespans.

We have the following variables: 
O: lifespan

D: decay

M: minimal capacity

K: carrying capacity

R: reproductive rate

T: reproductive lifespan threshold

Each live cell has a random lifespan of 1 to O. The modified rules are as follows: 

1. Every cycle each live cell’s lifespan goes down by D. Cells with a score of 1 dies, as if by age.  
2. Any live cell with fewer than M live neighbours dies, as if by underpopulation
3. Any live cell with more than K neighbors dies, as if by overpopulation.
4. Any dead cell with at least R live neighbors with a score T or above becomes a live cell, as if by reproduction. 

In the original model, the variables would be configured as follows:
O: 1
D: 0
M: 2
K: 3
R: 3
T: 1

With different configurations, we can observe different patterns. 
