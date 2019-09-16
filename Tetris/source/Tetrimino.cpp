//Tetrimino.cpp  ver.0.9
#include "Tetrimino.hpp"

//Tetriminoクラスメンバ関数の定義
void Tetrimino::moveU()
{
    y++;
    for(int i=0; i<4; i++){
        blocks[i].y++;
    }
}
void Tetrimino::moveD()
{
    y--;
    for(int i=0; i<4; i++){
        blocks[i].y--;
    }
}
void Tetrimino::moveL()
{
    x--;
    for(int i=0; i<4; i++){
        blocks[i].x--;
    }
}
void Tetrimino::moveR()
{
    x++;
    for(int i=0; i<4; i++){
        blocks[i].x++;
    }
}
void Tetrimino::turnR()
{
    if(type != 2){
        angle++;
        if(angle > 3){
            angle -= 4;
        }
        if(type != 1){
            for(int i=0; i<4; i++){
                Block tmp = blocks[i];
                blocks[i].x = x + (tmp.y - y);
                blocks[i].y = y - (tmp.x - x);
            }
        }
        else{   //I字の場合
            for(int i=0; i<4; i++){
                Block tmp = blocks[i];
                blocks[i].x = x + (tmp.y - y) + (angle==1?1:0) + (angle==3?-1:0);
                blocks[i].y = y - (tmp.x - x) + (angle==2?-1:0) + (angle==0?1:0);
            }
            x += (angle==1?1:0) + (angle==3?-1:0);
            y += (angle==2?-1:0) + (angle==0?1:0);

        }
    }
}
void Tetrimino::turnL()
{
    if(type != 2){
        angle--;
        if(angle < 0){
            angle += 4;
        }
        if(type != 1){
            for(int i=0; i<4; i++){
                Block tmp = blocks[i];
                blocks[i].x = x - (tmp.y - y);
                blocks[i].y = y + (tmp.x - x);
            }
        }
        else{   //I字の場合
            for(int i=0; i<4; i++){
                Block tmp = blocks[i];
                blocks[i].x = x - (tmp.y - y) + (angle==0?-1:0) + (angle==2?1:0);
                blocks[i].y = y + (tmp.x - x) + (angle==1?1:0) + (angle==3?-1:0);
            }
            x += (angle==0?-1:0) + (angle==2?1:0);
            y += (angle==1?1:0) + (angle==3?-1:0);
        }
    }
}
void Tetrimino::changeType(int ty)
{
    type = ty;
    angle = 0;
    
    if(type == 1){      //I字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x+1, y);
        blocks[3].setPoint(x+2, y);
    }
    else if(type == 2){ //O字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x, y+1);
        blocks[3].setPoint(x-1, y+1);
    }
    else if(type == 3){ //S字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x, y+1);
        blocks[3].setPoint(x+1, y+1);
    }
    else if(type == 4){ //Z字ブロック
        blocks[0].setPoint(x+1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x, y+1);
        blocks[3].setPoint(x-1, y+1);
    }
    else if(type == 5){ //J字ブロック
        blocks[0].setPoint(x+1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x-1, y);
        blocks[3].setPoint(x-1, y+1);
    }
    else if(type == 6){ //L字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x+1, y);
        blocks[3].setPoint(x+1, y+1);
    }
    else if(type == 7){ //T字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x+1, y);
        blocks[3].setPoint(x, y+1);
    }
}
void Tetrimino::setTetrimino(int a, int b, int ty)
{
    x = a;
    y = b;
    type = ty;
    angle = 0;
    state = 1;

    if(type == 1){      //I字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x+1, y);
        blocks[3].setPoint(x+2, y);
    }
    else if(type == 2){ //O字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x, y+1);
        blocks[3].setPoint(x-1, y+1);
    }
    else if(type == 3){ //S字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x, y+1);
        blocks[3].setPoint(x+1, y+1);
    }
    else if(type == 4){ //Z字ブロック
        blocks[0].setPoint(x+1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x, y+1);
        blocks[3].setPoint(x-1, y+1);
    }
    else if(type == 5){ //J字ブロック
        blocks[0].setPoint(x+1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x-1, y);
        blocks[3].setPoint(x-1, y+1);
    }
    else if(type == 6){ //L字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x+1, y);
        blocks[3].setPoint(x+1, y+1);
    }
    else if(type == 7){ //T字ブロック
        blocks[0].setPoint(x-1, y);
        blocks[1].setPoint(x, y);
        blocks[2].setPoint(x+1, y);
        blocks[3].setPoint(x, y+1);
    }
}