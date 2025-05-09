#include "game_renderer.hpp"

GameRenderer::GameRenderer(int windowWidth, int windowHeight, int cellSize)
    : windowWidth(windowWidth), windowHeight(windowHeight), cellSize(cellSize) {
    InitWindow(windowWidth, windowHeight, "Game of Life");
    SetTargetFPS(12);
    
    backgroundColor = {29, 29, 29, 255};
    aliveCellColor = {0, 255, 0, 255};
    deadCellColor = {55, 55, 55, 255};
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
    
    EndDrawing();
}

void GameRenderer::handleInput(GameLogic& game) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        auto [row, column] = screenToGrid(mousePos.x, mousePos.y);
        game.setCellState(row, column, !game.getCellState(row, column));
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