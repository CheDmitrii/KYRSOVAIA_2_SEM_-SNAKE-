#include "realize.h"
#include <raylib.h>
#include <iostream>
#include <math.h>

// TODO: control
// TODO: game over

Snake_part Body[FIELD_WIDTH][FIELD_HEIGHT];

//};
//        .has_eaten = false
//        .last_update = 0,
//        .speed = 0.2,
//        .pos_y = FIELD_HEIGHT / 2, // position of heard
//        .pos_x = FIELD_WIDTH / 2, // position of heard
//        .length = 2,
//        .dir_y = 0, // 1 - up, -1 - down, 0 - nowhere
//        .dir_x = 1, // 1 - right, -1 - left, 0 - howhere
//= {

snake MainSnake;

food Food;
bool game_over = false;

void InitSnake(){
    for (int i = 0; i < MainSnake.length; i++){
        int x = MainSnake.pos_x - MainSnake.dir_x * i;
        int y = MainSnake.pos_y - MainSnake.dir_y * i;
        Body[x][y].lifetime = MainSnake.length - i;
    }
}

void DropFood(){
    int x, y;
    int sup = GetRandomValue(-5, 15);
    do {
        x = GetRandomValue(0, FIELD_WIDTH - 1);
        y = GetRandomValue(0, FIELD_HEIGHT - 1);
    } while (Body[x][y].lifetime > 0);
    Food.x = x;
    Food.y = y;
    if (sup < 0){
        Food.sup_food = true;
    } else
        Food.sup_food = false;
}

void setup(){
    game_over = false;
    MainSnake = {
            .dir_x = 1, // 1 - right, -1 - left, 0 - howhere
            .dir_y = 0, // 1 - up, -1 - down, 0 - nowhere
            .length = 2,
            .pos_x = FIELD_WIDTH / 2, // position of heard
            .pos_y = FIELD_HEIGHT / 2, // position of heard
            .speed = 0.2,
            .last_update = 0,
            .has_eaten = false
    };
    for (int i = 0; i < FIELD_WIDTH; i++){
        for(int j = 0; j < FIELD_HEIGHT; j++){
            Body[i][j].lifetime = 0;
            Body[i][j].food_inside = false;
        }
    }
    InitSnake();
    DropFood();
}

void CreateButtom(){}

Rectangle GetCanvasTarget(){
    float screen_h = (float)GetScreenHeight();
    float screen_w = (float)GetScreenWidth();
    float scale = fminf(screen_h / CANVAS_HEIGHT, screen_w / CANVAS_WIDTH);
    Rectangle rec = {0,0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale};
    return rec;
}

void DrawBody(int i, int j){
    DrawRectangle(i * BODY_WIDTH, j * BODY_HEIGHT, body_width, body_height, BROWN);
}

void DrawSnakeHeard(){
    DrawRectangle(MainSnake.pos_x * BODY_WIDTH, MainSnake.pos_y * BODY_HEIGHT, body_width, body_height, DARKBROWN);
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

void DrawSnake(){
    DrawSnakeBody();
    DrawSnakeHeard();
}

void DrawFood(){
    double dx = (BODY_WIDTH - FOOD_WIDTH) / 2;
    double dy = (BODY_HEIGHT - FOOD_HEIGHT) / 2;
    if (Food.sup_food) {
        DrawRectangle((Food.x * BODY_WIDTH), (Food.y * BODY_HEIGHT), body_width, body_height, RED);
    }else{
        DrawRectangle((Food.x * BODY_WIDTH) + dx, (Food.y * BODY_HEIGHT) + dy, FOOD_WIDTH, FOOD_HEIGHT, RED);
    }
}

void Draw(){
    DrawFood();
    DrawSnake();
}

void ChekFood(){
    if (MainSnake.pos_x == Food.x && MainSnake.pos_y == Food.y && Food.sup_food){
        MainSnake.length += 2;
        MainSnake.has_eaten = 2;
        DropFood();
    } else{
        if (MainSnake.pos_x == Food.x && MainSnake.pos_y == Food.y && !Food.sup_food){
            MainSnake.length++;
            MainSnake.has_eaten = 2;
            DropFood();
        }
    }
}

void ChekCollision(){
    if (Body[MainSnake.pos_x][MainSnake.pos_y].lifetime < MainSnake.length){
        game_over = true;
    }
}

void ControlSnake(){
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && MainSnake.dir_y == 0){
        MainSnake.dir_y = 1;
        MainSnake.dir_x = 0;
    }
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && MainSnake.dir_y == 0) {
        MainSnake.dir_y = -1;
        MainSnake.dir_x = 0;
    }
    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && MainSnake.dir_x == 0) {
        MainSnake.dir_x = -1;
        MainSnake.dir_y = 0;
    }
    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && MainSnake.dir_x == 0) {
        MainSnake.dir_x = 1;
        MainSnake.dir_y = 0;
    }

}

void MoveSnake(){
    MainSnake.last_update += GetFrameTime();
    if (MainSnake.last_update >= MainSnake.speed){
        MainSnake.last_update = 0;
    } else{
        return;
    }
    if (MainSnake.has_eaten == 2){
        MainSnake.has_eaten--;
    }else {
        if (MainSnake.has_eaten == 1){
            MainSnake.has_eaten--;
        }
        else {
            for (int i = 0; i < FIELD_WIDTH; i++) {
                for (int j = 0; j < FIELD_HEIGHT; j++) {
                    if (Body[i][j].lifetime > 0) {
                        Body[i][j].lifetime--;
                    }
                }
            }
        }
    }
    MainSnake.pos_x += MainSnake.dir_x;
    MainSnake.pos_y += MainSnake.dir_y;

    if (MainSnake.pos_x >= FIELD_WIDTH){
        MainSnake.pos_x = 0;
    }
    if (MainSnake.pos_x < 0){
        MainSnake.pos_x = FIELD_WIDTH - 1;
    }
    if (MainSnake.pos_y >= FIELD_HEIGHT){
        MainSnake.pos_y = 0;
    }
    if (MainSnake.pos_y < 0){
        MainSnake.pos_y = FIELD_HEIGHT - 1;
    }

//    ChekCollision();

    Body[MainSnake.pos_x][MainSnake.pos_y].lifetime = MainSnake.length;
}

void Update(){
    if (game_over){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("GAME OVER", CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 50,MAGENTA);
        EndDrawing();
        return;
    }
    MoveSnake();
    ChekFood();
    ControlSnake();
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