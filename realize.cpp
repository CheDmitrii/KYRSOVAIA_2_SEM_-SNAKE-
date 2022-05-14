#include "realize.h"
#include <raylib.h>
#include <iostream>
#include <math.h>

int score = 0;
bool game_over = false;

Vector2 posPause = {0, 0};
Vector2 posPlay = {0, 0};
Vector2 posSet = {22, 0};
Vector2 MousePoint = {0, 0};
Vector2 pos = {0.0f,0.0f};

Rectangle Exit = {190, 220, 120, 40};

Snake_part Body[FIELD_WIDTH][FIELD_HEIGHT];

Snake_part Snake_menu[FIELD_WIDTH][FIELD_HEIGHT + 1];

food Food;

snake MainSnake = {.body_color = GRAY,
                   .heard_color = DARKGRAY
};

Button exit_Setting_but = {.name = "EXIT",
                   .posRec_x = 190,
                   .posRec_y = 230,
                   .posText_x = 200,
                   .posText_y = 230,
                   .width = 120,
                   .height = 40,
                   .active = false
};

Button exit_Menu_but = {.name = "EXIT",
                        .posRec_x = 260,
                        .posRec_y = 200,
                        .width = 100,
                        .height = 40,
                        .posText_x = 281,
                        .posText_y = 207,
                        .active = false
};

Button start_Menu_but = {.name = "START",
                         .posRec_x = 140,
                         .posRec_y = 200,
                         .width = 100,
                         .height = 40,
                         .posText_x = 147,
                         .posText_y = 207,
                         .active = false
};

Button restart_but = {.name = "RESTART",
                      .posRec_x = 190,
                      .posRec_y = 130,
                      .posText_x = 195,
                      .posText_y = 140,
                      .width = 120,
                      .height = 40,
                      .active = false
};

Button parametrsSnake_but = {.name = "PARAMETRS",
                             .posRec_x = 190,
                             .posRec_y = 180,
                             .posText_x = 193,
                             .posText_y = 190,
                             .width = 120,
                             .height = 40,
                             .active = false
};

Button menuSetting_but = {.name = "MENU",
                          .posRec_x = 190,
                          .posRec_y = 80,
                          .posText_x = 193,
                          .posText_y = 80,
                          .width = 120,
                          .height = 40,
                          .active = true
};

Button backSet_but = {.name = "BACK",
                   .posRec_x = 133,
                   .posRec_y = 68,
                   .posText_x = 133,
                   .posText_y = 68,
                   .width = 50,
                   .height = 20,
                   .active = false
};

Button backPar_but = {.name = "BACK",
                      .posRec_x = 133,
                      .posRec_y = 68,
                      .posText_x = 133,
                      .posText_y = 68,
                      .width = 50,
                      .height = 20,
                      .active = false,
                      .active_additionally = false
};

Button speed_but = {.name = "SPEED",
                    .posRec_x = 190,
                    .posRec_y = 80,
                    .width = 120,
                    .height = 40,
                    .posText_x = 193,
                    .posText_y = 81
};

Button speedPlus_but = {.name = "+",
                        .posRec_x = 255,
                        .posRec_y = 180,
                        .width = 55,
                        .height = 40,
                        .active = false
};

Button speedMinus_but = {.name = "-",
                         .posRec_x = 190,
                         .posRec_y = 180,
                         .width = 55,
                         .height = 40,
                         .active = false
};

blinking blink_game_over = {.speed = 1,
                            .update_past = 0,
                            .update_presert = 0
}; // for blinking gameover's screens

blinking blink_pause = {.speed = 1,
                        .update_past = 0,
                        .update_presert = 0
}; // for blinking pause's screen

blinking blink_menu = {.speed = 1,
                       .update_past = 0,
                       .update_presert = 0
}; // for blinking menu's screen

PausePlay Pause_Play = {.pos_x = 0,
                        .pos_y = 0,
                        .active_play = false,
                        .active_pause = true,
                        .pause_state = 0,
                        .play_state = 0
};

settings Setting = {.pos_x = 22,
                    .pos_y = 0,
                    .settings_state = 0,
                    .active = false
};

Speed Snake_speed = {.speed_intput = 0.2,
                     .speed_output = 50,
                     .speed_calculations = 20
};

void setPlayPNG(){
    Pause_Play.tex_play = LoadTexture("/Users/ekaterinacebykina/Desktop/labi_si++/KYRSACH_SNAKE/Motion/MENU/PLAY_PLAY.png");
}

void setPausePNG(){
    Pause_Play.tex_pause = LoadTexture("/Users/ekaterinacebykina/Desktop/labi_si++/KYRSACH_SNAKE/Motion/MENU/PAUSE_PAUSE.png");
}

void setSettingsPNG(){
    Setting.tex = LoadTexture("/Users/ekaterinacebykina/Desktop/labi_si++/KYRSACH_SNAKE/Motion/MENU/setting_22.png");
}

