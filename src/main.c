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
} State;

typedef struct
{
    Rectangle rectangle;
    char *text;
    Color fillColor;
    Color lineColor;
    Color hoverColor;
    bool buttonHovered;
    bool buttonPressed;
} Button;

typedef struct
{
    Button startButton;
} MenuState;

typedef struct
{
    State state;
    MenuState menuState;

} GameState;

void draw_button(Button button)
{
    Rectangle smallerRect = {
        button.rectangle.x + 1,
        button.rectangle.y + 1,
        button.rectangle.width - 2,
        button.rectangle.height - 2};

    DrawRectangleRec(button.rectangle, button.lineColor);
    DrawRectangleRec(smallerRect, button.fillColor);
    if (button.buttonHovered)
    {
        DrawRectangleRec(smallerRect, button.hoverColor);
    }

    Vector2 textSize = MeasureTextEx(GetFontDefault(), button.text, 30, 5);
    Vector2 textPos = {
        button.rectangle.x + ((button.rectangle.width / 2) - (textSize.x / 2)),
        button.rectangle.y + ((button.rectangle.height / 2) - (textSize.y / 2))};

    DrawTextEx(GetFontDefault(), button.text, textPos, 30, 5, BLACK);

    if (button.buttonPressed)
    {
        DrawTextEx(GetFontDefault(), "CLICKED", textPos, 30, 5, BLACK);
    };
}

void draw_menu(const MenuState *menuState)
{
    draw_button(menuState->startButton);
}

void render(const GameState *gameState)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (gameState->state == MENU)
    {
        draw_menu(&gameState->menuState);
    }
    EndDrawing();
}

void update_state(GameState *gameState)
{
    Vector2 mousePoint = GetMousePosition();

    gameState->menuState.startButton.buttonPressed = false;
    gameState->menuState.startButton.buttonHovered = false;
    if (CheckCollisionPointRec(mousePoint, gameState->menuState.startButton.rectangle))
    {
        gameState->menuState.startButton.buttonHovered = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            gameState->menuState.startButton.buttonPressed = true;
        }
    }
};

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    State state = MENU;

    Vector2 buttonSize = {
        100,
        50};
    Vector2 buttonCorner = {
        (screenWidth / 2) - (int)(buttonSize.x) / 2,
        (screenHeight / 2) + 100 - (int)(buttonSize.y) / 2};

    Rectangle buttonRectangle = {
        buttonCorner.x,
        buttonCorner.y,
        buttonSize.x,
        buttonSize.y};

    Button startButton = {
        buttonRectangle,
        "START",
        WHITE,
        BLACK,
        YELLOW,
        false,
        false};

    MenuState menuState = {
        startButton};
    GameState gameState = {
        state,
        menuState};

    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update_state(&gameState);
        render(&gameState);
    }

    CloseWindow();

    return 0;
}

// ToDo
// Think about input handling, or am i safe to do that in update_state for now?
// Look at bundling into other files, start on clean file structure for menu items
//      How to create a new file, add to compiler make and inlcude the header
// Fully understand and optimise the makefile
