#include "menu.h"

#define TABLE_SIZE 3

//      this is the matrix itself
typedef struct Table{
    Vector2 position;
    int value;
} Table;

//      thats the box you drag around with your mouse
typedef struct DragBox{
    Vector2 position;
    Vector2 defPosition;
    Rectangle space;
    bool dragged;
} DragBox;

//      those are the boxes that show up once you drag something with your mouse, they perform calculations when dropped on
typedef struct DragSlot{
    Vector2 position;
    Rectangle space;
    Color color;
    int operant;
    bool isVisible;
} DragSlot;


static Table table[TABLE_SIZE][TABLE_SIZE] = {0};
static DragBox dragBox[TABLE_SIZE] = {0};
static DragSlot dragSlot[2][TABLE_SIZE] = {0};


static bool signSwapped = false;


static Mouse mouse = {0};


void initGame(void){
    mouse.mouseDraggs = false;
    mouse.mouseDrops = false;

    //      sets parametrs for the numbers in the matrix
    for (int i = 0; i < TABLE_SIZE; i++){
        for (int j = 0; j < TABLE_SIZE; j++){
            table[i][j].position = (Vector2){200+30*i, 200+30*j};
            table[i][j].value = GetRandomValue(1, 9);
        }
    }

    //      sets parametrs for dragboxes
    for (int i = 0; i < TABLE_SIZE; i++){
        dragBox[i].position = (Vector2){table[0][i].position.x - 60, table[0][i].position.y};
        dragBox[i].defPosition = dragBox[i].position;
        dragBox[i].dragged = false;
        dragBox[i].space = (Rectangle){dragBox[i].position.x, dragBox[i].position.y, 20, 20};
    }
    
    //      sets parametrs for dragslots
    for (int i = 0; i < TABLE_SIZE; i++){
        dragSlot[i][0].operant = 0;
        dragSlot[i][0].color = BLUE;
        dragSlot[i][0].position = (Vector2){dragBox[i].position.x - 60, dragBox[i].position.y};
        dragSlot[i][0].space = (Rectangle){dragSlot[i][0].position.x, dragSlot[i][0].position.y, 20, 20};
    
        dragSlot[i][1].operant = 1;
        dragSlot[i][1].color = RED;
        dragSlot[i][1].position = (Vector2){dragBox[i].position.x - 30, dragBox[i].position.y};
        dragSlot[i][1].space = (Rectangle){dragSlot[i][1].position.x, dragSlot[i][1].position.y, 20, 20};

        dragSlot[i][2].operant = 2;
        dragSlot[i][2].color = YELLOW;
        dragSlot[i][2].position = (Vector2){table[TABLE_SIZE-1][i].position.x + 30, table[TABLE_SIZE-1][i].position.y};
        dragSlot[i][2].space = (Rectangle){dragSlot[i][2].position.x, dragSlot[i][2].position.y, 20, 20};
    }
}

void updateLogic(void){
    for (int i = 0; i < TABLE_SIZE; i++){
        switch (handleDragPosition(&dragBox[i].space, &dragBox[i].position, dragBox[i].defPosition, &dragBox[i].dragged, &mouse.mouseDraggs)){
            //      handles visibility of slots
            case 1:{
                for (int j = 0; j < TABLE_SIZE; j++){
                    dragSlot[j][0].isVisible = true;
                }
                dragSlot[i][0].isVisible = false;
                break;
            }
            //      handles addition, subtraction and row swapping
            case 2:{
                for (int j = 0; j < TABLE_SIZE; j++){
                    for (int k = 0; k < 3; k++){
                        if (CheckCollisionPointRec(GetMousePosition(), dragSlot[j][k].space)){
                            if (dragSlot[j][k].operant == 0){
                                for (int l = 0; l < TABLE_SIZE; l++){
                                    table[l][j].value = table[l][j].value - table[l][i].value;
                                }
                            } else if(dragSlot[j][k].operant == 1){
                                for (int l = 0; l < TABLE_SIZE; l++){
                                    table[l][j].value = table[l][j].value + table[l][i].value;
                                }
                            } else if(dragSlot[j][k].operant == 2){
                                for (int l = 0; l < TABLE_SIZE; l++){
                                    int x = table[l][i].value;
                                    table[l][i].value = table[l][j].value;
                                    table[l][j].value = x;
                                }
                                if (signSwapped){
                                    signSwapped = false;
                                } else{
                                    signSwapped = true;
                                }
                            }
                        }
                    }
                }

                for (int j = 0; j < TABLE_SIZE; j++){
                    dragSlot[j][0].isVisible = false;
                }
                break;
            }
        }
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
                DrawRectangleRec(dragSlot[i][0].space, dragSlot[i][0].color);
                DrawRectangleRec(dragSlot[i][1].space, dragSlot[i][1].color);
                DrawRectangleRec(dragSlot[i][2].space, dragSlot[i][2].color);

                DrawText(TextFormat("+"), dragSlot[i][1].position.x+5, dragSlot[i][1].position.y+1, 20, WHITE);
                DrawText(TextFormat("-"), dragSlot[i][0].position.x+6, dragSlot[i][0].position.y+1, 20, WHITE);
            }
        }
        
        //      renders draggable boxes
        for (int i = 0; i < TABLE_SIZE; i++){
            if (!dragBox[i].dragged){
                DrawRectangleRec(dragBox[i].space, BLACK);
            } else{
                DrawRectangleRec(dragBox[i].space, GREEN);
            }
            DrawText(TextFormat("="), dragBox[i].position.x+6, dragBox[i].position.y+1, 20, WHITE);
        }

        //      renders "-" after swapping rows
        if (signSwapped){
            DrawText("-", table[0][0].position.x - 30, table[0][0].position.y + ((table[0][TABLE_SIZE-1].position.y - table[0][0].position.y)/2), 30, BLACK);
        }
        
    EndDrawing();
}