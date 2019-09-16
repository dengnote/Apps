//  HumanPlay.cpp
#include "HumanPlay.hpp"

void humanPlay(TetrisOperation& TetrisOpe, GraphicSet& GraphSet)
{
    //ゲームのリセット
    if(KeyR.down()){
        TetrisOpe.field.resetTetrisField();
        TetrisOpe.keyOperation(1);
    }    

    //キーボードの入力を取得する
    getTetrisKeyInput(TetrisOpe.keyInput);

    //Tetris実行関数
    TetrisOpe.play();

    //テトリス描画
    GraphSet.drawTetris(TetrisOpe.Output);
    
    

}