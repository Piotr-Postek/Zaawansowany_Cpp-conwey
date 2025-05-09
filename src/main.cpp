#include "game_logic.hpp"
#include "game_renderer.hpp"

int main() {
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    
    GameRenderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    GameLogic game(WINDOW_HEIGHT / CELL_SIZE, WINDOW_WIDTH / CELL_SIZE);
    
    bool isPaused = true;
    
    while (!renderer.shouldClose()) {
        // Handle input
        renderer.handleInput(game);
        
        if (IsKeyPressed(KEY_SPACE)) {
            isPaused = !isPaused;
        }
        
        // Update game state
        if (!isPaused) {
            game.updateState();
        }
        
        // Render
        renderer.render(game);
    }
    
    return 0;
}