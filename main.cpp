/*******************************************************************************************
*
*   raylib [core] example - input keys
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include ".\build\_deps\raylib-build\raylib\include\raylib.h"
#include "include/opentone.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920 / 2; // will likely be imported from a config file in the future
    const int screenHeight = 1080 / 2;

    InitWindow(screenWidth, screenHeight, "OpenTone");

    Vector2 mousePos = {0.0f, 0.0f};

    // buttons
    Rectangle 

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        mousePos = GetMousePosition();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(OT_BACKGROUND);

            DrawText("move the ball with arrow keys", 10, 10, 20, OT_WHITE);
            
            DrawRectangle(100, 50, 200, 100, OT_ORANGE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}