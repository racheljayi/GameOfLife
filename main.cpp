#include <iostream>
#include <unistd.h>
using namespace std;

// MODIFY VARIABLES HERE
const int O = 3; // lifespan
const int D = 1; // decay
const int K = 3; // minimal capacity
const int M = 0; // carrying capacity
const int R = 2; // reproductive rate
const int T = 2; // reproductive lifespan threshold

const int gridSize = 25; 
void printGrid(int grid[gridSize][gridSize]);
void computeGrid(int grid[gridSize][gridSize]);

int main() {

    int grid[gridSize][gridSize] = {};

    for (int x = 0; x < gridSize; x++){
        for (int y = 0; y < gridSize; y++){
            grid[x][y] = rand() % (O+1); 
        }
    }

    while (true){
        printGrid(grid);
        computeGrid(grid);
        usleep(500000);
    }
    return 0; 
}

int countNeighbors(int grid[gridSize][gridSize], int r, int c, int threshold){
    int count = 0; 
    int i, j;
    for (i = r - 1; i <= r+1; i++){
        for (j = c - 1; j <= c + 1; j++){
            if ((i == r && c == j) || i < 0 || j < 0|| r >= gridSize || j >= gridSize) continue;
            if (grid[i][j] >= threshold) count++; 
        }
    }
    return count;
}

void printGrid(int grid[gridSize][gridSize]){
    cout << "\n--------------------------\n";
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            if (grid[i][j] != 0){
                cout << grid[i][j];
            }
            else {
                cout << ".";
            }
        }
        cout << "\n";
    }
    cout << "\n--------------------------\n";
}

void computeGrid(int grid[gridSize][gridSize]){
    int tempGrid[gridSize][gridSize] = {};
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            if (grid[i][j] == 0){
                if (countNeighbors(grid, i, j, T) >= R){
                    tempGrid[i][j] = rand() % (O+1); 
                }
                else {
                    tempGrid[i][j] = 0; 
                }
            }
            else {
                tempGrid[i][j] = grid[i][j] - D;
                int count = countNeighbors(grid, i, j, 1); 
                if (count < M || count >= K) {
                    tempGrid[i][j] = 0; 
                }
            }
        }
    }
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            grid[i][j] = tempGrid[i][j];
        }
    }
}
