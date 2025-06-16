#pragma once
#include <vector>
#include <utility>

using namespace std;

class NeighborhoodStrategy {
public:
    virtual ~NeighborhoodStrategy() = default;
    virtual vector<pair<int, int>> getNeighbors(int row, int column, int rows, int columns) const = 0;
    
protected:
    // Helper method to wrap coordinates around the grid
    pair<int, int> wrapCoordinates(int row, int col, int rows, int columns) const {
        // Handle negative coordinates
        row = (row + rows) % rows;
        col = (col + columns) % columns;
        
        // Handle coordinates beyond grid size
        if (row < 0) row += rows;
        if (col < 0) col += columns;
        
        return {row, col};
    }
};

class MooreNeighborhood : public NeighborhoodStrategy {
public:
    vector<pair<int, int>> getNeighbors(int row, int column, int rows, int columns) const override {
        vector<pair<int, int>> neighbors;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue; // Skip the cell itself
                
                // Calculate wrapped coordinates
                auto [wrappedRow, wrappedCol] = wrapCoordinates(row + i, column + j, rows, columns);
                neighbors.push_back({wrappedRow - row, wrappedCol - column});
            }
        }
        return neighbors;
    }
};

class VonNeumannNeighborhood : public NeighborhoodStrategy {
public:
    vector<pair<int, int>> getNeighbors(int row, int column, int rows, int columns) const override {
        vector<pair<int, int>> neighbors;
        const vector<pair<int, int>> directions = {
            {-1, 0},  // up
            {1, 0},   // down
            {0, -1},  // left
            {0, 1}    // right
        };
        
        for (const auto& dir : directions) {
            // Calculate wrapped coordinates
            auto [wrappedRow, wrappedCol] = wrapCoordinates(row + dir.first, column + dir.second, rows, columns);
            neighbors.push_back({wrappedRow - row, wrappedCol - column});
        }
        
        return neighbors;
    }
}; 