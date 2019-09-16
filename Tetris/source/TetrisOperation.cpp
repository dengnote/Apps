//TetrisOperation.cpp  ver.0.9
#include "TetrisOperation.hpp"

//KeyInputクラスのメンバ関数の定義
KeyInput::KeyInput()
{
    up = false;
    down = false;
    left = false;
    right = false;
    turnR = false;
    turnL = false;
    hold = false;
}
void KeyInput::keyReset()
{
    up = false;
    down = false;
    left = false;
    right = false;
    turnR = false;
    turnL = false;
    hold = false;
}

//TetrisFieldクラスのメンバ関数の定義
int TetrisField::getBlockC(int x, int y)
{
    if(0 <= x && x < 12){
        if(0 <= y && y < 23){
            return blockC[x][y];
        }
        else{
            return 1;
        }
    }
    else{
        return 1;
    }
}
int TetrisField::setBlockC(int x, int y, int f)
{
    if(1 <= x && x<=10){
        if(1 <= y && y <= 22){
            blockC[x][y] = f;
            return 0;
        }
    }
    return 1;
}
void TetrisField::levelUpOperation()
{
    int newLevel = lineScore / 5;
    if(level < newLevel && newLevel <= 20){
        level = newLevel;
        dropSpeed = 60 * pow(0.81488, level);
        fixSpeed = 60 * pow(0.96594, level);
    }
}
void TetrisField::setGhostTetrimino()
{
    Tetrimino tmpTet = droppingTetrimino;
    bool flag = true;

    while(flag && tmpTet.y > 1){
        for(int i=0; i<4; i++){
            int x = tmpTet.blocks[i].x;
            int y = tmpTet.blocks[i].y - 1;
            if(blockC[x][y]){
                flag = false;
            }
        }
        if(flag){
            tmpTet.moveD();
        }
    }
    ghostTetrimino = tmpTet;
}
void TetrisField::resetDroppingTetrimino()
{
    droppingTetrimino.setTetrimino(5,21,nextTetriminoType[0]);
    nextTetriminoType[0] = nextTetriminoType[1];
    nextTetriminoType[1] = nextTetriminoType[2];
    nextTetriminoType[2] = randamInt7();
    holdPossibility = true;
    resetDropFlame();
    resetFixFlameCount();
}
void TetrisField::deleteLines()
{
    //判定する段を調べる
    int minY = droppingTetrimino.blocks[0].y;
    int maxY = droppingTetrimino.blocks[0].y;
    for(int i=1; i<4; i++){
       if(droppingTetrimino.blocks[i].y < minY){
           minY = droppingTetrimino.blocks[i].y;
       }
       if(droppingTetrimino.blocks[i].y > maxY){
           maxY = droppingTetrimino.blocks[i].y;
       }
    }

    //段が消えるかどうかの判定
    int deletedNum = 0;             //消去した段の数
    int tmpBlockC[11][4]; //設置された段の仮のフィールド、その段が消えたら[0]に0を格納する
    for(int i=0; i<=maxY-minY; i++){
        bool flag = true;           //段が埋まっているかどうかのフラグ
        for(int j=1; j<=10; j++){
            if(!blockC[j][minY+i]){
                flag = false;
            }
        }
        if(flag){   //段が消えたら
            deletedNum++;
            for(int k=0; k<=10; k++){
                tmpBlockC[k][i] = 0;
            }
        }
        else{       //段が消えなかったら
            tmpBlockC[0][i] = 1;
            for(int k=1; k<=10; k++){
                tmpBlockC[k][i] = blockC[k][minY+i];
            }
        }
    }
    
    //スコアの加算
    increaseScore(deletedNum);
    increaseLineScore(deletedNum);

    //段を消す処理
    int dy = 0;     //blockCのminY+dyの段に当てはめていく
                    //dyはblockCの埋まった段数もあらわす
    for(int i=0; i<=maxY-minY; i++){    //tmpBlockCの0~(maxY-minY)段を新blockCにはめていく
        if(tmpBlockC[0][i]){
            for(int j=1; j<=10; j++){
                blockC[j][minY+dy] = tmpBlockC[j][i];
            }
            dy++;
        }
    }
    for(int i=maxY+1; i<=20; i++){    //旧blockCのmaxY~20段をずらす。
        for(int j=1; j<=10; j++){
            blockC[j][minY+dy] = blockC[j][i];
        }
        dy++;
    }
    for(int i=minY+dy; i<=20; i++){   //新blockCの空き段を空にする
        for(int j=1; j<=10; j++){
            blockC[j][minY+dy] = 0;
        }
        dy++;
    }
    
}
void TetrisField::fixDroppingTetrimino()
{
    for(int i=0; i<4; i++){
        int x = droppingTetrimino.blocks[i].x;
        int y = droppingTetrimino.blocks[i].y;
        if(1<=x && x<=10 && 1<=y && y<=22){
            blockC[x][y] = droppingTetrimino.type;
        };
    };
}
int TetrisField::judgeOverlapTetrimino(Tetrimino& t)
{
    //int flag = 0;
    for(int i=0; i<4; i++){
        int x = t.blocks[i].x;
        int y = t.blocks[i].y;
        if(y>22){
            return 1;
        }
        else if(blockC[x][y]){
            return 1;
        }
    }
    return 0;
}
Direction TetrisField::judgeOverlapTetriminoDirection(Tetrimino& t)
{
    Direction d;    //メンバはすべて0で初期化される
    for(int i=0; i<4; i++){
        int x = t.blocks[i].x;
        int y = t.blocks[i].y;
        if(blockC[x][y]){
            int dx = x - t.x;
            int dy = y - t.y;
            if(dx > d.right){   //I字が2マスめり込む場合も、これでOK
                d.right = dx;
            }
            else if(-dx > d.left){
                d.left = -dx;
            }
            if(dy > d.up){
                d.up = dy;
            }
            else if(-dy > d.down){
                d.down = -dy;
            }
            else if(dx == 0 && dy == 0){
                d.center = 1;
            }
        }
    }
    d.sumAll();
    return d;
}
int TetrisField::judgeTouchingGround()
{
    bool flag = true;   //落下可能フラグ
    for(int i=0; i<4; i++){
        int x = droppingTetrimino.blocks[i].x;
        int y = droppingTetrimino.blocks[i].y - 1;
        if(blockC[x][y]){
            flag = false;
        }
    }
    if(flag){
        return 1;   //1:空中
    }
    else{
        return 0;   //0:固定or接地
    }
}
void TetrisField::judgeDroppingTetriminoState()
{
    int lastState = droppingTetrimino.state;    //操作テトリミノの前の状態0:固定中、1:空中、2:地面に接触
    int judgement = judgeTouchingGround();  //0:固定or接地、1:空中
    if(judgement){
        droppingTetrimino.state = 1;    //1:空中
    }
    else{
        resetDropFlame();
        if(lastState == 1){     //たった今接地した場合
            resetFixFlameCount();
            droppingTetrimino.state = 2;    //2:接地
        }
        else if(flame - fixFlameCount < fixSpeed){
            droppingTetrimino.state = 2;    //2:接地
        }
        else{
            droppingTetrimino.state = 0;    //0:固定
        }
    }
}
int TetrisField::dropDroppingTetrimino()
{
    int df = flame - lastDropFlame;
    if(df >= dropSpeed){
        if(judgeTouchingGround()){
            droppingTetrimino.moveD();
            resetDropFlame();
            return 1;
        }
    }
    return 0;
}
void TetrisField::moveDroppingTetrimino(KeyInput key)
{
    if(key.hold && holdPossibility){
        if(holdTetriminoType){
            int tmp = holdTetriminoType;
            holdTetriminoType = droppingTetrimino.type;
            droppingTetrimino.setTetrimino(5,21,tmp);
        }
        else{
            holdTetriminoType = droppingTetrimino.type;
            resetDroppingTetrimino();
        }
        holdPossibility = false;
        //操作テトリミノの状況を判定する
        judgeDroppingTetriminoState();
        judgeAppearanceGameover();
        return;
    }
    if(key.left){
        bool flag = true;
        for(int i=0; i<4; i++){
            int x = droppingTetrimino.blocks[i].x - 1;
            int y = droppingTetrimino.blocks[i].y;
            if(blockC[x][y]){
                flag = false;
            }
        }
        if(flag){
            droppingTetrimino.moveL();
            resetFixFlameCount();
        }
    }
    else if(key.right){     //moveLとmoveRは同時に実行しない。
        bool flag = true;
        for(int i=0; i<4; i++){
            int x = droppingTetrimino.blocks[i].x + 1;
            int y = droppingTetrimino.blocks[i].y;
            if(blockC[x][y]){
                flag = false;
            }
        }
        if(flag){
            droppingTetrimino.moveR();
            resetFixFlameCount();
        }
    }
    if(key.turnR){
        bool flag = true;
        
        Tetrimino tmpTet = droppingTetrimino;
        tmpTet.turnR();
        Direction overlapDirection = judgeOverlapTetriminoDirection(tmpTet);
        
        if(overlapDirection.sum > 0){
            Tetrimino tmpTet1 = tmpTet;
            if(overlapDirection.down){
                if(tmpTet.angle == 0 || tmpTet.angle == 1){
                    tmpTet.moveL();
                }
                else{
                    tmpTet.moveR();
                }
                if(judgeOverlapTetrimino(tmpTet)){
                    tmpTet = tmpTet1;
                    tmpTet.moveU();
                    if(judgeOverlapTetrimino(tmpTet)){
                        if(tmpTet.type == 1 && tmpTet.angle == 1){
                            tmpTet.moveU();
                            if(judgeOverlapTetrimino(tmpTet)){
                                flag = false;
                            }
                        }
                        else{
                            flag = false;
                        }
                    }
                }
                
            }
            else if(overlapDirection.left){
                if(overlapDirection.right){
                    tmpTet.moveU();
                    if(judgeOverlapTetrimino(tmpTet)){
                        flag = false;
                    }
                }
                else{
                    tmpTet.moveR();
                    if(judgeOverlapTetrimino(tmpTet)){
                        if(tmpTet.type == 1 && tmpTet.angle == 2){
                            tmpTet.moveR();
                            if(judgeOverlapTetrimino(tmpTet)){
                                tmpTet = tmpTet1;
                                tmpTet.moveU();
                                if(judgeOverlapTetrimino(tmpTet)){
                                    flag = false;
                                }
                            }
                        }
                        else{
                            tmpTet = tmpTet1;
                            tmpTet.moveU();
                            if(judgeOverlapTetrimino(tmpTet)){
                                flag = false;
                            }
                        }
                    }
                }
            }
            else if(overlapDirection.right){    //(overlapDirection.right>0 && overlapDirection.left==0)のはず
                tmpTet.moveL();
                if(judgeOverlapTetrimino(tmpTet)){
                    if(tmpTet.type == 1 && tmpTet.angle == 0){
                        tmpTet.moveL();
                        if(judgeOverlapTetrimino(tmpTet)){
                            tmpTet = tmpTet1;
                            tmpTet.moveU();
                            if(judgeOverlapTetrimino(tmpTet)){
                                flag = false;
                            }
                        }
                    }
                    else{
                        tmpTet = tmpTet1;
                        tmpTet.moveU();
                        if(judgeOverlapTetrimino(tmpTet)){
                            flag = false;
                        }
                    }
                }
            }
            else if(overlapDirection.up){   //周囲8マスのうち上1マスのみが重なる場合
                if(tmpTet.angle == 0 || tmpTet.angle == 1){
                    tmpTet.moveL();
                }
                else{
                    tmpTet.moveR();
                }
                if(judgeOverlapTetrimino(tmpTet)){
                    tmpTet = tmpTet1;
                    tmpTet.moveD();
                    if(judgeOverlapTetrimino(tmpTet)){
                        flag = false;
                    }
                }
            }   //I字のcenterが重なる場合は、右回転ではない
        }
        if(flag && !judgeOverlapTetrimino(tmpTet)){    //条件分岐が重複しているが、バグが怖い
            droppingTetrimino = tmpTet;
            resetFixFlameCount();
        }
    }
    else if(key.turnL){         //turnRとturnLは同時に実行しない。
        bool flag = true;
        
        Tetrimino tmpTet = droppingTetrimino;
        tmpTet.turnL();
        Direction overlapDirection = judgeOverlapTetriminoDirection(tmpTet);
        
        if(overlapDirection.sum > 0){
            Tetrimino tmpTet1 = tmpTet;
            if(overlapDirection.down || (overlapDirection.center && tmpTet.angle == 3)){
                if(tmpTet.angle == 1 || tmpTet.angle == 2){
                    tmpTet.moveL();
                }
                else{
                    tmpTet.moveR();
                }
                if(judgeOverlapTetrimino(tmpTet)){
                    tmpTet = tmpTet1;
                    tmpTet.moveU();
                    if(judgeOverlapTetrimino(tmpTet)){
                        if(tmpTet.type == 1 && tmpTet.angle == 3){
                            tmpTet.moveU();
                            if(judgeOverlapTetrimino(tmpTet)){
                                flag = false;
                            }
                        }
                        else{
                            flag = false;
                        }
                    }
                }
                
            }
            else if(overlapDirection.left || (overlapDirection.center && tmpTet.angle == 0)){
                if(overlapDirection.right || (overlapDirection.center && tmpTet.angle == 2)){
                    tmpTet.moveU();
                    if(judgeOverlapTetrimino(tmpTet)){
                        flag = false;
                    }
                }
                else{
                    tmpTet.moveR();
                    if(judgeOverlapTetrimino(tmpTet)){
                        if(tmpTet.type == 1 && tmpTet.angle == 0){
                            tmpTet.moveR();
                            if(judgeOverlapTetrimino(tmpTet)){
                                tmpTet = tmpTet1;
                                tmpTet.moveU();
                                if(judgeOverlapTetrimino(tmpTet)){
                                    flag = false;
                                }
                            }
                        }
                        else{
                            tmpTet = tmpTet1;
                            tmpTet.moveU();
                            if(judgeOverlapTetrimino(tmpTet)){
                                flag = false;
                            }
                        }
                    }
                }
            }
            else if(overlapDirection.right || (overlapDirection.center && tmpTet.angle == 2)){    //(overlapDirection.right>0 && overlapDirection.left==0)のはず
                tmpTet.moveL();
                if(judgeOverlapTetrimino(tmpTet)){
                    if(tmpTet.type == 1 && tmpTet.angle == 2){
                        tmpTet.moveL();
                        if(judgeOverlapTetrimino(tmpTet)){
                            tmpTet = tmpTet1;
                            tmpTet.moveU();
                            if(judgeOverlapTetrimino(tmpTet)){
                                flag = false;
                            }
                        }
                    }
                    else{
                        tmpTet = tmpTet1;
                        tmpTet.moveU();
                        if(judgeOverlapTetrimino(tmpTet)){
                            flag = false;
                        }
                    }
                }
            }
            else if(overlapDirection.up || (overlapDirection.center && tmpTet.angle == 1)){   //周囲8マスのうち上1マスのみが重なる場合
                if(tmpTet.angle == 1 || tmpTet.angle == 2){
                    tmpTet.moveL();
                }
                else{
                    tmpTet.moveR();
                }
                if(judgeOverlapTetrimino(tmpTet)){
                    tmpTet = tmpTet1;
                    tmpTet.moveD();
                    if(judgeOverlapTetrimino(tmpTet)){
                        flag = false;
                    }
                }
            }
        }
        if(flag && !judgeOverlapTetrimino(tmpTet)){ //条件分岐が重複しているが、バグが怖い
            droppingTetrimino = tmpTet;
            resetFixFlameCount();
        }


        /* if(!judgeOverlapTetrimino(tmpTet)){
            droppingTetrimino = tmpTet;
            resetFixFlameCount();
        }
        else{
            tmpTet.moveU();     //1段上げて回ったら上げる
            if(!judgeOverlapTetrimino(tmpTet)){
                droppingTetrimino = tmpTet;
                resetFixFlameCount();
            }
            else if(tmpTet.type == 1 && tmpTet.angle == 1){ //I字は2段上げる向きがある
                tmpTet.moveU();
                if(!judgeOverlapTetrimino(tmpTet)){
                    droppingTetrimino = tmpTet;
                    resetFixFlameCount();
                }
            }
        } */
    }
    if(key.up){ //ハードドロップ
        if(droppingTetrimino.y > ghostTetrimino.y){
            droppingTetrimino = ghostTetrimino;
        }
        droppingTetrimino.state = 0;
        return;
    }
    else if(key.down && judgeTouchingGround()){ //空中で下を押した場合
        droppingTetrimino.moveD();
        resetDropFlame();
        //操作テトリミノの状況を判定する
        judgeDroppingTetriminoState();
    }
    else {  //上が押されず、「下が押されていないまたは接地している」場合
        dropDroppingTetrimino();
        //操作テトリミノの状況を判定する
        judgeDroppingTetriminoState();
    }

}
void TetrisField::judgeFixingGameover()
{
    bool flag = false;      //テトリミノが完全に画面外(y>20)だったらfalseのままにする
    for(int i=0; i<4; i++){
        if(droppingTetrimino.blocks[i].y <= 20){
            flag = true;    //ゲームオーバーでないと判定する
        }
    }
    if(!flag){
        gameState = 0;
    }
}
void TetrisField::judgeAppearanceGameover()
{
    for(int i=0; i<4; i++){
        int x = droppingTetrimino.blocks[i].x;
        int y = droppingTetrimino.blocks[i].y;
        if(1<=x && x<=10 && 1<=y && y<=22 && blockC[x][y]){
            gameState = 0;
            return;
        };
    }
}
void TetrisField::resetTetrisField()  //ゲームの初期化
{
    //フレーム数の初期化
    resetFlame();
    //resetDropFlame();     //resetDroppingTetrimino()内で初期化される。
    //resetFixFlameCount(); //resetDroppingTetrimino()内で初期化される。

    //レベルの初期化
    level = 0;

    //ドロップスピードの初期化
    dropSpeed = 60;

    //fixSpeedの初期化
    fixSpeed = 60;

    //ゲームの状況の初期化
    gameState = 1;

    //スコアの初期化
    score = 0;
    lineScore = 0;

    //nextTetriminoType[]の初期化
    nextTetriminoType[0] = randamInt7(1);   //乱数グループを初期化する
    for(int i=1; i<3; i++){
        nextTetriminoType[i] = randamInt7();
    }

    //holdTetriminoTypeの初期化
    holdTetriminoType = 0;

    //holdPossibility = true;   //resetDroppingTetrimino()内で初期化される。

    //操作テトリミノの初期化
    resetDroppingTetrimino();

    //フィールドブロックの初期化
    for(int i=1; i<=10; i++){
        blockC[i][0] = 1;
        for(int j=1; j<=22; j++){
            blockC[i][j] = 0;
        }
    }
    for(int j=1; j<=22; j++){
        blockC[0][j] = 1;
        blockC[11][j] = 1;
    }

    //ゴーストテトリミノの位置をセット
    setGhostTetrimino();

}
TetrisField::TetrisField()  //ゲームの初期化
{
    resetTetrisField();
}

