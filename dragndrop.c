#include "menu.h"

//      Example draggable element
// typedef struct ExampleDragnDropObject{
//     Vector2 position;            //  this is elements dynamic position
//     Vector2 defPosition;         //  this is the default position of the element
//     Rectangle space;             //  this is the elements position comibined with its dimenstions
//     bool dragged;                //  true when element is being dragged
// };



//      handles position during drag and drop for given element
//          returns 1 when element is being dragged
//          returns 2 when element has been dropped
//      initialize Mouse struct for mouseDraggs
int handleDragPosition(Rectangle *space, Vector2 *position, Vector2 defPosition, bool *dragged, bool *mouseDraggs){
    *space = (Rectangle){position->x, position->y, space->width, space->height};
    
    if (!*mouseDraggs && IsMouseButtonDown(0) && CheckCollisionPointRec(GetMousePosition(), *space)){
        *dragged = true;
        *mouseDraggs = true;
    }

    if (*dragged && IsMouseButtonReleased(0)){
        *position = defPosition;
        *dragged = false;
        *mouseDraggs = false;
        return 2;
    }
        
    if (*dragged){
        *position = GetMousePosition();
        return 1;
    }
}