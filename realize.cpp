#include "realize.h"
#include <raylib.h>
#include <iostream>
#include <math.h>


int score = 0;
int PauseState;
int PlayState;
bool game_over = false;

Vector2 posPause_Collision = {10, 10};
Vector2 posPlay_Collision = {10, 10};
Vector2 posPause = {0, 0};
Vector2 posPlay = {0, 0};
Vector2 MousePoint = {0, 0};
Vector2 pos = {0.0f,0.0f};
Vector2 Treang_1 = {0, 0};
Vector2 Treang_2 = {10, 5};
Vector2 Treang_3 = {0, 10};
Rectangle PauseRec = {0, 0, 20,20};
Rectangle PlayRec = {0, 0, 20, 20};
snake MainSnake;

food Food;

Snake_part Body[FIELD_WIDTH][FIELD_HEIGHT];
Circule Paus = {.pos_x = 10,
                .pos_y = 10,
                .radius = 10,
                .vec_Pause = {10, 10}
};

Circule Pla = {.pos_x = 10,
               .pos_y = 10,
               .radius = 10,
               .vec_Pause = {10, 10}
};

blinking blink = {.speed = 1,
                  .update_past = 0,
                  .update_presert = 0
}; // for blinking game over's table

PausePlay Pause_Play = {.pos_x = 0,
                        .pos_y = 0,
                        .active_play = false,
                        .active_pause = true,
                        .draw = true
};

void setPlayPNG(){
    Pause_Play.tex_play = LoadTexture("/Users/ekaterinacebykina/Desktop/labi_si++/KYRSACH_SNAKE/Motion/MENU/PLAY_PLAY.png");
}

void setPausePNG(){
    Pause_Play.tex_pause = LoadTexture("/Users/ekaterinacebykina/Desktop/labi_si++/KYRSACH_SNAKE/Motion/MENU/PAUSE_PAUSE.png");
}

void ParametrsPNG(){
    float Scale_Play_Width = 20 / (float)Pause_Play.tex_play.width;
    float Scale_Play_Height = 20 / (float)Pause_Play.tex_play.height;
    float Scale_Pause_Width = 20 / (float)Pause_Play.tex_pause.width;
    float Scale_Pause_Height = 20 / (float)Pause_Play.tex_pause.height;

    float scalePause;
    float scalePlay;
    scalePause = fminf(Scale_Pause_Width, Scale_Pause_Height);
    scalePlay = fminf(Scale_Play_Width, Scale_Play_Height);

    Pause_Play.scale_play = scalePlay;
    Pause_Play.scale_pause = scalePause;
}

void UnLoadPNG(){
    UnloadTexture(Pause_Play.tex_pause);
    UnloadTexture(Pause_Play.tex_play);
}

void print_scale(){
    std::cout << Pause_Play.scale_play << std::endl;
    std::cout << Pause_Play.scale_pause << std::endl;
}

// for motion start


void DrawPause(){
    DrawTextureEx(Pause_Play.tex_pause, posPause , 0, Pause_Play.scale_pause, WHITE);
}

void DrawPlay(){
    DrawTextureEx(Pause_Play.tex_play, posPlay, 0, Pause_Play.scale_play, WHITE);
}

bool active = false;
int framesCounter = 0;
//fot motion end


//void PlayPause(){

//}

Rectangle GetCanvasTarget(){
    float screen_h = (float)GetScreenHeight();
    float screen_w = (float)GetScreenWidth();
    float scale = fminf(screen_h / CANVAS_HEIGHT, screen_w / CANVAS_WIDTH);
    Rectangle rec = {0,0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale};
    return rec;
}

