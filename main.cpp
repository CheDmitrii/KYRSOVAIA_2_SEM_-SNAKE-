#include <iostream>
//#include "raylib.h"
//#include <math.h>
#include "realize.h"

using namespace std;

const Vector2 VEC_ZERO = {0, 0};


int main() {
//    Game();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIND_WIDTH, WIND_HEIGHT, "Game_Snake");
    SetTargetFPS(60);
    RenderTexture2D canvas = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    Rectangle canvas_field = {0, 0, (float)canvas.texture.width, (float)canvas.texture.height};
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
    setup();

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GREEN);
        BeginTextureMode(canvas);
        ClearBackground(BLACK);
        Draw();
        EndTextureMode();
        DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget() , VEC_ZERO, 0, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
