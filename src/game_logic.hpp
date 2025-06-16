#pragma once
#include <vector>
#include <utility>
#include <memory>
#include "neighborhood_strategy.hpp"

using namespace std;

class GameLogic {
public:
    GameLogic(int rows, int columns, shared_ptr<NeighborhoodStrategy> strategy = make_shared<MooreNeighborhood>());
    
    // Core game logic methods
    void setCellState(int row, int column, bool alive);
    bool getCellState(int row, int column) const;
    int countLiveNeighbors(int row, int column) const;
    void updateState(); // Applies Game of Life rules to update the grid
    
    // Getters
    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    const vector<vector<bool>>& getGrid() const { return grid; }

    // Strategy setter
    void setNeighborhoodStrategy(shared_ptr<NeighborhoodStrategy> newStrategy) {
        strategy = newStrategy;
    }

private:
    int rows;
    int columns;
    vector<vector<bool>> grid;
    shared_ptr<NeighborhoodStrategy> strategy;
    bool isWithinBounds(int row, int column) const;
}; 