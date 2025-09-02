#include "input-handler.h"

InputState initialise_input_state()
{
    InputState inputState = {
        false,
        false,
        false,
        false,
        false,
        {0, 0},
        false,
    };

    return inputState;
}

void reset_inputs(InputState *inputState)
{
    inputState->right = false;
    inputState->down = false;
    inputState->left = false;
    inputState->up = false;
    inputState->space = false;
    inputState->leftClick = false;
}

void update_inputs(InputState *inputState)
{
    inputState->mousePos = GetMousePosition();

    if (IsKeyDown(KEY_RIGHT))
    {
        inputState->right = true;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        inputState->down = true;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        inputState->left = true;
    }
    if (IsKeyDown(KEY_UP))
    {
        inputState->up = true;
    }
    if (IsKeyDown(KEY_SPACE))
    {
        inputState->space = true;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        inputState->leftClick = true;
    }
}