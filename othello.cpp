#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<iostream>
#include<termios.h>

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

enum{
    COLOR_NOME=-1,
    COLOR_BLACK=0,
    COLOR_WHITE=1,
    COLOR_MAX
};
char colorNames[][5 + 1] = {
    "Black",// COLOR_BLACK
    "White"// COLOR_WHITE
};

int cells[BOARD_WIDTH][BOARD_HEIGHT];

int cursorX, cursorY;
int turn;

int main(){
    for(int y=0; y<BOARD_HEIGHT; y++) 
        for(int x=0; x<BOARD_WIDTH; x++)
            cells[y][x] = COLOR_NOME;
            
    while(1){
        system("reset");
        for(int y=0; y<BOARD_HEIGHT; y++) {
            for(int x=0; x<BOARD_WIDTH; x++)
                if((x==cursorX) && (y==cursorY))
                    printf("◎ ");
                else{
                    switch(cells[y][x]){
                    case COLOR_NOME:    printf("・");    break;
                    case COLOR_BLACK:   printf("⚫︎");    break;
                    case COLOR_WHITE:   printf("⚪︎");    break;
                    }
                }    
                    
            printf("\n");
        }
        // ボードを描画した後
        printf("%s turn.\n", colorNames[turn]);

        switch(getchar()){
        case'w': cursorY--; break;  //上へ
        case's': cursorY++; break;  //下へ
        case'a': cursorX--; break;  //左へ
        case'd': cursorX++; break;  //右へ
        default:
            // 移動後、石を置く
            cells[cursorY][cursorX] = turn;
            break;
        }
    }
}
