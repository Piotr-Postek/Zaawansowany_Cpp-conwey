#pragma once
#include <vector>
#include <utility>

class GameLogic {
public:
    GameLogic(int rows, int columns);
    
    // Core game logic methods
    void setCellState(int row, int column, bool alive);
    bool getCellState(int row, int column) const;
    int countLiveNeighbors(int row, int column) const;
    void updateState(); // Applies Game of Life rules to update the grid
    
    // Getters
    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    const std::vector<std::vector<bool>>& getGrid() const { return grid; }

private:
    int rows;
    int columns;
    std::vector<std::vector<bool>> grid;
    bool isWithinBounds(int row, int column) const;
}; 