void ParametrsPNG(){
    float scale_Button_Width = (float)GetScreenWidth() / FIELD_WIDTH;
    float scale_Button_Height = (float)GetScreenHeight() / FIELD_HEIGHT;

    float Scale_Play_Width = scale_Button_Width / (float)Pause_Play.tex_play.width;
    float Scale_Play_Height = scale_Button_Height / (float)Pause_Play.tex_play.height;
    float Scale_Pause_Width = scale_Button_Width / (float)Pause_Play.tex_pause.width;
    float Scale_Pause_Height = scale_Button_Height / (float)Pause_Play.tex_pause.height;

    float Scale_Setting_Width = scale_Button_Width / (float)Setting.tex.width;
    float Scale_Setting_Height = scale_Button_Height / (float)Setting.tex.height;

    float scaleSetting;
    scaleSetting = fminf(Scale_Setting_Width, Scale_Setting_Height);

    Setting.scale_settings = scaleSetting;


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
    UnloadTexture(Setting.tex);
}

void DrawButtonExit(){
    if (exit_Setting_but.state == 1 || exit_Setting_but.state == 2){
        DrawRectangle(exit_Setting_but.posRec_x, exit_Setting_but.posRec_y, exit_Setting_but.width, exit_Setting_but.height, BLACK);
        DrawText(exit_Setting_but.name, exit_Setting_but.posText_x, exit_Setting_but.posText_y, 40, WHITE);
    }else {
        DrawRectangle(exit_Setting_but.posRec_x, exit_Setting_but.posRec_y, exit_Setting_but.width, exit_Setting_but.height, RED);
        DrawText(exit_Setting_but.name, exit_Setting_but.posText_x, exit_Setting_but.posText_y, 40, BLACK);
    }
}

void DrawButtonRestart(){
    if (restart_but.state == 1 || restart_but.state == 2){
        DrawRectangle(restart_but.posRec_x, restart_but.posRec_y, restart_but.width, restart_but.height, BLACK);
        DrawText(restart_but.name, restart_but.posText_x, restart_but.posText_y, 23, WHITE);
    }else {
        DrawRectangle(restart_but.posRec_x, restart_but.posRec_y, restart_but.width, restart_but.height, RED);
        DrawText(restart_but.name, restart_but.posText_x, restart_but.posText_y, 23, BLACK);
    }
}

void DrawButtonParametrsSnake(){
    if (parametrsSnake_but.state == 1 || parametrsSnake_but.state == 2){
        DrawRectangle(parametrsSnake_but.posRec_x, parametrsSnake_but.posRec_y, parametrsSnake_but.width, parametrsSnake_but.height, BLACK);
        DrawText(parametrsSnake_but.name, parametrsSnake_but.posText_x, parametrsSnake_but.posText_y, 19, WHITE);
    }else {
        DrawRectangle(parametrsSnake_but.posRec_x, parametrsSnake_but.posRec_y, parametrsSnake_but.width, parametrsSnake_but.height, RED);
        DrawText(parametrsSnake_but.name, parametrsSnake_but.posText_x, parametrsSnake_but.posText_y, 19, BLACK);
    }

}

void DrawButtonMenuSetting(){
    if (menuSetting_but.state == 1 || menuSetting_but.state == 2){
        DrawRectangle(190, 80, 120, 40, BLACK);
        DrawText(menuSetting_but.name, 193, 80, 40, WHITE);
    }else {
        DrawRectangle(190, 80, 120, 40, RED);
        DrawText(menuSetting_but.name, 193, 80, 40, BLACK);
    }
}

void DrawButtonBackSetting(){
    if (backSet_but.state == 1 || backSet_but.state == 2){
        DrawRectangle(backSet_but.posRec_x, backSet_but.posRec_y, backSet_but.width, backSet_but.height, BLACK);
        DrawText(backSet_but.name, backSet_but.posText_x, backSet_but.posText_y, 19, WHITE);
    }else {
        DrawRectangle(backSet_but.posRec_x, backSet_but.posRec_y, backSet_but.width, backSet_but.height, RED);
        DrawText(backSet_but.name, backSet_but.posText_x, backSet_but.posText_y, 19, BLACK);
    }
}

void DrawButtonSpeedText(){
    DrawRectangle(speed_but.posRec_x, speed_but.posRec_y, speed_but.width, speed_but.height, RED);
    DrawText(speed_but.name, speed_but.posText_x, speed_but.posText_y, 34, BLACK);
}

void DrawSpeedScreen(){
//    DrawRectangle(190, 130, 120, 40, RED);
    DrawRectangle(190, 130, 6, 40, BLACK);
    DrawRectangle(190, 130, 120, 6, BLACK);
    DrawRectangle(190 + 120 - 6, 130, 6, 40, BLACK);
    DrawRectangle(190, 130 + 40 - 6, 120, 6, BLACK);
    if(Snake_speed.speed_output == 100){
        DrawText("MAX", 218, 136, 30, BLACK);
    } else{
        if(Snake_speed.speed_output == 0){
            DrawText("MIN", 222, 136, 30, BLACK);
        } else{
            DrawText(TextFormat("%03i", Snake_speed.speed_output), 225, 136, 30, BLACK);
        }
    }
}

