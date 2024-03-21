#include "menu.h"
#include "raylib.h"

typedef struct Blok{
    Vector2 defPosition;
    Vector2 position;
    Rectangle space;
    bool dragged;
} Blok;


static Blok blok = {};
static Blok malyblok = {};

static Mouse mouse = {};

void testInit(){
    mouse.mouseDraggs = false;
    mouse.mouseDrops = false;

    blok.defPosition = (Vector2){100, 100};
    blok.position = blok.defPosition;
    blok.space = (Rectangle){blok.defPosition.x, blok.defPosition.y, 50, 30};
    blok.dragged = false;

    malyblok.defPosition = (Vector2){300, 100};
    malyblok.position = malyblok.defPosition;
    malyblok.space = (Rectangle){malyblok.defPosition.x, malyblok.defPosition.y, 50, 30};
    malyblok.dragged = false;
}

void blokLogic(){
    handleDragPosition(&blok.space, &blok.position, blok.defPosition, &blok.dragged, &mouse.mouseDraggs);
}

void testLogic(){
    blokLogic();
    switch (handleDragPosition(&malyblok.space, &malyblok.position, malyblok.defPosition, &malyblok.dragged, &mouse.mouseDraggs)){
        case 1:{
            DrawText("drag", 200, 100, 20, RED);
            break;
        }
        case 2:{
            break;
        }
    }
}

void testDraw(){
    BeginDrawing();
        ClearBackground(WHITE);
        DrawText("this is a diffrent file", 400, 400, 20, BLACK);

        if (mouse.mouseDraggs){
            DrawText("dziala", 200, 200, 20, BLACK);
        }
        

        DrawRectangleRec(blok.space, RED);
        DrawRectangleRec(malyblok.space, BLUE);
    EndDrawing();

}

void testLoop(){
    testDraw();
    testLogic();
}