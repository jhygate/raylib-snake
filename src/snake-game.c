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
        NULL,
        RIGHT};

    Apple apple = {
        {5, 5}};

    PlayingState playingState = {20, 20, snake, apple};

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

void draw_snake(const PlayingState *playingState)
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

    for (int tailIndex = 0; tailIndex < arrlen(playingState->snake.tail); tailIndex++)
    {
        Rectangle snakeTail = {
            playingState->snake.tail[tailIndex].x * cellWidth + 1,
            playingState->snake.tail[tailIndex].y * cellHeight + 1,
            5,
            5,
        };
        DrawRectangleRec(snakeTail, GREEN);
    }

    DrawRectangleRec(snakeHead, GREEN);
}

void draw_apples(const PlayingState *playingState)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const int cellWidth = (int)floor(screenWidth / playingState->cols);
    const int cellHeight = (int)floor(screenHeight / playingState->rows);

    for (int i = 0; i < 1; i++)
    {

        Rectangle appleRect = {
            playingState->apple.pos.x * cellWidth + 1,
            playingState->apple.pos.y * cellHeight + 1,
            5,
            5,
        };

        DrawRectangleRec(appleRect, RED);
    }
}

void draw_playing(const PlayingState *playingState)
{
    draw_grid(playingState->rows,
              playingState->cols);

    draw_apples(playingState);
    draw_snake(playingState);
}

void update_playing_state(PlayingState *playingState, InputState inputState)
{

    if (inputState.space)
    {
        Vector2 move = directionVectors[playingState->snake.direction];
        playingState->snake.head.x += move.x;
        playingState->snake.head.y += move.y;
    }

    if ((playingState->snake.head.x == playingState->apple.pos.x) &&
        (playingState->snake.head.y == playingState->apple.pos.y))
    {
        playingState->apple.pos.x = 0;
        playingState->apple.pos.y = 0;
    }

    if (inputState.right & (playingState->snake.direction != LEFT))
    {
        playingState->snake.direction = RIGHT;
    }
    if (inputState.down & (playingState->snake.direction != UP))
    {
        playingState->snake.direction = DOWN;
    }
    if (inputState.left & (playingState->snake.direction != RIGHT))
    {
        playingState->snake.direction = LEFT;
    }
    if (inputState.up & (playingState->snake.direction != DOWN))
    {
        playingState->snake.direction = UP;
    }
}

// ToDo:
// Create tail object
//  - Work out how to initialise playingState with variable size list
// Make apple move to random pos that is not occupied
