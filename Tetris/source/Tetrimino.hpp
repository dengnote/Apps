//Tetrimino.hpp  ver.0.9
#ifndef INCLUDE_GUARD_TETRIMINO_HPP
#define INCLUDE_GUARD_TETRIMINO_HPP

//Blockクラスの宣言
class Block{
public:
	int x;
	int y;
	//int color;		//1~7,Tetriminoのtypeと同じ。
	void setPoint(int a, int b){x=a; y=b;}
};

//Tetriminoクラスの宣言
class Tetrimino{
public:
	int x;		//1~10,左が1、右が10。
	int y;		//1~22,下が1、上が20。
	int type;	//1~7,ブロックの形状
	int angle;	//0~3,ブロックの向き、1で右90°。
	int state;	//テトリミノの状態。0:固定中、1:空中、2:地面に接触
    Block blocks[4];    //各ブロックの座標
	void moveU();
	void moveD();
	void moveL();
	void moveR();
	void turnR();
	void turnL();
	void changeType(int ty);
	void setTetrimino(int a=5, int b=21, int ty=1);
	Tetrimino(int a=5, int b=21, int ty=1){setTetrimino(a,b,ty);}
};

#endif	//INCLUDE_GUARD_TETRIMINO_HPP