void DrawSpeedUP(){
    if (speedPlus_but.state == 1 || speedPlus_but.state == 2){
        DrawRectangle(255, 180, 55, 40, BLACK);
        DrawRectangle(255, 180, 6, 40, RED);
        DrawRectangle(255, 180, 55, 6, RED);
        DrawRectangle(255 + 55 - 6, 180, 6, 40, RED);
        DrawRectangle(255, 180 + 40 - 6, 55, 6, RED);
        DrawText("+", 255 + 17, 181, 40, WHITE);
    }else {
        DrawRectangle(255, 180, 55, 40, RED);
        DrawRectangle(255, 180, 6, 40, BLACK);
        DrawRectangle(255, 180, 55, 6, BLACK);
        DrawRectangle(255 + 55 - 6, 180, 6, 40, BLACK);
        DrawRectangle(255, 180 + 40 - 6, 55, 6, BLACK);
        DrawText("+", 255 + 17, 181, 40, BLACK);
    }
}

void DrawSpeedDOWN(){
    if (speedMinus_but.state == 1 || speedMinus_but.state ==2){
        DrawRectangle(190, 180, 55, 40, BLACK);
        DrawRectangle(190, 180, 6, 40, RED);
        DrawRectangle(190, 180, 55, 6, RED);
        DrawRectangle(190 + 55 - 6, 180, 6, 40, RED);
        DrawRectangle(190, 180 + 40 - 6, 55, 6, RED);
        DrawText("-", 190 + 19, 181, 40, WHITE);
    }else {
        DrawRectangle(190, 180, 55, 40, RED);
        DrawRectangle(190, 180, 6, 40, BLACK);
        DrawRectangle(190, 180, 55, 6, BLACK);
        DrawRectangle(190 + 55 - 6, 180, 6, 40, BLACK);
        DrawRectangle(190, 180 + 40 - 6, 55, 6, BLACK);
        DrawText("-", 190 + 19, 181, 40, BLACK);
    }
}

void DrawSpeed(){
    DrawButtonSpeedText();
    DrawSpeedScreen();
    DrawSpeedUP();
    DrawSpeedDOWN();
}

void DrawButtonBackParametrs(){
    if (backPar_but.state == 1 || backPar_but.state == 2){
        DrawRectangle(backPar_but.posRec_x, backPar_but.posRec_y, backPar_but.width, backPar_but.height, BLACK);
        DrawText(backPar_but.name, backPar_but.posText_x, backPar_but.posText_y, 19, WHITE);
    }else{
        DrawRectangle(backPar_but.posRec_x, backPar_but.posRec_y, backPar_but.width, backPar_but.height, RED);
        DrawText(backPar_but.name, backPar_but.posText_x, backPar_but.posText_y, 19, BLACK);
    }
}

void DrawSetting_Buttons(){
    DrawButtonExit();
    DrawButtonRestart();
    DrawButtonParametrsSnake();
    DrawButtonParametrsSnake();
    DrawButtonMenuSetting();
    DrawButtonBackSetting();
}

void print_scale(){
    std::cout << Pause_Play.scale_play << std::endl;
    std::cout << Pause_Play.scale_pause << std::endl;
}

void DrawPause(){
    if (Pause_Play.pause_state == 1 || Pause_Play.pause_state == 2){
        DrawRectangle(0, 0, 20,20, RED);
        DrawTextureEx(Pause_Play.tex_pause, posPause , 0, Pause_Play.scale_pause, WHITE);
    }else{
        DrawTextureEx(Pause_Play.tex_pause, posPause , 0, Pause_Play.scale_pause, WHITE);
    }
}

void DrawPlayBlink (){
    blink_pause.update_presert += GetFrameTime();
    float pos_rec_x = (CANVAS_WIDTH / 8);
    float pos_rec_y = ((CANVAS_HEIGHT - BODY_HEIGHT) / 8) * 3;
    if (blink_pause.update_presert >= 0 && blink_pause.update_presert < (blink_pause.speed / 2)){
        DrawRectangle(pos_rec_x, pos_rec_y, 400, 130, WHITE);
        DrawRectangle(pos_rec_x, pos_rec_y, 400, 8, LIGHTGRAY);
        DrawRectangle(pos_rec_x, pos_rec_y, 8, 130, LIGHTGRAY);
        DrawRectangle(pos_rec_x + 400 - 8, pos_rec_y, 8, 130, LIGHTGRAY);
        DrawRectangle(pos_rec_x, pos_rec_y + 130 - 8, 400, 8, LIGHTGRAY);
        DrawText("PAUSE", (CANVAS_WIDTH / 2) - 160, (CANVAS_HEIGHT / 2) - 30, 100, BLACK);
    }else{
        if (blink_pause.update_presert > blink_pause.speed){
            blink_pause.update_presert = 0;
        }
        DrawRectangle(pos_rec_x, pos_rec_y, 400, 130, BLACK);
        DrawRectangle(pos_rec_x, pos_rec_y, 400, 8, WHITE);
        DrawRectangle(pos_rec_x, pos_rec_y, 8, 130, WHITE);
        DrawRectangle(pos_rec_x + 400 - 8, pos_rec_y, 8, 130, WHITE);
        DrawRectangle(pos_rec_x, pos_rec_y + 130 - 8, 400, 8, WHITE);
        DrawText("PAUSE", (CANVAS_WIDTH / 2) - 160, (CANVAS_HEIGHT / 2) - 30, 100, WHITE);
    }
}

