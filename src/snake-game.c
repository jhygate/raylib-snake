#include "snake-game.h"

#include <stdio.h>

Vector2 directionVectors[] = {
    {0, -1}, // UP
    {1, 0},  // RIGHT
    {0, 1},  // DOWN
    {-1, 0}  // LEFT
};

PlayingState initialise_playing_state()
{
    Snake snake = {
        {0, 0},
        RIGHT};

    PlayingState playingState = {10, 10, snake};

    return playingState;
}

void draw_grid(int rows, int cols)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const int cellWidth = (int)floor(screenWidth / cols);
    const int cellHeight = (int)floor(screenHeight / rows);

    for (int x = 0; x < rows; x++)
    {

        for (int y = 0; y < cols; y++)
        {

            Rectangle rectangleBorder = {
                x * cellWidth,
                y * cellHeight,
                cellWidth,
                cellHeight};

            Rectangle rectangleInner = {
                x * cellWidth + 1,
                y * cellHeight + 1,
                cellWidth - 2,
                cellHeight - 2};
            DrawRectangleRec(rectangleBorder, BLACK);
            DrawRectangleRec(rectangleInner, WHITE);
        }
    }
}

void draw_snake(PlayingState *playingState)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const int cellWidth = (int)floor(screenWidth / playingState->cols);
    const int cellHeight = (int)floor(screenHeight / playingState->rows);

    Rectangle snakeHead = {
        playingState->snake.head.x * cellWidth + 1,
        playingState->snake.head.y * cellHeight + 1,
        5,
        5,
    };

    DrawRectangleRec(snakeHead, RED);
}

void draw_playing(PlayingState *playingState)
{
    draw_grid(playingState->rows,
              playingState->cols);

    draw_snake(playingState);
}

void update_playing_state(PlayingState *playingState, InputState inputState)
{
    if (inputState.right)
    {
        playingState->snake.direction = RIGHT;
    }
    if (inputState.down)
    {
        playingState->snake.direction = DOWN;
    }
    if (inputState.left)
    {
        playingState->snake.direction = LEFT;
    }
    if (inputState.up)
    {
        playingState->snake.direction = UP;
    }

    if (inputState.space)
    {
        Vector2 move = directionVectors[playingState->snake.direction];
        playingState->snake.head.x += move.x;
        playingState->snake.head.y += move.y;
    }
}