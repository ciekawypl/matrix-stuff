#define RAYGUI_IMPLEMENTATION
#include "menu.h"

const int screenWidth = 800;
const int screenHeight = 450;


int main(){
    InitWindow(screenWidth, screenHeight, "Matrix Calculator");

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);
            if (GuiButton((Rectangle){100,100,100,100}, "matrix")){
                initGame();
                while (!WindowShouldClose()){
                    updateLogic();
                    drawFrame();
                }
                CloseWindow();
                
            }

            if (GuiButton((Rectangle){200, 200, 100, 100}, "test")){
                testInit();
                while (!WindowShouldClose()){
                    testLoop();
                }
                
            }
            
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}