void DrawPlay(){
    DrawPlayBlink();
    if (Pause_Play.play_state == 2 || Pause_Play.play_state == 1) {
        DrawRectangle(0, 0, 20, 20, RED);
        DrawTextureEx(Pause_Play.tex_play, posPlay, 0, Pause_Play.scale_play, WHITE);
    }else{
        DrawTextureEx(Pause_Play.tex_play, posPlay, 0, Pause_Play.scale_play, WHITE);
    }
}

void DrawSetting(){
    if (Setting.settings_state == 1 || Setting.settings_state == 2){
        DrawRectangle(22, 0, 20, 20, RED);
        DrawTextureEx(Setting.tex, posSet, 0, Setting.scale_settings, WHITE);
    }else{
        DrawTextureEx(Setting.tex, posSet, 0, Setting.scale_settings, WHITE);
    }
}

void DrawParametrButtons(){
    DrawTextureEx(Setting.tex, posSet, 0, Setting.scale_settings, WHITE);
    DrawTextureEx(Setting.tex, posSet, 0, Setting.scale_settings, WHITE);
    DrawRectangle(125, 60, 250, 240, WHITE);
    DrawRectangle(125, 60, 8, 240, BROWN);
    DrawRectangle(125, 60, 250, 8, BROWN);
    DrawRectangle(125 + 250 - 8, 60, 8, 240, BROWN);
    DrawRectangle(125, 60 + 240 - 8, 250, 8, BROWN);
    DrawButtonBackParametrs();
    DrawSpeed();
}

void DrawSettingActive(){
    DrawTextureEx(Setting.tex, posSet, 0, Setting.scale_settings, WHITE);
    DrawRectangle(125, 60, 250, 240, WHITE);
    DrawRectangle(125, 60, 8, 240, BROWN);
    DrawRectangle(125, 60, 250, 8, BROWN);
    DrawRectangle(125 + 250 - 8, 60, 8, 240, BROWN);
    DrawRectangle(125, 60 + 240 - 8, 250, 8, BROWN);
    DrawSetting_Buttons();
}

Rectangle GetCanvasTarget(){
    float screen_h = (float)GetScreenHeight();
    float screen_w = (float)GetScreenWidth();
    float scale = fminf(screen_h / CANVAS_HEIGHT, screen_w / CANVAS_WIDTH);
    Rectangle rec = {0,0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale};
    return rec;
}

float ScaleCanvas(){
    float screen_h = (float)GetScreenHeight();
    float screen_w = (float)GetScreenWidth();
    float scale = fminf(screen_h / CANVAS_HEIGHT, screen_w / CANVAS_WIDTH);
    return scale;
}

void InitSnake(){
    for (int i = 0; i <= MainSnake.length; i++){
        int x = MainSnake.pos_x - i * MainSnake.dir_x;
        int y = MainSnake.pos_y;
        Body[x][y].lifetime = MainSnake.length - i;
    }
}

void Init_Menu(){
    for (int i = 0; i < FIELD_WIDTH; i++){
        for (int j = 0; j < FIELD_HEIGHT; j++){
            Snake_menu[i][j].lifetime = 0;
        }
    }


    for (int i = 11; i <= 14; i++){
        Snake_menu[1][i].lifetime = 1;
    }
    Snake_menu[2][14].lifetime = 1;
    Snake_menu[2][15].lifetime = 1;
    Snake_menu[2][16].lifetime = 2;


    for (int i = 17; i >= 14; i--){
        Snake_menu[4][i].lifetime = 1;
    }
    for (int i = 4; i <= 8; i++){
        Snake_menu[i][14].lifetime = 1;
    }
    Snake_menu[8][15].lifetime = 1;
    Snake_menu[8][16].lifetime = 2;



    for (int i = 17; i > 14; i--){
        Snake_menu[11][i].lifetime = 1;
    }
    Snake_menu[11][14].lifetime = 2;



    for (int i = 15; i <= 19; i++){
        Snake_menu[i][15].lifetime = 1;
    }
    for (int i = 15; i >= 14; i--){
        Snake_menu[19][i].lifetime = 1;
    }
    Snake_menu[20][14].lifetime = 1;
    Snake_menu[21][14].lifetime = 1;
    Snake_menu[22][14].lifetime = 1;
    Snake_menu[22][13].lifetime = 1;
    Snake_menu[22][12].lifetime = 2;




    for (int i = 23; i <= 25; i++){
        Snake_menu[i][4].lifetime = 1;
    }
    for (int i = 0; i <= 3; i++){
        Snake_menu[i][4].lifetime = 1;
    }
    Snake_menu[3][5].lifetime = 1;
    Snake_menu[3][6].lifetime = 2;



    for (int i = 5; i > 2; i--){
        Snake_menu[i][1].lifetime = 1;
    }
    Snake_menu[2][1].lifetime = 2;



    for (int i = 10; i < 18; i++){
        Snake_menu[i][2].lifetime = 1;
    }
    Snake_menu[18][2].lifetime = 2;


    for (int i = 23; i > 21; i--){
        Snake_menu[i][2].lifetime = 1;
    }
    Snake_menu[22][1].lifetime = 1;
    Snake_menu[21][1].lifetime = 1;
    Snake_menu[20][1].lifetime = 2;



    for (int i = 21; i < 23; i++){
        Snake_menu[i][16].lifetime = 1;
    }
    Snake_menu[23][16].lifetime = 2;



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
    Init_Menu();
    game_over = false;
    score = 0;
    MousePoint = GetMousePosition();
    MainSnake = {.dir_x = 1,                    // 1 - right, -1 - left, 0 - howhere
                 .dir_y = 0,                    // 1 - up, -1 - down, 0 - nowhere
                 .next_dir_x = 1,
                 .next_dir_y = 0,
                 .length = 2,
                 .pos_x = FIELD_WIDTH / 2,      // position of heard
                 .pos_y = FIELD_HEIGHT / 2,     // position of heard
                 .speed = 0.2,
                 .last_update = 0,
                 .has_eaten = false,
                 .speed_table = 20
    };

    exit_Setting_but.active = false;
    restart_but.active = false;
    parametrsSnake_but.active = false;
    backSet_but.active = false;
    Pause_Play.active_pause = true;
    Pause_Play.active_play = false;
    Setting.active = false;

    for (int i = 0; i < FIELD_WIDTH; i++){
        for(int j = 0; j < FIELD_HEIGHT; j++){
            Body[i][j].lifetime = 0;
            Body[i][j].food_inside = false;
        }
    }
    InitSnake();
    DropFood();
}

