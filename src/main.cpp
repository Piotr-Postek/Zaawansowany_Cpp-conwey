#include <raylib.h>
#include "simulation.hpp"


int main() 
{
    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    int FPS = 12;


    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");
    SetTargetFPS(FPS);  //FPS limit
    Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};
    simulation.SetCellValue(3, 4, 1);

    //Simulation Loop
    while(WindowShouldClose() == false)     //ESC lub close button closes the program
    {
        // 1. Event Handling


        // 2. Updating State


        // 3. Drawing
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();

    }




    CloseWindow();
}