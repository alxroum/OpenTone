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

class OTButton : public Rectangle {
    
    private:

        Vector2 screenPos;
        float width = 100;
        float height = 35;
        Color color;
        int btnState = 0;
        Rectangle rect;

    public:

        OTButton(Vector2 screenPosition, float btnWidth, float btnHeight,  Color backgroundColor) {
            screenPos = screenPosition;
            width = btnWidth;
            height = btnHeight;
            color = backgroundColor;
            rect = {screenPos.x, screenPos.y, width, height};
        }

        void DrawButton() {
            DrawRectanglePro(rect, {width / 2, height / 2}, 0, color);
        }

        Rectangle Rect() {
            return this->rect;
        }

        float Width() {
            return this->width;
        }

        float Height() {
            return this->height;
        }
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920 / 2; // will likely be imported from a config file in the future
    const int screenHeight = 1080 / 2;

    const Vector2 screenCenter = {screenWidth / 2, screenHeight / 2};

    // VARIABLES

    Vector2 mousePos = {0.0f, 0.0f};

    // BUTTONS

    OTButton btn = OTButton(screenCenter, 150, 50, OT_BLUE);

    // GAME SETUP

    InitWindow(screenWidth, screenHeight, "OpenTone");
    
    Font apb = LoadFontEx("/graphics/font/calibri.ttf", 32, 0, 250);

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

            DrawTextEx(apb, "Welcome to OpenTone!",{10, 10}, 20, 3, OT_WHITE);
            
            btn.DrawButton();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}