void Drawline(){
    DrawRectangle(0,0, CANVAS_WIDTH, 20, WHITE);
    DrawText(TextFormat("score: %06i", score), CANVAS_WIDTH - 315,0, 20, BLACK);
    if (Pause_Play.active_pause && !Pause_Play.active_play){
        DrawPause();
    }else {
        if (!Pause_Play.active_pause && Pause_Play.active_play){
            DrawPlay();
        }
    }
    if (Setting.active){
        if (parametrsSnake_but.active){
            DrawParametrButtons();
        }else{
            DrawSettingActive();
        }
    } else{
        if (!Setting.active) {
            DrawSetting();
        }
    }

}

void DrawSnakeHeard_menu(int i, int j){
    DrawRectangle(i * BODY_WIDTH, j * BODY_HEIGHT,body_width, body_height,DARKGRAY);
}

void DrawSnakeBody_menu(int i, int j){
    DrawRectangle(i * BODY_WIDTH, j * BODY_HEIGHT, body_width, body_height, GRAY);
}

void DrawBody(int i, int j){
    DrawRectangle(i * BODY_WIDTH, (j + 1) * BODY_HEIGHT, body_width, body_height, GRAY);
}

void DrawSnakeHeard(){
    DrawRectangle(MainSnake.pos_x * BODY_WIDTH, (MainSnake.pos_y + 1) * BODY_HEIGHT, body_width, body_height, DARKGRAY);
}

