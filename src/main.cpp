#include <raylib.h>
#include <iostream>
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
    // simulation.SetCellValue(5, 29, 1);
    // simulation.SetCellValue(6, 0, 1);
    // simulation.SetCellValue(5, 0, 1);
    // std::cout << simulation.CountLiveNeighbors(5, 29) << std::endl;

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