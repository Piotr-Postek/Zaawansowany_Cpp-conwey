#include "game_logic.hpp"

using namespace std;

GameLogic::GameLogic(int rows, int columns, shared_ptr<NeighborhoodStrategy> strategy)
    : rows(rows), columns(columns), grid(rows, vector<bool>(columns, false)), strategy(strategy) {}

void GameLogic::setCellState(int row, int column, bool alive) {
    if (isWithinBounds(row, column)) {
        grid[row][column] = alive;
    }
}

bool GameLogic::getCellState(int row, int column) const {
    if (isWithinBounds(row, column)) {
        return grid[row][column];
    }
    return false;
}

// 

int GameLogic::countLiveNeighbors(int row, int column) const {
    int liveNeighbors = 0;
    
    // Get neighbor offsets from the strategy
    auto neighborOffsets = strategy->getNeighbors(row, column, rows, columns);
    
    // Count live neighbors
    for (const auto& offset : neighborOffsets) {
        int neighborRow = (row + offset.first + rows) % rows;
        int neighborColumn = (column + offset.second + columns) % columns;
        liveNeighbors += grid[neighborRow][neighborColumn] ? 1 : 0;
    }
    
    return liveNeighbors;
}

void GameLogic::updateState() {
    // Create a new grid for the next state
    vector<vector<bool>> newGrid(rows, vector<bool>(columns, false));
    
    // Calculate next state for each cell
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            int neighbors = countLiveNeighbors(row, column);
            bool currentState = grid[row][column];
            
            // Apply Game of Life rules
            if (currentState) {
                // Live cell
                if (neighbors == 2 || neighbors == 3) {
                    newGrid[row][column] = true; // Survives
                }
            } else {
                // Dead cell
                if (neighbors == 3) {
                    newGrid[row][column] = true; // Becomes alive
                }
            }
        }
    }
    
    // Update the grid with the new state
    grid = move(newGrid);
}

bool GameLogic::isWithinBounds(int row, int column) const {
    return row >= 0 && row < rows && column >= 0 && column < columns;
} 