void InitSnake(){
    for (int i = 0; i <= MainSnake.length; i++){
        int x = MainSnake.pos_x - i * MainSnake.dir_x;
        int y = MainSnake.pos_y;
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
//    Pause_Play = {.pos_x = 0,
//                  .pos_y = 0,
//                  .active_play = false,
//                  .active_pause = true,
//                  .draw = true
//    };
    game_over = false;
    score = 0;
    MousePoint = GetMousePosition();
    MainSnake = {.dir_x = 1, // 1 - right, -1 - left, 0 - howhere
                 .dir_y = 0, // 1 - up, -1 - down, 0 - nowhere
                 .next_dir_x = 1,
                 .next_dir_y = 0,
                 .length = 2,
                 .pos_x = FIELD_WIDTH / 2, // position of heard
                 .pos_y = FIELD_HEIGHT / 2, // position of heard
                 .speed = 0.2,
                 .last_update = 0,
                 .has_eaten = false
    };
//    Pause_Play = {.pos_x = 10,
//                  .pos_y = 10,
//                  .active = false,
//                  .scale_pause = scale_pause,
//                  .scale_play = scale_play};
    for (int i = 0; i < FIELD_WIDTH; i++){
        for(int j = 0; j < FIELD_HEIGHT; j++){
            Body[i][j].lifetime = 0;
            Body[i][j].food_inside = false;
        }
    }
    InitSnake();
    DropFood();
}

void Boom(){
//    InitAudioDevice();
    active = false;
    Texture2D boom = LoadTexture("/Users/ekaterinacebykina/Desktop/labi_si++/KYRSACH_SNAKE/Motion/boom_boom.png");
    float frameWidth = (float)(boom.width/NUM_FRAMES_PER_LINE);
    float frameHeight = (float)(boom.height/NUM_LINES);
    int currentFrame = 0;
    int currentLine = 0;
    Rectangle frameRec = {0,0, frameWidth, frameHeight};
    if (game_over && !active){
        active = true;
        pos = {(float)MainSnake.pos_x, (float)MainSnake.pos_y};
        pos.x -= frameWidth;
        pos.y -= frameHeight;
    }
    if (active) {
        framesCounter++;
        if (framesCounter > 2) {
            currentFrame++;
            if (currentFrame >= NUM_FRAMES_PER_LINE) {
                currentFrame = 0;
                currentLine++;
                if (currentLine >= NUM_LINES) {
                    currentLine = 0;
                    active = false;
                }
            }
            framesCounter = 0;
        }
    }
    frameRec.x = frameWidth * currentFrame;
    frameRec.y = frameHeight * currentLine;
//    frameRec.y = frameHeight;
//    frameRec.x = frameWidth;
    ClearBackground(BLACK);
    DrawTextureRec(boom, frameRec, pos, WHITE);
    UnloadTexture(boom);
}

void CreateButtom(){}

void Drawline(){
    DrawRectangle(0,0, CANVAS_WIDTH, 20, WHITE);
    DrawText(TextFormat("score: %06i", score), CANVAS_WIDTH - 315,0, 20, BLACK);
    DrawRectangle(0, 0, 90, 20, MAGENTA);
    if (Pause_Play.active_pause && !Pause_Play.active_play){
        DrawPause();
    }else {
        if (!Pause_Play.active_pause && Pause_Play.active_play){
            DrawPlay();
        }
    }

}

void DrawBody(int i, int j){
    DrawRectangle(i * BODY_WIDTH, (j + 1) * BODY_HEIGHT, body_width, body_height, GRAY);
}

void DrawSnakeHeard(){
    DrawRectangle(MainSnake.pos_x * BODY_WIDTH, (MainSnake.pos_y +1) * BODY_HEIGHT, body_width, body_height, DARKGRAY);
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
        DrawRectangle((Food.x * BODY_WIDTH), ((Food.y + 1) * BODY_HEIGHT), body_width, body_height, RED);
    }else{
        DrawRectangle((Food.x * BODY_WIDTH) + dx, ((Food.y + 1) * BODY_HEIGHT) + dy, FOOD_WIDTH, FOOD_HEIGHT, RED);
    }
}

