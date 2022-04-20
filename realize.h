//
// Created by Екатерина Чебыкина on 12.04.2022.
//

#ifndef KYRSACH_SNAKE_REALIZE_H
#define KYRSACH_SNAKE_REALIZE_H

#include <raylib.h>

#define WIND_WIDTH  650
#define WIND_HEIGHT  400
#define CANVAS_WIDTH 650
#define CANVAS_HEIGHT 400
#define BODY_WIDTH 15
#define BODY_HEIGHT 15

const int FIELD_WIDTH = CANVAS_WIDTH / BODY_WIDTH;
const int FIELD_HEIGHT  = CANVAS_HEIGHT / BODY_HEIGHT;


struct Snake_part{
    int lifetime;
    bool food_inside;
};
struct snake_{
    int dir_x;
    int dir_y;
    int length;
    int pos_x;
    int pos_y;
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

#endif //KYRSACH_SNAKE_REALIZE_H
