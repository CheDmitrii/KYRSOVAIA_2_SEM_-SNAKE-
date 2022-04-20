//
// Created by Екатерина Чебыкина on 12.04.2022.
//

#ifndef KYRSACH_SNAKE_REALIZE_H
#define KYRSACH_SNAKE_REALIZE_H

#include <raylib.h>

#define CANVAS_WIDTH 600
#define CANVAS_HEIGHT 400
#define BODY_WIDTH 15
#define BODY_HEIGHT 15
#define body_width 14.9
#define body_height 14.9
#define FOOD_WIDTH 10
#define FOOD_HEIGHT 10

const int FIELD_WIDTH = CANVAS_WIDTH / BODY_WIDTH;
const int FIELD_HEIGHT  = CANVAS_HEIGHT / BODY_HEIGHT;


struct Snake_part{
    int lifetime; //number of cell of snake
    bool food_inside; // has food or not
};
struct snake_{
    int dir_x;         // snake's direction on OX (1 - right, -1 - left, 0 - howhere)
    int dir_y;         // snake's direction on OY (1 - up, -1 - down, 0 - nowhere)
    int length;        // length of snake
    int pos_x;         // position snake's heard on OX
    int pos_y;         // position snake's heard on OY
    float speed;       // in seconds till next move
    float last_update; // time since last update
    bool has_eaten;    //has or has't eaten
};
struct food {
    int x;             // position on OX
    int y;             // position on OY
    bool sup_eat;
};
void CreateButtom();
void DropFood();
Rectangle GetCanvasTarget();
void DrawSnakeBody();
void setup();
snake_ InitSnake();
void DrawBody(int i, int j);
void DrawSnakeHeard();
void Draw();
void Game();
void MoveSnake();
void Update();
void ControlSnake();
void DrawFood();
void DrawSnake();

#endif //KYRSACH_SNAKE_REALIZE_H
