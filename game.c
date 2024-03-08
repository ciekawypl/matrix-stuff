#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Testowe okno");
    

    //      test data to render
    // int table[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};


    //      default draggable circile position
    int circx = 200;
    int circy = 200;

    bool isHeld = false;
    bool dropped = false;


    SetTargetFPS(60);

    while (!WindowShouldClose()){

        //      handles dragged circle position
        if (isHeld && IsMouseButtonDown(0)){
            circx = GetMouseX();
            circy = GetMouseY();

            DrawRectangle(300, 300, 50, 50, BLACK);
        } else{

            //      tells to draw blue circle if dragged circle has been dropped on the correct spot
            if (CheckCollisionCircleRec((Vector2){circx, circy}, 20, (Rectangle){300, 300, 50, 50})){
                dropped = true;
            }

            isHeld = false;
            circx = 200;
            circy = 200;
        }

        //      sets the circle as being held
        if (IsMouseButtonDown(0) && CheckCollisionPointCircle(GetMousePosition(), (Vector2){circx, circy}, 20)){
            isHeld = true;
        }

        //      renders only when dragged circle touches the black box
        if (CheckCollisionCircleRec((Vector2){circx, circy}, 20, (Rectangle){300, 300, 50, 50})){
            DrawRectangle(500, 100, 50, 50, GREEN);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            GuiGrid((Rectangle){0, 0, screenWidth, screenHeight}, "dupa", 50, 1, &(Vector2){0,0});

            //      draws only when dragged circle has been dropped on the black box
            if (dropped){
                DrawCircle(500, 200, 20, BLUE);
            }
            
            DrawCircle(circx,circy,20,BLACK);


            //      playing around with matrix rendering
            // for (int i = 0; i < sizeof(table)/sizeof(table[0]); i++){
                // for (int j = 0; j < sizeof(table)/sizeof(table[0]); j++){
                    // DrawText(TextFormat("%d", table[i][j]), screenWidth/2+20*j, 20+20*i, 20, BLACK);
                // }
            // }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}