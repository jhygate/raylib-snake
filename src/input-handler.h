#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "raylib.h"
#include "raymath.h"

#include "stb_ds.h"

typedef struct
{
    bool up;
    bool right;
    bool down;
    bool left;

    bool space;

    Vector2 mousePos;
    bool leftClick;

} InputState;

InputState initialise_input_state();
void reset_inputs(InputState *inputState);
void update_inputs(InputState *inputState);

#endif // INPUT_HANDLER_H