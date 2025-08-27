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

void drawButton(Vector2 bottomCorner, Vector2 size, char *text, Color fillColor, Color lineColor)
{
    Vector2 mousePoint = GetMousePosition();
    Vector2 smallerRectSize = {
        size.x - 2,
        size.y - 2};

    Vector2 smallerBottomCorner = {
        bottomCorner.x + 1,
        bottomCorner.y + 1};

    Rectangle btnBounds = {
        bottomCorner.x,
        bottomCorner.y,
        size.x,
        size.y};

    DrawRectangleV(bottomCorner, size, lineColor);
    DrawRectangleV(smallerBottomCorner, smallerRectSize, fillColor);
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        DrawRectangleV(smallerBottomCorner, smallerRectSize, YELLOW);
    }

    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 30, 5);
    Vector2 textPos = {
        bottomCorner.x + ((size.x / 2) - (textSize.x / 2)),
        bottomCorner.y + ((size.y / 2) - (textSize.y / 2))};

    DrawTextEx(GetFontDefault(), text, textPos, 30, 5, BLACK);
}

void drawMenu()
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), "SNAKE", 30, 5);

    Vector2 textPos = {
        (GetScreenWidth() / 2) - (int)(textSize.x) / 2,
        (GetScreenHeight() / 2) - (int)(textSize.y) / 2};

    DrawTextEx(GetFontDefault(), "SNAKE", textPos, 30, 5, BLACK);

    Vector2 buttonSize = {
        100,
        50};

    Vector2 buttonCorner = {
        (GetScreenWidth() / 2) - (int)(buttonSize.x) / 2,
        (GetScreenHeight() / 2) + 100 - (int)(buttonSize.y) / 2};

    drawButton(buttonCorner, buttonSize, "PLAY", WHITE, BLACK);
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
