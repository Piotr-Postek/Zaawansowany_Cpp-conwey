#include <raylib.h>


int main() 
{
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");
    SetTargetFPS(FPS);  //FPS limit

    //Simulation Loop
    while(WindowShouldClose() == false)     //ESC lub close button closes the program
    {
        // 1. Event Handling


        // 2. Updating State


        // 3. Drawing
        BeginDrawing();
        EndDrawing();

    }




    CloseWindow();
}