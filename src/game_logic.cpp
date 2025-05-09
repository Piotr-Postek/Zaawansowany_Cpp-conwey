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
    const std::vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& offset : neighborOffsets) {
        int neighborRow = (row + offset.first + rows) % rows;
        int neighborColumn = (column + offset.second + columns) % columns;
        liveNeighbors += grid[neighborRow][neighborColumn] ? 1 : 0;
    }

    return liveNeighbors;
}

void GameLogic::updateState() {
    std::vector<std::vector<bool>> newGrid = grid;
    
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            int neighbors = countLiveNeighbors(row, column);
            bool currentState = grid[row][column];
            
            // Apply Game of Life rules
            if (currentState) {
                // Live cell
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[row][column] = false; // Dies
                }
            } else {
                // Dead cell
                if (neighbors == 3) {
                    newGrid[row][column] = true; // Becomes alive
                }
            }
        }
    }
    
    grid = std::move(newGrid);
}

bool GameLogic::isWithinBounds(int row, int column) const {
    return row >= 0 && row < rows && column >= 0 && column < columns;
} 