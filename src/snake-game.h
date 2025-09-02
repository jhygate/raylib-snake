#include "raylib.h"
#include "raymath.h"

#include "stb_ds.h"
#include "input-handler.h"

typedef enum
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
} Direction;

typedef struct
{
    Vector2 head;
    Direction direction;
} Snake;

typedef struct
{
    int rows;
    int cols;
    Snake snake;
} PlayingState;

PlayingState initialise_playing_state();
void draw_grid(int rows, int cols);
void draw_playing(const PlayingState *playingState);
void update_playing_state(PlayingState *playingState, InputState inputState);
void draw_snake(const PlayingState *playingState);