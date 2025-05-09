#pragma once
#include <raylib.h>
#include "game_logic.hpp"

class GameRenderer {
public:
    GameRenderer(int windowWidth, int windowHeight, int cellSize);
    ~GameRenderer();
    
    void render(const GameLogic& game);
    void handleInput(GameLogic& game);
    bool shouldClose() const;
    
private:
    int windowWidth;
    int windowHeight;
    int cellSize;
    Color backgroundColor;
    Color aliveCellColor;
    Color deadCellColor;
    
    void drawCell(int row, int column, bool isAlive);
    std::pair<int, int> screenToGrid(int x, int y) const;
}; 