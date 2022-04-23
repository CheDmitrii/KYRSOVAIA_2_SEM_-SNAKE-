//
// Created by Екатерина Чебыкина on 12.04.2022.
//

#ifndef KYRSACH_SNAKE_REALIZE_H
#define KYRSACH_SNAKE_REALIZE_H

#include <raylib.h>

#define CANVAS_WIDTH 500
#define CANVAS_HEIGHT 360
#define BODY_WIDTH 20
#define BODY_HEIGHT 20
#define body_width 19.9
#define body_height 19.9
#define FOOD_WIDTH 12.5
#define FOOD_HEIGHT 12.5

const int FIELD_WIDTH = CANVAS_WIDTH / BODY_WIDTH;
const int FIELD_HEIGHT  = CANVAS_HEIGHT / BODY_HEIGHT;


struct Snake_part{
    int lifetime;            //number of cell of snake
    bool food_inside;        // has food or not
};
struct snake{
    int dir_x;                // snake's direction on OX (1 - right, -1 - left, 0 - howhere)
    int dir_y;                // snake's direction on OY (1 - up, -1 - down, 0 - nowhere)
    int length;               // length of snake
    int pos_x;                // position snake's heard on OX
    int pos_y;                // position snake's heard on OY
    float speed;              // in seconds till next move
    float last_update;        // time since last update
    int has_eaten;            //has or has't eaten
};
struct food {
    int x;                    // position on OX
    int y;                    // position on OY
    bool sup_food;
};
void CreateButtom();
void DropFood();
Rectangle GetCanvasTarget();  // for scale window
void DrawSnakeBody();
void setup();
void InitSnake();             // creation snake
void DrawBody(int i, int j);
void DrawSnakeHeard();
void Draw();
void Game();
void MoveSnake();
void Update();
void ControlSnake();
void DrawFood();
void DrawSnake();
void ChekCollision();

#endif //KYRSACH_SNAKE_REALIZE_H
