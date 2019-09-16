//TetrisOperation.hpp  ver.0.9
#ifndef INCLUDE_GUARD_TETRISOPERATION_HPP
#define INCLUDE_GUARD_TETRISOPERATION_HPP

#include <math.h>
#include "library.hpp"
#include "Tetrimino.hpp"

class KeyInput{
public:
    bool up;
    bool down;
    bool left;
    bool right;
    bool turnR;
    bool turnL;
    bool hold;
public:
    KeyInput();
    void keyReset();    //すべてfalseにする
};

class TetrisOutput{
public:
    const int* blockC[12][23]; //注：配列。blockC[x][y]:0~7,(x,y)のマスにブロックがなければ0、あればブロックの色1~7。
    const int* level;          //ゲームのレベル。0~20。
    const int* gameState;      //ゲームの状況。0:ゲームオーバー、1:プレイ中、2:ポーズ？。
    const int* score;          //ゲームのスコア
    const int* lineScore;      //消したライン数
    const int* nextTetriminoType[3];   //注：配列。3つあとまでのNEXTテトリミノのタイプ
    const int* holdTetriminoType;      //ホールドテトリミノのタイプ。0:ホールドなし、1~7:テトリミノのタイプ
    const bool* holdPossibility;       //ホールド可能かどうか。true:可能、false:不可能。
    Tetrimino droppingTetrimino;    //現在操作中のTetrimino
    const Tetrimino* ghostTetrimino;       //真下に接地する場合の設置位置を示すTetrimino

    void copyDroppingTetrimino(Tetrimino& originalTet){droppingTetrimino = originalTet;}  
        //droppingTetriminoだけポインタできなかったから、これでコピーする
};

class Direction{    //方向ごとに数値を格納できるクラス
public:
    int up;
    int down;
    int left;
    int right;
    int center;
    int sum;
    Direction(){up=0;down=0;left=0;right=0;center=0;sum=0;}
    void sumAll(){sum=up+down+left+right+center;}
};

class TetrisField{
public:
    int blockC[12][23]; //blockC[x][y]:0~7,(x,y)のマスにブロックがなければ0、あればブロックの色1~7。
    int flame;          //最後に(reset)TetrisField()が呼ばれてからのフレーム数
    int lastDropFlame;  //最後に落下などをしたときのフレーム数
    int fixFlameCount;  //接地したときのフレーム数
public:
    int level;          //ゲームのレベル。0~20。
    int dropSpeed;      //操作テトリミノの落下速度。1回の落下にかかるフレーム数。60~1。
    int fixSpeed;       //操作テトリミノが接地してから固定するまでのフレーム数。60〜30。
    int gameState;      //ゲームの状況。0:ゲームオーバー、1:プレイ中、2:ポーズ？。
    int score;          //ゲームのスコア
    int lineScore;      //消したライン数
    int nextTetriminoType[3];   //3つあとまでのNEXTテトリミノのタイプ
    int holdTetriminoType;      //ホールドテトリミノのタイプ。0:ホールドなし、1~7:テトリミノのタイプ
    bool holdPossibility;       //ホールド可能かどうか。true:可能、false:不可能。
    Tetrimino droppingTetrimino;    //現在操作中のTetrimino
    Tetrimino ghostTetrimino;       //真下に接地する場合の設置位置を示すTetrimino
    
    //blockCに関するメンバ関数
    int getBlockC(int x, int y);
    int setBlockC(int x, int y, int f);    //blockC[x][y]にint型引数fを格納する。
    
    //flameに関するメンバ関数
    void increaseFlame(){if(flame<2100000000) flame++; else gameState = 0;} //intの限界近くまで++し、int限界に近くなったらゲームオーバーにする。（120fpsで202日くらい）
    void resetFlame(){flame = 0;}
    int getFlame(){return flame;}

    //lastDropFlameに関するメンバ関数
    void resetDropFlame(){lastDropFlame = flame;}
    int getLastDropFlame(){return lastDropFlame;}

    //fixFlameCountに関するメンバ関数
    void resetFixFlameCount(){fixFlameCount = flame;}

    //level,dropSpeed,fixSpeedに関するメンバ関数
    void levelUpOperation();    //レベルアップ処理

    //score,lineScoreに関するメンバ関数
    void increaseScoreAfterFixing(){score++;}
    void increaseScore(int linesNum){score += linesNum * linesNum * 1000;}
    void increaseLineScore(int linesNum){lineScore += linesNum;}

    //GhostTetriminoに関するメンバ関数
    void setGhostTetrimino();

    //droppingTetriminoの固定〜固定後に関するメンバ関数
    void resetDroppingTetrimino();  //操作テトリミノを次のテトリミノに切り替える。
    void deleteLines();
    void fixDroppingTetrimino();

    //TetriminoとblockCの重なりを判定するメンバ関数
    int judgeOverlapTetrimino(Tetrimino& t); //テトリミノtがフィールドブロックと重なるかどうかを戻す。0:重ならない、1:重なる。
    Direction judgeOverlapTetriminoDirection(Tetrimino& t); //どの方向に何マスめり込むかをDirectionクラスで返す。

    //droppingTetriminoの接地・固定状況を判定するメンバ関数
    int judgeTouchingGround();      //操作テトリミノが地面に接触しているかを返す。0:接地、1:空中
    void judgeDroppingTetriminoState();    //操作テトリミノの状況を判定する

    //固定前のdroppingTetriminoを移動させるメンバ関数
    int dropDroppingTetrimino();   //時間経過による落下処理。動かすか「固定中」にする。0:落下なし、1:落下した
    void moveDroppingTetrimino(KeyInput key);

    //ゲームオーバーを判定するメンバ関数
    void judgeFixingGameover();     //操作テトリミノの固定位置がy>20だったら、gameStateを0:ゲームオーバーにする。
    void judgeAppearanceGameover(); //操作テトリミノの出現位置がblockCと重なったら、gameStateを0:ゲームオーバーにする。
    
    //TetrisFieldを初期化するメンバ関数
    void resetTetrisField();        //ゲームの初期化
    TetrisField();                  //resetTetrisField()を呼び出す
};

class TetrisOperation{  //このクラスのオブジェクト1つが、1つのゲーム（プレイ）となる。
public:
    TetrisField field;
    KeyInput keyInput;  //キーボードのpress状態。あるいはAIからの入力を格納する。
    KeyInput keySent;   //TetrisFieldに伝える操作情報
    TetrisOutput Output;      //他の関数などからアクセスするメンバ。これだけ渡せば描画などをできるようにしたい。
    void keyOperation(int flag=0);    //キーの押下状態の判定。flagに1を入れると、staticのflameをリセットする
    void resetTetrisOperation();    //ゲームの初期化。TetrisOperationを初期化する。
    void setOutput();   //メンバにデータをセットする
    int play();         //1フレームに1回呼び出す
    TetrisOperation(){setOutput();}
};




#endif	//INCLUDE_GUARD_TETRISOPERATION_HPP