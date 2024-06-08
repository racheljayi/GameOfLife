#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

// MODIFY VARIABLES HERE
const int O = 3; // lifespan
const int D = 1; // decay
const int K = 3; // minimal capacity
const int M = 0; // carrying capacity
const int R = 2; // reproductive rate
const int T = 2; // reproductive lifespan threshold
const int gridSize = 25; 

// Cell class: manages the state and behavior of each cell
class Cell {
public:
    int lifespan;
    
    Cell() : lifespan(0) {}
    Cell(int life) : lifespan(life){}

    bool isAlive() const{
        return lifespan > 0;
    }

    void decay() {
        if (lifespan > 0) {
            lifespan -= D;
        }
    }
};

// Grid class
class Grid {
    private:
        vector<vector<Cell>> grid;
        vector<vector<Cell>> tempGrid;
    
    // Count the number of neighbors a cell at (row: r, column c) has whose value exceeds a specific threshold
    int countNeighbors(int r, int c, int threshold){
        int count = 0; 
        for (int i = r - 1; i <= r + 1; i++) {
            for (int j = c - 1; j <= c + 1; j++) {
                if ((i == r && c == j) || i < 0 || j < 0 || i >= gridSize || j >= gridSize) continue;
                if (grid[i][j].isAlive() && grid[i][j].lifespan >= threshold) count++; 
            }
        }
        return count;
    }

    public:
        Grid() : grid(gridSize, vector<Cell>(gridSize)), tempGrid(gridSize, vector<Cell>(gridSize)) {
            for (int x = 0; x < gridSize; x++) {
                for (int y = 0; y < gridSize; y++) {
                    grid[x][y] = Cell(rand() % (O + 1));
                }
            }
        }
        void print() const {
            cout << "\n--------------------------\n";
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                    if (grid[i][j].isAlive()) {
                        cout << grid[i][j].lifespan;
                    } else {
                        cout << ".";
                    }
                }
                cout << "\n";
            }
            cout << "\n--------------------------\n";
        }

        void computeNextStep() {
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                    if (!grid[i][j].isAlive()) {
                        if (countNeighbors(i, j, T) >= R) {
                            tempGrid[i][j] = Cell(rand() % (O + 1)); 
                        } else {
                            tempGrid[i][j] = Cell(0); 
                        }
                    } else {
                        tempGrid[i][j] = grid[i][j];
                        tempGrid[i][j].decay();
                        int count = countNeighbors(i, j, 1); 
                        if (count < M || count >= K) {
                            tempGrid[i][j] = Cell(0); 
                        }
                    }
                }
            }
            grid.swap(tempGrid);
        }
};

int main() {
    Grid grid;
    while (true) {
        grid.print();
        grid.computeNextStep();
        usleep(500000);
    }
    return 0; 
}

