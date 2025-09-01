/* snake-menu.c */
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

MenuState initialise_menu_state(int screenWidth, int screenHeight);
void update_menu_state(MenuState *menuState);
void draw_button(Button button);
void draw_menu(const MenuState *menuState);
