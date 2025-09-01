#include "raylib.h"
#include "raymath.h"
#include "stb_ds.h"
#include <math.h>
#include <stdio.h>

#include "snake-menu.h"

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
    State state;
    MenuState menuState;

} GameState;

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
    if (gameState->state == MENU)
    {
        update_menu_state(&gameState->menuState);

        if (gameState->menuState.startButton.buttonPressed == true)
        {
            gameState->state = PLAYING;
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
    MenuState menuState = initialise_menu_state(screenWidth, screenHeight);

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
// Fully understand and optimise the makefile
