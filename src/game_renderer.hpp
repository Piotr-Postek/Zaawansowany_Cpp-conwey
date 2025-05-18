#pragma once
#include </opt/homebrew/Cellar/raylib/5.5/include/raylib.h>
#include "game_logic.hpp"

class GameRenderer {
public:
    GameRenderer(int windowWidth, int windowHeight, int cellSize);
    ~GameRenderer();
    
    void render(const GameLogic& game);
    void handleInput(GameLogic& game);
    bool shouldClose() const;
    bool isGameStarted() const { return gameStarted; }
    
private:
    int windowWidth;
    int windowHeight;
    int cellSize;
    Color backgroundColor;
    Color aliveCellColor;
    Color deadCellColor;
    
    // Button properties
    Rectangle startButton;
    const char* buttonText = "Start Game";
    bool gameStarted;
    
    void drawCell(int row, int column, bool isAlive);
    std::pair<int, int> screenToGrid(int x, int y) const;
    void drawStartButton();
    bool isMouseOverButton() const;
}; 