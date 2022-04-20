//
// Created by Екатерина Чебыкина on 12.04.2022.
//

#include "realize.h"
#include <raylib.h>
#include <iostream>
#include <math.h>



snake_ MainSnake = {
        .dir_x = 1,
        .dir_y = 0,
        .length = 2,
        .pos_x = FIELD_WIDTH / 2,
        .pos_y = FIELD_HEIGHT / 2
};

Snake_part Body[FIELD_WIDTH][FIELD_HEIGHT];

snake_ InitSnake(){
    for (int i = 0; i < MainSnake.length; i++){
        int x = MainSnake.pos_x - MainSnake.dir_x * i;
        int y = MainSnake.pos_y - MainSnake.dir_y * i;
        Body[x][y].lifetime = MainSnake.length - i;
    }
    return MainSnake;
}

void setup(){
    for (int i = 0; i < FIELD_WIDTH; i++){
        for(int j = 0; j < FIELD_HEIGHT; j++){
            Body[i][j].lifetime = 0;
            Body[i][j].food_inside = false;
        }
    }
    InitSnake();
}


void CreateButtom(){}

void DropFood(){}

Rectangle GetCanvasTarget(){
    float screen_h = (float)GetScreenHeight();
    float screen_w = (float)GetScreenWidth();
    float scale = fminf(screen_h / CANVAS_HEIGHT, screen_w / CANVAS_WIDTH);
    Rectangle rec = {0,0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale};
    return rec;
}



void DrawBody(int i, int j){
    DrawRectangle(i * BODY_WIDTH, j * BODY_HEIGHT, BODY_WIDTH, BODY_HEIGHT, BROWN);
}

void DrawSnakeHeard(){
    DrawRectangle(MainSnake.pos_x * BODY_WIDTH, MainSnake.pos_y * BODY_HEIGHT, BODY_WIDTH, BODY_HEIGHT, DARKBROWN);
}

void DrawSnakeBody(){
    for (int i = 0; i < FIELD_WIDTH; i++){
        for (int j = 0; j < FIELD_HEIGHT; j++){
            if (Body[i][j].lifetime > 0){
                DrawBody(i, j);
            }
        }
    }
}

void Draw(){
    DrawSnakeBody();
    DrawSnakeHeard();
}

//Vector2 ZER = {0,0};
//
//void Game(){
//    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
//    InitWindow(WIND_WIDTH, WIND_HEIGHT, "SNAKE");
//    SetTargetFPS(60);
//    RenderTexture2D CANVAS = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
//    Rectangle canvas_field = {0, 0, (float)CANVAS.texture.width, (float)CANVAS.texture.height};
//    SetTextureFilter(CANVAS.texture, TEXTURE_FILTER_POINT);
//    setup();
//
//    while (!WindowShouldClose()){
//        BeginDrawing();
//        ClearBackground(GREEN);
//        BeginTextureMode(CANVAS);
//        ClearBackground(BLACK);
//        Draw();
//        EndTextureMode();
//        DrawTexturePro(CANVAS.texture, canvas_field, GetCanvasTarget(), ZER, 0, WHITE);
//        EndDrawing();
//    }
//
//    CloseWindow();
//
//}