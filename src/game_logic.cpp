#include "game_logic.hpp"

GameLogic::GameLogic(int rows, int columns)
    : rows(rows), columns(columns), grid(rows, std::vector<bool>(columns, false)) {}

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

int GameLogic::countLiveNeighbors(int row, int column) const {
    int liveNeighbors = 0;
    
    // Check all 8 surrounding cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Skip the cell itself
            if (i == 0 && j == 0) continue;
            
            int neighborRow = (row + i + rows) % rows;
            int neighborColumn = (column + j + columns) % columns;
            liveNeighbors += grid[neighborRow][neighborColumn] ? 1 : 0;
        }
    }
    
    return liveNeighbors;
}

void GameLogic::updateState() {
    // Create a new grid for the next state
    std::vector<std::vector<bool>> newGrid(rows, std::vector<bool>(columns, false));
    
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
    grid = std::move(newGrid);
}

bool GameLogic::isWithinBounds(int row, int column) const {
    return row >= 0 && row < rows && column >= 0 && column < columns;
} 