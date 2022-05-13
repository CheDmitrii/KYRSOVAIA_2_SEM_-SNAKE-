#ifndef KYRSACH_SNAKE_REALIZE_H
#define KYRSACH_SNAKE_REALIZE_H

#include <raylib.h>
#include <iostream>
#include <cmath>

#define CANVAS_WIDTH 500
#define CANVAS_HEIGHT 360
#define BODY_WIDTH 20
#define BODY_HEIGHT 20
#define body_width 19.9
#define body_height 19.9
#define FOOD_WIDTH 12.5
#define FOOD_HEIGHT 12.5
#define NUM_FRAMES_PER_LINE 5
#define NUM_LINES 5
#define NUM_FRAMES 3

const int FIELD_WIDTH = CANVAS_WIDTH / BODY_WIDTH;
const int FIELD_HEIGHT  = (CANVAS_HEIGHT / BODY_HEIGHT) - 1;




struct Snake_part{
    int lifetime;            //number of cell of snake
    bool food_inside;        // has food or not
};
struct snake{
    int dir_x;                // snake's direction on OX (1 - right, -1 - left, 0 - howhere)
    int dir_y;                // snake's direction on OY (1 - up, -1 - down, 0 - nowhere)
    int next_dir_x;
    int next_dir_y;
    int length;               // length of snake
    int pos_x;                // position snake's heard on OX
    int pos_y;                // position snake's heard on OY
    float speed;              // in seconds till next move
    float last_update;        // time since last update
    int has_eaten;            // has or has't eaten
    Color heard_color;        // color of snake's heard
    Color body_color;         // color of snake's body
    int speed_table;
};
struct food {
    int x;                    // position on OX
    int y;                    // position on OY
    bool sup_food;
};
struct blinking{
    double speed;
    double update_past;
    double update_presert;
};
struct settings{
    Texture2D tex;
    int settings_state;
    double scale_settings;
    int pos_x;
    int pos_y;
    bool active;
};
struct PausePlay{
    int pos_x;
    int pos_y;
    double scale_pause;
    double scale_play;
    bool active_play;
    bool active_pause;
    Texture2D tex_play;
    Texture2D tex_pause;
    int pause_state;
    int play_state;
};
struct Button{
    int posRec_x;
    int posRec_y;
    int posText_x;
    int posText_y;
    int width;
    int height;
    char name[64];
    bool active;
    int state;
};
struct Speed{
    int speed_output;
    float speed_intput;
};
void CreateButtom();
void DropFood();
Rectangle GetCanvasTarget();  // for scale window
void DrawSnakeBody();
void setup();
void InitSnake();             // creation snake
void DrawBody(int i, int j);
void DrawSnakeHeard();
void DrawGame();
void Game();
void MoveSnake();
void UpdateGame();
void ControlSnake();
void DrawFood();
void DrawSnake();
void ChekCollision();
void Boom();
void Drawline();
void PlayPause();
void Draw_Pause_Play();
void ParametrsPNG();
void UnLoadPNG();
void setPlayPNG();
void setPausePNG();
void DrawPause();
void print_scale();
void DrawPlay();
void ChekPause();
void DrawPlayBlink();
void setSettingsPNG();
void DrawSetting();
void DrawButtonExit();
void DrawButtonRestart();
void DrawButtonParametrsSnake();
void DrawButtonBackSetting();
void DrawButtonMenuSetting();
void DrawSetting_Buttons();
bool exitActive();

#endif //KYRSACH_SNAKE_REALIZE_H
