#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<iostream>
#include<termios.h>

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

enum {
    COLOR_NOME=-1,
    COLOR_BLACK=0,
    COLOR_WHITE=1,
    COLOR_MAX
};

enum {
    DIRECTION_UP,
    DIRECTION_UP_LEFT,
    DIRECTION_LEFT,
    DIRECTION_DOWN_LEFT,
    DIRECTION_DOWN,
    DIRECTION_DOWN_RIGHT,
    DIRECTION_RIGHT,
    DIRECTION_UP_RIGHT,
    DIRECTION_MAX,
};
int directions[][2] = {
    {0,-1},// DIRECTION_UP
    {-1,-1},// DIRECTION_UP_LEFT
    {-1,0},// DIRECTION_LEFT
    {-1,1},// DIRECTION_DOWN_LEFT
    {0,1},// DIRECTION_DOWN
    {1,1},// DIRECTION_DOWN_RIGHT
    {1,0},// DIRECTION_RIGHT
    {1,-1},// DIRECTION_UP_RIGHT
};

char colorNames[][5 + 1] = {
    "Black",// COLOR_BLACK
    "White"// COLOR_WHITE
};

int cells[BOARD_WIDTH][BOARD_HEIGHT];

int cursorX, cursorY;
int turn;

bool checkCanPut(int _color, int _x, int _y, bool _turnOver){
    if(cells[_y][_x] !=COLOR_NOME)
        return false;
    // 全方向のチェック
    for(int i = 0; i < DIRECTION_MAX; i++){
        int x = _x, y = _y;
        x += directions[i][0];
        y += directions[i][1];
        if(cells[y][x]!=(_color ^1))
            continue;       //敵の色でなければ続ける
        while(1){
            x += directions[i][0];
            y += directions[i][1];
            // チェックする方向の全てのマス
            if((x<0) || (x >= BOARD_WIDTH) || (y<0) || (y >= BOARD_HEIGHT))
                break;
            if(cells[y][x]==COLOR_NOME)     //色が（石が）ない時
                break;
            if(cells[y][x]== _color)        //自分と同色の時
                if(! _turnOver)
                    return true;            //置ける
                int x2 = _x, y2 = _y;       //新たな x y 
                // ひっくり返し処理
                while(1){
                    cells[y2][x2] = _color;

                    x2 += directions[i][0];
                    y2 += directions[i][1];

                    if((x2 == x) && (y2 == y))
                        break;
                }
        }
    }
    return false;
}

bool checkCanPutAll(int _color){
    for(int y=0; y<BOARD_HEIGHT; y++) 
        for(int x=0; x<BOARD_WIDTH; x++)
            if(checkCanPut(_color, x, y, false))        //もし置く場所があったら
                return true;

    return false;
}

int main(){
    for(int y=0; y<BOARD_HEIGHT; y++) 
        for(int x=0; x<BOARD_WIDTH; x++)
            cells[y][x] = COLOR_NOME;
    cells[3][3] = cells[4][4] = COLOR_WHITE;
    cells[3][4] = cells[4][3] = COLOR_BLACK;
    bool cantPut = false;
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
        if(cantPut)
            printf("Can't put! %s turn.\n", colorNames[turn]);
        else    
        // ボードを描画した後
            printf("%s turn.\n", colorNames[turn]);

        cantPut = false;
        switch(getchar()){
        case'w': cursorY--; break;  //上へ
        case's': cursorY++; break;  //下へ
        case'a': cursorX--; break;  //左へ
        case'd': cursorX++; break;  //右へ
        default:
            if (!checkCanPut(turn, cursorX, cursorY, false)){
                cantPut = true;
                break;
            }

            checkCanPut(turn, cursorX, cursorY, true);

            // 移動後、石を置く
            cells[cursorY][cursorX] = turn;
            turn ^=1;

            //パスの場合（置けるところがない場合）
            if(!checkCanPutAll(turn))
                turn ^=1;

            break;
        }

        if((!checkCanPutAll(COLOR_BLACK)) && (!checkCanPutAll(COLOR_WHITE))){
            printf("Game set!\n");
            // getchar();
            break;
        }
    }
}
