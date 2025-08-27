#include "raylib.h"
#include "raymath.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include <math.h>
#include <stdio.h>

typedef struct
{
    double x1, y1;
    double x2, y2;
} Line;

typedef enum
{
    MENU = 0,
    PLAYING = 1,
    GAMEOVER = 2
} GameState;

void drawButton(Vector2 bottomCorner, int width, int height, char *text)
{
    Vector2 Corner1 = {
        bottomCorner.x + width,
        bottomCorner.y};

    Vector2 Corner2 = {
        bottomCorner.x + width,
        bottomCorner.y + height};

    Vector2 Corner3 = {
        bottomCorner.x,
        bottomCorner.y + height};

    DrawLineV(bottomCorner, Corner1, BLACK);
    DrawLineV(Corner1, Corner2, BLACK);
    DrawLineV(Corner2, Corner3, BLACK);
    DrawLineV(Corner3, bottomCorner, BLACK);
}

void drawMenu()
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), "SNAKE", 30, 5);

    Vector2 textPos = {
        (GetScreenWidth() / 2) - (int)(textSize.x) / 2,
        (GetScreenHeight() / 2) - (int)(textSize.y) / 2};

    DrawTextEx(GetFontDefault(), "SNAKE", textPos, 30, 5, BLACK);

    int buttonWidth = 100;
    int buttonHeight = 50;

    Vector2 buttonCorner = {
        (GetScreenWidth() / 2) - (int)(buttonWidth) / 2,
        (GetScreenHeight() / 2) - (int)(buttonHeight) / 2};

    drawButton(buttonCorner, buttonWidth, buttonHeight, "PLAY");
}

void drawToScreen(GameState gameState)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (gameState == MENU)
    {
        drawMenu();
    }
    EndDrawing();
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    GameState gameState = 0;

    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Handle Input
        // Update State
        // Draw

        drawToScreen(gameState);
    }

    CloseWindow();

    return 0;
}
