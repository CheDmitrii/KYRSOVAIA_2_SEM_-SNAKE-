#include <iostream>
#include "realize.h"

using namespace std;

const Vector2 VEC_ZERO = {0, 0};


int main() {

    bool  exit_chek;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "Game_Snake");
    SetTargetFPS(60);

    setPlayPNG();
    setPausePNG();
    setSettingsPNG();
    ParametrsPNG();

    RenderTexture2D canvas = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    Rectangle canvas_field = {0, 0, (float)canvas.texture.width, -(float)canvas.texture.height};
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
    setup();


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(LIME);
        BeginTextureMode(canvas);
        ClearBackground(BLACK);
        DrawPause();
//        Boom();
        DrawGame();
        EndTextureMode();
        DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget() , VEC_ZERO, 0, WHITE);
        EndDrawing();

        UpdateGame();
        exit_chek = exitActive();
        if (exit_chek){
            return 0;
        }

    }

    UnLoadPNG();
    CloseWindow();

    return 0;
}