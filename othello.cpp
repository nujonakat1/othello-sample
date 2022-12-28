#include<stdio.h>
#include<wchar.h>
#include<iostream>
#include<termios.h>

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

int cursorX, cursorY;

int main(){
    switch(getchar()){
    case'w': cursorY--; break;
    case's': cursorY++; break;
    case'a': cursorX--; break;
    case'd': cursorX++; break;
    default:
        break;
    }
    for(int y=0; y<BOARD_HEIGHT; y++) {
        for(int x=0; x<BOARD_WIDTH; x++)
            if((x==cursorX) && (y==cursorY))
                printf("◎");
            else    
                printf("・");
        printf("\n");
    }
   

}
