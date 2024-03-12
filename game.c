#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


#define TABLE_SIZE 3

typedef struct Table{
    Vector2 position;
    int value;
} Table;

typedef struct DragBox{
    Vector2 position;
    Vector2 defPosition;
    bool isHeld;
    bool dropped;
} DragBox;

typedef struct DragSlot{
    Vector2 position;
    Color color;
    int operant;
    bool isVisible;
} DragSlot;


const int screenWidth = 800;
const int screenHeight = 450;


static bool mouseDraggs = false;
static bool mouseDrops = false;


static Table table[TABLE_SIZE][TABLE_SIZE] = {0};
static DragBox dragBox[TABLE_SIZE] = {0};
static DragSlot dragSlot[2][TABLE_SIZE] = {0};


static void initGame(void);
static void drawFrame(void);
static void updateLogic(void);


int main(){
    InitWindow(screenWidth, screenHeight, "Matrix Calculator");

    initGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        updateLogic();
        drawFrame();
    }
    
    CloseWindow();
    return 0;
}

void initGame(void){
    mouseDraggs = false;
    for (int i = 0; i < TABLE_SIZE; i++){
        for (int j = 0; j < TABLE_SIZE; j++){
            table[i][j].position = (Vector2){200+30*i, 200+30*j};
            table[i][j].value = GetRandomValue(1, 9);
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++){
        dragBox[i].position = (Vector2){table[0][i].position.x - 30, table[0][i].position.y};
        dragBox[i].defPosition = dragBox[i].position;
        dragBox[i].isHeld = false;
        dragBox[i].dropped = false;
    }
    
    for (int i = 0; i < TABLE_SIZE; i++){
        dragSlot[i][0].operant = 0;
        dragSlot[i][0].color = BLUE;
        dragSlot[i][0].position = (Vector2){dragBox[i].position.x - 60, dragBox[i].position.y};
    
        dragSlot[i][1].operant = 1;
        dragSlot[i][1].color = RED;
        dragSlot[i][1].position = (Vector2){dragBox[i].position.x - 30, dragBox[i].position.y};
    }
}

void updateLogic(void){
    if (!IsMouseButtonDown(0)){
        mouseDraggs = false;
    }

    if (IsMouseButtonReleased(0)){
        mouseDrops = true;   
    }
    

    //      handles dragging status
    if (!mouseDraggs){
        for (int i = 0; i < TABLE_SIZE; i++){
            if (IsMouseButtonDown(0) && CheckCollisionPointRec(GetMousePosition(), (Rectangle){dragBox[i].position.x, dragBox[i].position.y, 20, 20})){
                dragBox[i].isHeld = true;
                mouseDraggs = true;
            } else{
                if (dragBox[i].isHeld){
                    dragBox[i].dropped = true;
                }
                dragBox[i].isHeld = false;
            }
        }
    }

    //      handles dragged box position
    if (mouseDraggs && !mouseDrops){
        for (int i = 0; i < TABLE_SIZE; i++){
            if (IsMouseButtonDown(0) && dragBox[i].isHeld){
                dragBox[i].position = GetMousePosition();
            } 
        }
    } else if(mouseDrops){
        for (int i = 0; i < TABLE_SIZE; i++){
            dragBox[i].position = dragBox[i].defPosition;
        }
    }

    //      handles row addition and subtraction
    if (mouseDrops){
        for (int i = 0; i < TABLE_SIZE; i++){
            for (int j = 0; j < 2; j++){
                if (dragSlot[i][0].isVisible && CheckCollisionPointRec(GetMousePosition(), (Rectangle){dragSlot[i][j].position.x, dragSlot[i][j].position.y, 20, 20})){
                    for (int k = 0; k < TABLE_SIZE; k++){
                        if (dragBox[k].dropped){
                            dragBox[k].dropped = false;
                            for (int l = 0; l < TABLE_SIZE; l++){
                                if (dragSlot[i][j].operant == 1){
                                    table[l][i].value = table[l][i].value + table[l][k].value;
                                } else{
                                    table[l][i].value = table[l][i].value - table[l][k].value;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    

    //      handles visibiltiy of slots
    if (mouseDraggs && !mouseDrops){
        for (int i = 0; i < TABLE_SIZE; i++){
            if (dragBox[i].isHeld){
                for (int j = 0; j < TABLE_SIZE; j++){
                    dragSlot[j][0].isVisible = true;
                }
                dragSlot[i][0].isVisible = false;
            } 
        }
    } else if(mouseDrops){
        for (int i = 0; i < TABLE_SIZE; i++){
            dragSlot[i][0].isVisible = false;
        }
    }

    //      pinnacle of coding
    if (mouseDrops){
        mouseDrops = false;
    }
}

void drawFrame(void){
    BeginDrawing();
        ClearBackground(WHITE);

        //      renders the table
        for (int i = 0; i < TABLE_SIZE; i++){
            for (int j = 0; j < TABLE_SIZE; j++){
                DrawText(TextFormat("%d", table[i][j].value), table[i][j].position.x, table[i][j].position.y, 20, BLACK);
            }
        }


        //      renders hideable slots
        for (int i = 0; i < TABLE_SIZE; i++){
            if (dragSlot[i][0].isVisible){
                DrawRectangle(dragSlot[i][0].position.x, dragSlot[i][0].position.y, 20, 20, dragSlot[i][0].color);
                DrawRectangle(dragSlot[i][1].position.x, dragSlot[i][1].position.y, 20, 20, dragSlot[i][1].color);
                
                DrawText(TextFormat("+"), dragSlot[i][1].position.x+5, dragSlot[i][1].position.y+1, 20, WHITE);
                DrawText(TextFormat("-"), dragSlot[i][0].position.x+6, dragSlot[i][0].position.y+1, 20, WHITE);
            }
        }
        
        //      renders draggable boxes
        for (int i = 0; i < TABLE_SIZE; i++){
            if (!dragBox[i].isHeld){
                DrawRectangle(dragBox[i].position.x, dragBox[i].position.y, 20, 20, BLACK);
            } else{
                DrawRectangle(dragBox[i].position.x, dragBox[i].position.y, 20, 20, GREEN);
            }
            DrawText(TextFormat("="), dragBox[i].position.x+6, dragBox[i].position.y+1, 20, WHITE);
        }
    EndDrawing();
}