//TetrisOperationクラスのメンバ関数の定義
void TetrisOperation::keyOperation(int flag)
{
    static KeyInput lastKey;    //falseで初期化される
    static int downFlame = field.getFlame();
    static int leftFlame = field.getFlame();
    static int rightFlame = field.getFlame();
    if(flag){
        lastKey.keyReset();
        downFlame = field.getFlame();
        leftFlame = field.getFlame();
        rightFlame = field.getFlame();
        return;
    }

    if(keyInput.up && !lastKey.up){
        keySent.up = true;
    }
    else{
        keySent.up = false;
    }
    if(keyInput.down && (!lastKey.down || (field.getFlame() - downFlame >= 3))){
        keySent.down = true;
        if(!lastKey.down){
            downFlame = field.getFlame()+10;
        }
        else{
            downFlame = field.getFlame();
        }
    }
    else{
        keySent.down = false;
    }
    if(keyInput.left && (!lastKey.left || (field.getFlame() - leftFlame >= 3))){
        keySent.left = true;
        if(!lastKey.left){
            leftFlame = field.getFlame()+10;
        }
        else{
            leftFlame = field.getFlame();
        }
    }
    else{
        keySent.left = false;
    }
    if(keyInput.right && (!lastKey.right || (field.getFlame() - rightFlame >= 3))){
        keySent.right = true;
        if(!lastKey.right){
            rightFlame = field.getFlame()+10;
        }
        else{
            rightFlame = field.getFlame();
        }
    }
    else{
        keySent.right = false;
    }
    if(keyInput.turnR && !lastKey.turnR){
        keySent.turnR = true;
    }
    else{
        keySent.turnR = false;
    }
    if(keyInput.turnL && !lastKey.turnL){
        keySent.turnL = true;
    }
    else{
        keySent.turnL = false;
    }
    if(keyInput.hold && !lastKey.hold){
        keySent.hold = true;
    }
    else{
        keySent.hold = false;
    }

    lastKey = keyInput;
}
void TetrisOperation::resetTetrisOperation()
{
    field.resetTetrisField();
    keyInput.keyReset();
    keySent.keyReset();
    keyOperation(1);
}
void TetrisOperation::setOutput(){
    for(int i=0;i<12;i++){
        for(int j=0;j<23;j++){
            Output.blockC[i][j] = &field.blockC[i][j];
        }
    }
    Output.level = &field.level;
    Output.gameState = &field.gameState;
    Output.score = &field.score;
    Output.lineScore = &field.lineScore;
    for(int i=0;i<3;i++){
        Output.nextTetriminoType[i] = &field.nextTetriminoType[i];
    }
    Output.holdTetriminoType = &field.holdTetriminoType;
    Output.holdPossibility = &field.holdPossibility;
    Output.copyDroppingTetrimino(field.droppingTetrimino);
    Output.ghostTetrimino = &field.ghostTetrimino;
}
//テトリス実行関数。この関数は1回の描画ごとに1回呼び出す。
int TetrisOperation::play()
{
    //フレーム数の増加
    field.increaseFlame();

    //キーの押下状態の判定
    keyOperation();

    //ゲーム状況が「プレイ中」なら
    if(field.gameState == 1){
        //キー入力に従って操作テトリミノを動かし、状況を判定する
        field.moveDroppingTetrimino(keySent);

        //ゴーストテトリミノを設置する
        field.setGhostTetrimino();

        //操作テトリミノが「固定中」になったら
        if(field.droppingTetrimino.state == 0){
            //固定時のゲームオーバーの判定
            field.judgeFixingGameover();

            //ゲーム状況が「プレイ中」なら
            if(field.gameState == 1){
                //操作テトリミノを固定する(フィールドブロックにコピーする)
                field.fixDroppingTetrimino();

                //テトリミノ固定の得点を加算する。
                field.increaseScoreAfterFixing();

                //ライン消去の判定をし、ブロックを消去する
                field.deleteLines();

                //レベルアップ処理
                field.levelUpOperation();

                //操作テトリミノが固定されたらリセットする。
                field.resetDroppingTetrimino();

                //新しい操作テトリミノのゲームオーバーの判定
                field.judgeAppearanceGameover();
            }
        }
    }
    else if(field.gameState == 0){
        //ゲームオーバー処理
    }

    //droppingTetriminoをOutputにコピー（出力用）
    Output.copyDroppingTetrimino(field.droppingTetrimino);

    return 0;
}