void DrawGame(){
    Drawline();
    DrawFood();
    DrawSnake();
    if (game_over){
        blink.update_presert = GetFrameTime();
//        Boom();
        if (blink.update_presert - blink.update_past > blink.speed) {
            blink.update_past = blink.update_presert;
            DrawRectangle((CANVAS_WIDTH / 2) - 200, (CANVAS_HEIGHT / 2) - 100, 400, 150, WHITE);
            DrawText("GAME OVER", CANVAS_WIDTH - 400, (CANVAS_HEIGHT / 2) - 50, 50, BLACK);
            DrawText("Press SPACE to restart", CANVAS_WIDTH - 380, CANVAS_HEIGHT / 2, 20, BLACK);
            DrawText(TextFormat("Your score: %05i", score), (CANVAS_WIDTH / 2) - 90, (CANVAS_HEIGHT / 2) - 80, 20,
                     BLACK);
        }else {
            DrawRectangle((CANVAS_WIDTH / 2) - 200, (CANVAS_HEIGHT / 2) - 100, 400, 150, BLACK);
            DrawText("GAME OVER", CANVAS_WIDTH - 400, (CANVAS_HEIGHT / 2) - 50, 50, WHITE);
            DrawText("Press SPACE to restart", CANVAS_WIDTH - 380, CANVAS_HEIGHT / 2, 20, WHITE);
            DrawText(TextFormat("Your score: %05i", score), (CANVAS_WIDTH / 2) - 90, (CANVAS_HEIGHT / 2) - 80, 20,
                     WHITE);
        }
    }
}

void ChekFood(){
    if (MainSnake.pos_x == Food.x && MainSnake.pos_y == Food.y && Food.sup_food){
        MainSnake.has_eaten = 2;
        score += 30;
        DropFood();
    } else{
        if (MainSnake.pos_x == Food.x && MainSnake.pos_y == Food.y && !Food.sup_food){
            MainSnake.has_eaten = 1;
            score += 10;
            DropFood();
        }
    }
}

void ChekPause(){
    if (CheckCollisionPointRec(MousePoint, PlayRec) && !Pause_Play.active_play){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            Pause_Play.active_play = true;
            Pause_Play.active_pause = false;
        }
    }else{
        if (CheckCollisionPointRec(MousePoint, PauseRec) && !Pause_Play.active_pause){
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                Pause_Play.active_play = false;
                Pause_Play.active_pause = true;
            }
        }
//        if (CheckCollisionPointCircle(MousePoint, posPlay_Collision, Pla.radius) && Pause_Play.active_play){
//            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
//            }
//            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
//                Pause_Play.active_play = false;
//                Pause_Play.active_pause = true;
//            }
//        }
    }
    MousePoint = GetMousePosition();
}

void ChekCollision(){
    if (Body[MainSnake.pos_x][MainSnake.pos_y].lifetime > 0){
        game_over = true;
    }
}

void ControlSnake(){
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && MainSnake.dir_y == 0){
        MainSnake.next_dir_y = -1;
        MainSnake.next_dir_x = 0;
    }
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && MainSnake.dir_y == 0) {
        MainSnake.next_dir_y = 1;
        MainSnake.next_dir_x = 0;
    }
    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && MainSnake.dir_x == 0) {
        MainSnake.next_dir_x = -1;
        MainSnake.next_dir_y = 0;
    }
    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && MainSnake.dir_x == 0) {
        MainSnake.next_dir_x = 1;
        MainSnake.next_dir_y = 0;
    }

}

void MoveSnake(){
    ChekPause();
    MainSnake.last_update += GetFrameTime();
    if (MainSnake.last_update >= MainSnake.speed){
        MainSnake.last_update = 0;
    } else{
        return;
    }
    if (MainSnake.has_eaten == 2){
        MainSnake.has_eaten--;
        MainSnake.length++;
    }else {
        if (MainSnake.has_eaten == 1){
            MainSnake.has_eaten--;
            MainSnake.length++;
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

    MainSnake.dir_x = MainSnake.next_dir_x;
    MainSnake.dir_y = MainSnake.next_dir_y;

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
        MainSnake.pos_y = FIELD_HEIGHT -1;
    }

    ChekCollision();

    Body[MainSnake.pos_x][MainSnake.pos_y].lifetime = MainSnake.length;
}

void UpdateGame(){
    if (game_over){
        if (IsKeyPressed(KEY_SPACE)){
            setup();
        }
        return;
    }
    if (Pause_Play.active_play && !Pause_Play.active_pause){
        ChekPause();
        return;
    }
    MoveSnake();
    ChekFood();
    ControlSnake();
    MousePoint = GetMousePosition();
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
//        DrawGame();
//        EndTextureMode();
//        DrawTexturePro(CANVAS.texture, canvas_field, GetCanvasTarget(), ZER, 0, WHITE);
//        EndDrawing();
//    }
//
//    CloseWindow();
//
//}