void DrawSnakeMenu(){
    for (int i = 0; i <= FIELD_WIDTH; i++){
        for (int j = 0; j <= FIELD_HEIGHT; j++){
            if (Snake_menu[i][j].lifetime == 1){
                DrawSnakeBody_menu(i, j);
            }else{
                if (Snake_menu[i][j].lifetime == 2){
                    DrawSnakeHeard_menu(i, j);
                }
            }
        }
    }
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

void DrawStartMenuButton(){
    if (start_Menu_but.state == 1 || start_Menu_but.state == 2){
        DrawRectangle(7 * BODY_WIDTH, 10 * BODY_HEIGHT, 100, 40, DARKGRAY);
        DrawText(start_Menu_but.name, (7 * BODY_WIDTH) + 7, (10 * BODY_HEIGHT) + 7, 25, WHITE);
    }else {
        DrawRectangle(7 * BODY_WIDTH, 10 * BODY_HEIGHT, 100, 40, RED);
        DrawText(start_Menu_but.name, (7 * BODY_WIDTH) + 7, (10 * BODY_HEIGHT) + 7, 25, BLACK);
    }
}

void DrawExitMenuButton(){
    if (exit_Menu_but.state == 1 || exit_Menu_but.state == 2){
        DrawRectangle(13 * BODY_WIDTH, 10 * BODY_HEIGHT, 100, 40, DARKGRAY);
        DrawText(exit_Menu_but.name, (14 * BODY_WIDTH) + 1, (10 * BODY_HEIGHT) + 7, 25, WHITE);
    }else {
        DrawRectangle(13 * BODY_WIDTH, 10 * BODY_HEIGHT, 100, 40, RED);
        DrawText(exit_Menu_but.name, (14 * BODY_WIDTH) + 1, (10 * BODY_HEIGHT) + 7, 25, BLACK);
    }
}

void DrawGame(){
    if (menuSetting_but.active){
        DrawSnakeMenu();
        blink_menu.update_presert += GetFrameTime();
        if(blink_menu.update_presert >= 0 && blink_menu.update_presert < (blink_menu.speed / 2)){
            DrawRectangle(5 * BODY_WIDTH, 3 * BODY_HEIGHT, 15 * BODY_WIDTH, (11 * BODY_HEIGHT) - 0.1, WHITE);

            DrawRectangle(5 * BODY_WIDTH, 3 * BODY_HEIGHT, 8, (11 * BODY_HEIGHT) - 0.1, BROWN);
            DrawRectangle(5 * BODY_WIDTH, 3 * BODY_HEIGHT, 15 * BODY_WIDTH, 8 - 0.1, BROWN);
            DrawRectangle((20 * BODY_WIDTH) - 8, 3 * BODY_HEIGHT, 8, (11 * BODY_HEIGHT) - 0.1, BROWN);
            DrawRectangle(5 * BODY_WIDTH, (14 * BODY_HEIGHT) - 8, 15 * BODY_WIDTH, 8 - 0.1, BROWN);

            DrawText("SNAKE GAME", (6 * BODY_WIDTH) - 10, 5 * BODY_HEIGHT, 42, BLACK);
            DrawText("by Chebykin Dmitrii", 7 * BODY_WIDTH, 7 * BODY_HEIGHT, 25, BLACK);
        }else{
            if (blink_menu.update_presert > blink_menu.speed){
                blink_menu.update_presert = 0;
            }
            DrawRectangle(5 * BODY_WIDTH, 3 * BODY_HEIGHT, 15 * BODY_WIDTH, (11 * BODY_HEIGHT) - 0.1, BLACK);

            DrawRectangle(5 * BODY_WIDTH, 3 * BODY_HEIGHT, 8, (11 * BODY_HEIGHT) - 0.1, LIGHTGRAY);
            DrawRectangle(5 * BODY_WIDTH, 3 * BODY_HEIGHT, 15 * BODY_WIDTH, 8 - 0.1, LIGHTGRAY);
            DrawRectangle((20 * BODY_WIDTH) - 8, 3 * BODY_HEIGHT, 8, (11 * BODY_HEIGHT) - 0.1, LIGHTGRAY);
            DrawRectangle(5 * BODY_WIDTH, (14 * BODY_HEIGHT) - 8, 15 * BODY_WIDTH, 8 - 0.1, LIGHTGRAY);

            DrawText("SNAKE GAME", (6 * BODY_WIDTH) - 10, 5 * BODY_HEIGHT, 42, WHITE);
            DrawText("by Chebykin Dmitrii", 7 * BODY_WIDTH, 7 * BODY_HEIGHT, 25, WHITE);
        }

        DrawStartMenuButton();
        DrawExitMenuButton();
    }else {
        DrawFood();
        DrawSnake();
        Drawline();
        if (game_over) {
            blink_game_over.update_presert += GetFrameTime();
            if (blink_game_over.update_presert >= 0 && blink_game_over.update_presert < (blink_game_over.speed / 2)) {
                DrawRectangle((CANVAS_WIDTH / 2) - 200, (CANVAS_HEIGHT / 2) - 100, 400, 150, BLANK);
                DrawText("GAME OVER", CANVAS_WIDTH - 400, (CANVAS_HEIGHT / 2) - 50, 50, WHITE);
                DrawText("Press SPACE to restart", CANVAS_WIDTH - 380, CANVAS_HEIGHT / 2, 20, WHITE);
                DrawText(TextFormat("Your score: %05i", score), (CANVAS_WIDTH / 2) - 90, (CANVAS_HEIGHT / 2) - 80, 20,
                         WHITE);
            } else {
                if (blink_game_over.update_presert > blink_game_over.speed) {
                    blink_game_over.update_presert = 0;
                }
                DrawRectangle((CANVAS_WIDTH / 2) - 200, (CANVAS_HEIGHT / 2) - 100, 400, 150, WHITE);
                DrawText("GAME OVER", CANVAS_WIDTH - 400, (CANVAS_HEIGHT / 2) - 50, 50, BLACK);
                DrawText("Press SPACE to restart", CANVAS_WIDTH - 380, CANVAS_HEIGHT / 2, 20, BLACK);
                DrawText(TextFormat("Your score: %05i", score), (CANVAS_WIDTH / 2) - 90, (CANVAS_HEIGHT / 2) - 80, 20,
                         BLACK);
            }
        }
    }
}

void ChekFood(){
    if (MainSnake.pos_x == Food.x && MainSnake.pos_y == Food.y && Food.sup_food){
        MainSnake.has_eaten = 2;
        score += 40;
        DropFood();
    } else{
        if (MainSnake.pos_x == Food.x && MainSnake.pos_y == Food.y && !Food.sup_food){
            MainSnake.has_eaten = 1;
            score += 20;
            DropFood();
        }
    }
}

void ChekPlayButt(){
    float width_play = (float)GetScreenWidth() / FIELD_WIDTH;
    float height_play = (float)GetScreenHeight() / FIELD_HEIGHT;

    Rectangle PlayRecc = {0, 0, width_play, height_play};

    if (CheckCollisionPointRec(MousePoint, PlayRecc)){
        Pause_Play.pause_state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            Pause_Play.pause_state = 2;
            Pause_Play.active_pause = true;
            Pause_Play.active_play = false;
        }
    } else{
        Pause_Play.pause_state = 0;
    }
    MousePoint = GetMousePosition();
}

