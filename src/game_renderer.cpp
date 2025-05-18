#include "game_renderer.hpp"
#include <chrono>
#include <thread>

GameRenderer::GameRenderer(int windowWidth, int windowHeight, int cellSize)
    : windowWidth(windowWidth), windowHeight(windowHeight), cellSize(cellSize), gameStarted(false) {
    InitWindow(windowWidth, windowHeight, "Game of Life");
    SetTargetFPS(12);
    
    backgroundColor = {29, 29, 29, 255};
    aliveCellColor = {0, 255, 0, 255};
    deadCellColor = {55, 55, 55, 255};
    
    // Initialize button
    int buttonWidth = 150;
    int buttonHeight = 40;
    startButton = {
        (float)(windowWidth - buttonWidth) / 2,
        (float)(windowHeight - buttonHeight - 20),
        (float)buttonWidth,
        (float)buttonHeight
    };
}

GameRenderer::~GameRenderer() {
    CloseWindow();
}

void GameRenderer::render(const GameLogic& game) {
    BeginDrawing();
    ClearBackground(backgroundColor);
    
    for (int row = 0; row < game.getRows(); row++) {
        for (int column = 0; column < game.getColumns(); column++) {
            drawCell(row, column, game.getCellState(row, column));
        }
    }
    
    if (!gameStarted) {
        drawStartButton();
    }
    
    EndDrawing();
}

void GameRenderer::handleInput(GameLogic& game) {
    if (!gameStarted) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (isMouseOverButton()) {
                gameStarted = true;
                // Add a small delay to ensure the button click is processed
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } else {
                Vector2 mousePos = GetMousePosition();
                auto [row, column] = screenToGrid(mousePos.x, mousePos.y);
                if (row >= 0 && row < game.getRows() && column >= 0 && column < game.getColumns()) {
                    game.setCellState(row, column, !game.getCellState(row, column));
                }
            }
        }
    } else {
        if (IsKeyPressed(KEY_SPACE)) {
            gameStarted = false;
        }
    }
}

bool GameRenderer::shouldClose() const {
    return WindowShouldClose();
}

void GameRenderer::drawCell(int row, int column, bool isAlive) {
    Color color = isAlive ? aliveCellColor : deadCellColor;
    DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
}

std::pair<int, int> GameRenderer::screenToGrid(int x, int y) const {
    int row = y / cellSize;
    int column = x / cellSize;
    return {row, column};
}

void GameRenderer::drawStartButton() {
    Color buttonColor = isMouseOverButton() ? GRAY : DARKGRAY;
    DrawRectangleRec(startButton, buttonColor);
    
    int textWidth = MeasureText(buttonText, 20);
    int textX = startButton.x + (startButton.width - textWidth) / 2;
    int textY = startButton.y + (startButton.height - 20) / 2;
    
    DrawText(buttonText, textX, textY, 20, WHITE);
}

bool GameRenderer::isMouseOverButton() const {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, startButton);
} 