#include "game_logic.hpp"
#include "game_renderer.hpp"
#include <chrono>
#include <thread>

int main() {
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    
    GameRenderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    GameLogic game(WINDOW_HEIGHT / CELL_SIZE, WINDOW_WIDTH / CELL_SIZE);
    
    while (!renderer.shouldClose()) {
        // Handle input
        renderer.handleInput(game);
        
        // Update game state only if game has started
        if (renderer.isGameStarted()) {
            // Add a small delay to make the simulation visible
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            game.updateState();
        }
        
        // Render
        renderer.render(game);
    }
    
    return 0;
}