void ChekPauseButt(){
    float width_pause = (float)GetScreenWidth() / FIELD_WIDTH;
    float height_pause = (float)GetScreenHeight() / FIELD_HEIGHT;

    Rectangle PauseRecc = {0, 0, width_pause, height_pause};

    if (CheckCollisionPointRec(MousePoint, PauseRecc)){
        Pause_Play.play_state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            Pause_Play.play_state = 2;
            Pause_Play.active_play = true;
            Pause_Play.active_pause = false;
        }else{
            Pause_Play.play_state = 0;
        }
    }
    MousePoint = GetMousePosition();
}

void ChekParametrsButtons(){
    float scale = ScaleCanvas();
    float delta_width = (float)GetScreenWidth() - (CANVAS_WIDTH * scale);
    float delta_height = (float)GetScreenHeight() - (CANVAS_HEIGHT * scale);

    float width_back = backPar_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_back = backPar_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_back = backPar_but.posRec_x * scale;
    float pos_y_back = backPar_but.posRec_y * scale;

    Rectangle backRec = {pos_x_back, pos_y_back, width_back, height_back};

    float width_speed_plus = speedPlus_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_speed_plus = speedPlus_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_speed_plus = speedPlus_but.posRec_x * scale;
    float pos_y_speed_plus = speedPlus_but.posRec_y * scale;

    Rectangle speedPlusRec = {pos_x_speed_plus, pos_y_speed_plus, width_speed_plus, height_speed_plus};

    float width_speed_minus = speedMinus_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_speed_minus = speedMinus_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_speed_minus = speedMinus_but.posRec_x * scale;
    float pos_y_speed_minus = speedMinus_but.posRec_y * scale;

    Rectangle speedMinusRec = {pos_x_speed_minus, pos_y_speed_minus, width_speed_minus, height_speed_minus};


    if (CheckCollisionPointRec(MousePoint, speedMinusRec)){
        speedMinus_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && parametrsSnake_but.active){
            speedMinus_but.active = true;
            speedMinus_but.state = 2;
            return;
        }
    }else{
        speedMinus_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, speedPlusRec) && parametrsSnake_but.active){
        speedPlus_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            speedPlus_but.active = true;
            speedPlus_but.state = 2;
            return;
        }
    }else{
        speedPlus_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, backRec)){
        backPar_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            backPar_but.state = 2;
            backPar_but.active = true;
            return;
        }
    }else{
        backPar_but.state = 0;
    }
    MousePoint = GetMousePosition();
}

void ChekStartExitButton(){
    float scale = ScaleCanvas();
    float delta_width = (float)GetScreenWidth() - (CANVAS_WIDTH * scale);
    float delta_height = (float)GetScreenHeight() - (CANVAS_HEIGHT * scale);

    float width_start = start_Menu_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_start = start_Menu_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_start = start_Menu_but.posRec_x * scale;
    float pos_y_start = start_Menu_but.posRec_y * scale;

    Rectangle startRec = {pos_x_start, pos_y_start, width_start, height_start};

    float width_exit_menu = exit_Menu_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_exit_menu = exit_Menu_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_exut_menu = exit_Menu_but.posRec_x * scale;
    float pos_y_exit_menu = exit_Menu_but.posRec_y * scale;

    Rectangle exitMenuRec = {pos_x_exut_menu, pos_y_exit_menu, width_exit_menu, height_exit_menu};

    if (CheckCollisionPointRec(MousePoint, startRec)){
        start_Menu_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            start_Menu_but.state = 2;
            start_Menu_but.active = true;
        }
    }else{
        start_Menu_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, exitMenuRec)){
        exit_Menu_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            exit_Menu_but.state = 2;
            exit_Menu_but.active = true;
        }
    }else{
        exit_Menu_but.state = 0;
    }
    MousePoint = GetMousePosition();
}

void ChekBackParametrsActive(){
    if (backPar_but.active){
        backPar_but.active = false;
        backSet_but.active = false;
        parametrsSnake_but.active = false;
        Setting.active = true;
        parametrsSnake_but.active_additionally = false;
    }

}

void ChekSpeedButtonsActive(){
    if (speedPlus_but.active){
        speedPlus_but.active = false;
        if (Snake_speed.speed_output >= 100){
            return;
        } else {
            Snake_speed.speed_output += 5;
            Snake_speed.speed_calculations -= 5;
            Snake_speed.speed_intput = Snake_speed.speed_calculations / 100;
            MainSnake.speed = Snake_speed.speed_intput;
        }
    }
    if (speedMinus_but.active){
        speedMinus_but.active = false;
        if (Snake_speed.speed_output <= 0){
            return;
        }else {
            Snake_speed.speed_output -= 5;
            Snake_speed.speed_calculations += 5;
            Snake_speed.speed_intput = Snake_speed.speed_calculations / 100;
            MainSnake.speed = Snake_speed.speed_intput;
        }
    }
}

