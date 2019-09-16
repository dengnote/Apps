//TetrisUI.hpp  ver.1.0
#ifndef INCLUDE_GUARD_TETRISUI_HPP
#define INCLUDE_GUARD_TETRISUI_HPP

#include <Siv3D.hpp> // OpenSiv3D v0.4.0
#include "TetrisOperation.hpp"

class FPS{  //.cppファイルでは一番下に記述
protected:
    int flame;
    int lastFlame;
    unsigned long long lastTime;
    double fps;
public:
    void processFps();
    double getFps(){return fps;}
    FPS(){flame=0; lastFlame=0; lastTime=Time::GetMillisec(); fps=0.0;}
};

const String blockColor[8] = {
    U"#ffffff",  //白
    U"#00ffff",  //I字：シアン
    U"#ffff00",  //O字：黄色
    U"#00ff00",  //S字：ライム
    U"#ff0000",  //Z字：赤
    U"#0000ff",  //J字：青
    U"#ffa500",  //L字：オレンジ
    U"#ff00ff"   //T字：マゼンタ
};

class GraphicSet{
public:
	Font font;      // 大きさ 30 のフォントを用意
    Font fontGameover;
    FPS fps;        //FPSクラスのオブジェクトの宣言
    int blockSize;      //ブロックのサイズ（pixel）を設定する。
    Point ulCorner;     //プレイフィールドの左上の座標を設定する
    Tetrimino nextTetriminoGraphics[3]; //描画用nextTetriminoのオブジェクトの宣言
    Tetrimino holdTetriminoGraphic;     //描画用holdTetriminoのオブジェクト宣言
    GraphicSet(TetrisOutput Output);

    void drawTetrimino(const Tetrimino& t, int type);  //type 0:外枠なし、1:外枠あり。
    void drawGhostTetrimino(const Tetrimino& t);
    void drawFieldBlocks(TetrisOutput& Output);
    
    void drawTetris(TetrisOutput& Output);

};

void drawTetrimino(Tetrimino t, const int blockSize, Point ulCorner);
void drawGhostTetrimino(Tetrimino t, const int blockSize, Point ulCorner);
void drawFieldBlocks(TetrisField field, const int blockSize, Point ulCorner);


void getTetrisKeyInput(KeyInput& key);
void getTetrisKeyInputOnlyTrue(KeyInput& key);



#endif	//INCLUDE_GUARD_TETRISUI_HPP
