#include "raylib.h"
#include "raymath.h"
#include "stb_ds.h"
#include <math.h>
#include <stdio.h>

#include "snake-menu.h"
#include "snake-game.h"
#include "input-handler.h"

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
    PlayingState playingState;

} GameState;

void update_state(GameState *gameState, InputState *inputState)
{
    Vector2 mousePoint = GetMousePosition();
    if (gameState->state == MENU)
    {
        update_menu_state(&gameState->menuState, *inputState);

        if (gameState->menuState.startButton.buttonPressed == true)
        {
            gameState->state = PLAYING;
        }
    }

    if (gameState->state == PLAYING)
    {
        update_playing_state(&gameState->playingState, *inputState);
    }
};

void render(const GameState *gameState)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (gameState->state == MENU)
    {
        draw_menu(&gameState->menuState);
    }
    if (gameState->state == PLAYING)
    {
        draw_playing(&gameState->playingState);
    }
    EndDrawing();
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    float frameTimer = 0;

    State state = MENU;
    MenuState menuState = initialise_menu_state(screenWidth, screenHeight);
    PlayingState playingState = initialise_playing_state();

    GameState gameState = {
        state,
        menuState,
        playingState};

    InputState inputState = initialise_input_state();

    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        frameTimer += GetFrameTime();

        update_inputs(&inputState);

        if (frameTimer >= 0.1)
        {
            update_state(&gameState, &inputState);
            reset_inputs(&inputState);
            frameTimer = 0;
        }
        render(&gameState);
    }

    CloseWindow();

    return 0;
}

// ToDo
// Think about input handling, or am i safe to do that in update_state for now?
// Make the menu pretty
// - Add title
// - Make button nicer
// Start Playing State
// - Make grid cleaner
// - render snake and move it
// - Make Score counter
// - Make apple sprite
// - Make snake sprites
// Understand how to do good logging and debugging

// Fully understand and optimise the makefile
