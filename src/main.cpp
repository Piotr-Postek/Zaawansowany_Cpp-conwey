#include "game_logic.hpp"
#include "game_renderer.hpp"
#include "neighborhood_strategy.hpp"
#include <chrono>
#include <thread>

using namespace std;

int main() {
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    
    // Create game with Moore neighborhood (8 neighbors) by default
    GameLogic game(WINDOW_HEIGHT / CELL_SIZE, WINDOW_WIDTH / CELL_SIZE);
    
    // To use Von Neumann neighborhood (4 neighbors), uncomment the following line:
    // game.setNeighborhoodStrategy(make_shared<VonNeumannNeighborhood>());
    
    GameRenderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    
    while (!renderer.shouldClose()) {
        // Handle input
        renderer.handleInput(game);
        
        // Update game state only if game has started
        if (renderer.isGameStarted()) {
            // Add a small delay to make the simulation visible
            this_thread::sleep_for(chrono::milliseconds(100));
            game.updateState();
        }
        
        // Render
        renderer.render(game);
    }
    
    return 0;
}