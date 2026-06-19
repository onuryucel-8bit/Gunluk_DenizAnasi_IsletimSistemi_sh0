#include "pong.h"

void pongRun()
{
    printf("PONG");

    uint16_t posx = 0;
    uint16_t posy = 30;
    while (1)
    {
        drawFilledRectangle(posx, posy, 10, 30, VGA_Color_BLUE);

        if(getKey() == IDT_KEY_W)
        {
            printf("hey!");
            posy += 5;
        }
    }
    
}