void ChekSettingButtonsActive(){
    float scale = ScaleCanvas();
    float delta_width = (float)GetScreenWidth() - (CANVAS_WIDTH * scale);
    float delta_height = (float)GetScreenHeight() - (CANVAS_HEIGHT * scale);

    float width_exit = exit_Setting_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_exit = exit_Setting_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_exit = exit_Setting_but.posRec_x * scale;
    float pos_y_exit = exit_Setting_but.posRec_y * scale;
    
    Rectangle exitRec = {pos_x_exit, pos_y_exit, width_exit, height_exit};

    float width_restart = restart_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_restart = restart_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_restart = restart_but.posRec_x * scale;
    float pos_y_restart = restart_but.posRec_y * scale;
    
    Rectangle restartRec = {pos_x_restart, pos_y_restart, width_restart, height_restart};

    float width_parametrs = parametrsSnake_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_parametrs = parametrsSnake_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_parametrs = parametrsSnake_but.posRec_x * scale;
    float pos_y_parametrs = parametrsSnake_but.posRec_y * scale;

    Rectangle parametrsRec = {pos_x_parametrs, pos_y_parametrs, width_parametrs, height_parametrs};

    float width_menu = menuSetting_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_menu = menuSetting_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_menu = menuSetting_but.posRec_x * scale;
    float pos_y_menu = menuSetting_but.posRec_y * scale;

    Rectangle menuRec = {pos_x_menu, pos_y_menu, width_menu, height_menu};

    float width_back = backSet_but.width * ((float)GetScreenWidth() - delta_width) / CANVAS_WIDTH;
    float height_back = backSet_but.height * ((float)GetScreenHeight() - delta_height) / CANVAS_HEIGHT;
    float pos_x_back = backSet_but.posRec_x * scale;
    float pos_y_back = backSet_but.posRec_y * scale;

    Rectangle backRec = {pos_x_back, pos_y_back, width_back, height_back};

    if (CheckCollisionPointRec(MousePoint, exitRec)){
        exit_Setting_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            exit_Setting_but.active = true;
            exit_Setting_but.state = 2;
            return;
        }
    } else{
        exit_Setting_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, restartRec)){
        restart_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            restart_but.active = true;
            restart_but.state = 2;
            return;
        }
    }else{
        restart_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, parametrsRec)){
        parametrsSnake_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            parametrsSnake_but.active = true;
            parametrsSnake_but.state = 2;
            return;
        }
    } else{
        parametrsSnake_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, menuRec)){
        menuSetting_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            menuSetting_but.active = true;
            menuSetting_but.state = 2;
            return;
        }
    }else{
        menuSetting_but.state = 0;
    }
    if (CheckCollisionPointRec(MousePoint, backRec)){
        backSet_but.state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            backSet_but.active = true;
            backSet_but.state = 2;
            return;
        }
    }else{
        backSet_but.state = 0;
    }
}

bool exitActive(){
    bool state;
    if (exit_Setting_but.active || exit_Menu_but.active){
        state = true;
    } else{
        state = false;
    }
    return  state;
}

void restartActive(){
    if (restart_but.active){
        setup();
    }
}

void ChekSetting(){
    float width_set = (float)GetScreenWidth() / FIELD_WIDTH;
    float height_set = (float)GetScreenHeight() / FIELD_HEIGHT;

    float distance = width_set + ((5 * (float)GetScreenWidth()) / CANVAS_WIDTH);

    Rectangle SetRecc = {distance, 0, width_set, height_set};

    if (CheckCollisionPointRec(MousePoint, SetRecc)){
        Setting.settings_state = 1;
        if (Setting.active){
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                Setting.active = false;
                Setting.settings_state = 2;
            }
        }else{
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                Setting.active = true;
                Setting.settings_state = 2;
            }
        }
    }else{
        Setting.settings_state = 0;
    }
    MousePoint = GetMousePosition();
}

void ChekCollision(){
    if (Body[MainSnake.pos_x][MainSnake.pos_y].lifetime > 0){
        game_over = true;
    }
}

void ChekBackSettingActive(){
    if (backSet_but.active){
        Setting.active = false;
        backSet_but.active = false;
    }
    MousePoint = GetMousePosition();
}

void ChekMenuButtonSettings(){
    if (menuSetting_but.active){
        start_Menu_but.active = false;
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
    ChekPlayButt();
    ChekPauseButt();
    ChekSetting();
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

void ChekParametrsAdditionally(){
    if (parametrsSnake_but.active){
        parametrsSnake_but.active_additionally = true;
    }
}

void ChekStartMenuActive(){
    if (start_Menu_but.active){
        menuSetting_but.active = false;
        Setting.active = false;
        start_Menu_but.active = false;
        setup();
    }
}

void UpdateGame(){
    if (menuSetting_but.active) {
        ChekStartExitButton();
        ChekStartMenuActive();
        return;
    }
    if (game_over){
        if (IsKeyPressed(KEY_SPACE)){
            setup();
        }
        return;
    }
    if (Pause_Play.active_play && !Pause_Play.active_pause){
        Pause_Play.pause_state = 2;
        ChekPlayButt();
        return;
    }
    if (Setting.active){
        Setting.settings_state = 2;
        ChekSettingButtonsActive();
        ChekMenuButtonSettings();//??
        restartActive();
        ChekBackSettingActive();
        if (parametrsSnake_but.active && parametrsSnake_but.active_additionally){
            ChekBackParametrsActive();
            ChekSpeedButtonsActive();
            ChekParametrsButtons();
            return;
        }
        ChekParametrsAdditionally();
        return;
    }
    MoveSnake();
    ChekFood();
    ControlSnake();
    MousePoint = GetMousePosition();
}