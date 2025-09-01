#include "raylib.h"
#include "raymath.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include <math.h>
#include <stdio.h>
#include "snake-menu.h"

MenuState initialise_menu_state(int screenWidth, int screenHeight)
{
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

    return menuState;
}

void update_menu_state(MenuState *menuState)
{
    Vector2 mousePoint = GetMousePosition();

    menuState->startButton.buttonPressed = false;
    menuState->startButton.buttonHovered = false;
    if (CheckCollisionPointRec(mousePoint, menuState->startButton.rectangle))
    {
        menuState->startButton.buttonHovered = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            menuState->startButton.buttonPressed = true;
        }
    }
}

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