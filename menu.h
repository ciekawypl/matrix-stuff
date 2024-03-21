#ifndef MENU
#define MENU
#include "raylib.h"
#include "raygui.h"

//      Use when working with drag n drop
typedef struct Mouse{
    bool mouseDraggs;
    bool mouseDrops;
} Mouse;


//      Matrix module functions
void initGame(void);
void drawFrame(void);
void updateLogic(void);


//      Drag n drop functions
int handleDragPosition(Rectangle *space, Vector2 *position, Vector2 defPosition, bool *dragged, bool *mouseDraggs);

void testLoop();
void testInit();

#endif //MENU