//TetrisUI.cpp  ver.0.9
#include "TetrisUI.hpp"

//GraphicSetクラスメンバ関数の定義
GraphicSet::GraphicSet(TetrisOutput Output)
{
	// 大きさ 30 のフォントを用意
	font = Font(30);

    //Gameover用のフォント
    fontGameover = Font(50);

    //ブロックのサイズ（pixel）を設定する。
    blockSize = 28;

    //プレイフィールドの左下の座標を設定する
    ulCorner = Point(800/2 - blockSize * 5, 600/2 - blockSize * 10);
	
    //nextTetriminoGraphics[3]の初期化
    for(int i=0; i<3; i++){
		nextTetriminoGraphics[i].setTetrimino(13+i, 16-i*3, *(Output.nextTetriminoType[i]));
	}
    
    //holdTetriminoGraphicの初期化
    holdTetriminoGraphic.setTetrimino(-3, 17, *(Output.holdTetriminoType));
}
void GraphicSet::drawTetrimino(const Tetrimino& t, int type)
{
    int x[4],y[4];
    for(int i=0; i<4; i++){
        x[i] = ulCorner.x + blockSize * (t.blocks[i].x-1);
        y[i] = ulCorner.y + blockSize * (20-t.blocks[i].y);
        if(type){
            //ブロックの外枠を塗る
            Rect(x[i], y[i], blockSize, blockSize).drawFrame(0, 2, ColorF(1.0, 0.4));
        }
    }
    for(int i=0; i<4; i++){
        //ブロックの中を塗る
        Rect(x[i], y[i], blockSize, blockSize).draw(ColorF(blockColor[t.type]));
        //ブロックの内枠を塗る
        Rect(x[i], y[i], blockSize, blockSize).drawFrame(2, 0, ColorF(0.3, 0.4));
    }
}
void GraphicSet::drawGhostTetrimino(const Tetrimino& t)
{
    for(int i=0; i<4; i++){
        int x, y;
        x = ulCorner.x + blockSize * (t.blocks[i].x-1);
        y = ulCorner.y + blockSize * (20-t.blocks[i].y);
        Rect(x, y, blockSize, blockSize).draw(ColorF(blockColor[t.type]+U"7f"));
        Rect(x, y, blockSize, blockSize).drawFrame(2, 0, ColorF(0.3, 0.4));
    }
}
void GraphicSet::drawFieldBlocks(TetrisOutput& Output)
{
    for(int i=1; i<=10; i++){
        for(int j=1; j<=20; j++){
            if(*(Output.blockC[i][j])){ //ポインタ注意
                int x = ulCorner.x + blockSize * (i-1);
                int y = ulCorner.y + blockSize * (20-j);
                //ブロックの中を塗る
                Rect(x, y, blockSize, blockSize).draw(ColorF(blockColor[*(Output.blockC[i][j])]));
                //ブロックの内枠を塗る
                Rect(x, y, blockSize, blockSize).drawFrame(2, 0, ColorF(0.3, 0.4));
            }
        }
    }
}
void GraphicSet::drawTetris(TetrisOutput& Output)
{
    //プレイフィールドを描く（ベタ塗り）
    Rect(ulCorner.x, ulCorner.y, blockSize*10, blockSize*20).draw(ColorF(0.3, 1.0));
    Rect(ulCorner.x, ulCorner.y, blockSize*10, blockSize*20).drawFrame(0, 3, ColorF(1.0, 1.0));
    
    //プレイフィールドにブロック模様を描く
    for(int i=0; i<10; i++){
        for (int j=0; j<20; j++) {
            Rect(ulCorner.x + blockSize * i, ulCorner.y + blockSize * j, blockSize, blockSize).drawFrame(2, 0, ColorF(0.4, 1.0));
        }
    }

    //テトリミノとブロックを表示する
    drawFieldBlocks(Output);
    drawGhostTetrimino(*(Output.ghostTetrimino));
    drawTetrimino(Output.droppingTetrimino, 1);

    //ネクストテトリミノを表示
    font(U"NEXT").draw(Arg::topRight = Vec2(645, 30), ColorF(U"#0000ff"));
    for(int i=0; i<3; i++){
        nextTetriminoGraphics[i].changeType(*(Output.nextTetriminoType[i]));
        drawTetrimino(nextTetriminoGraphics[i], 1);
    }

    //ホールドテトリミノを表示
    font(U"HOLD").draw(Arg::topRight = Vec2(205, 30), ColorF(U"#0000ff"));
    if(*(Output.holdTetriminoType)){
        holdTetriminoGraphic.changeType(*(Output.holdTetriminoType));
        drawTetrimino(holdTetriminoGraphic, 1);
    }

    //スコア表示
    font(U"スコア").draw(Arg::topRight = Vec2(205, 160), ColorF(U"#0000ff"));
    font(U"", *(Output.score)).draw(Arg::topRight = Vec2(205, 190), ColorF(U"#0000ff"));
    font(U"ライン").draw(Arg::topRight = Vec2(205, 250), ColorF(U"#0000ff"));
    font(U"", *(Output.lineScore)).draw(Arg::topRight = Vec2(205, 280), ColorF(U"#0000ff"));

    //レベル表示
    font(U"レベル").draw(Arg::topRight = Vec2(205, 340), ColorF(U"#0000ff"));
    font(U"", *(Output.level)).draw(Arg::topRight = Vec2(205, 370), ColorF(U"#0000ff"));
    
    //ゲームオーバー表示
    if(*(Output.gameState) == 0){
        fontGameover(U"Game Over").drawAt(Scene::Center(), Palette::White);
	}

    //FPS表示
    fps.processFps();
    font(U"", fps.getFps(), U"fps").draw(Arg::bottomLeft = Vec2(0, 600));

}
void drawTetrimino(Tetrimino t, const int blockSize, Point ulCorner)
{
    int x[4],y[4];
    for(int i=0; i<4; i++){
        x[i] = ulCorner.x + blockSize * (t.blocks[i].x-1);
        y[i] = ulCorner.y + blockSize * (20-t.blocks[i].y);
        //ブロックの外枠を塗る
        Rect(x[i], y[i], blockSize, blockSize).drawFrame(0, 2, ColorF(1.0, 0.4));
    }
    for(int i=0; i<4; i++){
        //ブロックの中を塗る
        Rect(x[i], y[i], blockSize, blockSize).draw(ColorF(blockColor[t.type]));
        //ブロックの内枠を塗る
        Rect(x[i], y[i], blockSize, blockSize).drawFrame(2, 0, ColorF(0.3, 0.4));
    }
}
void drawGhostTetrimino(Tetrimino t, const int blockSize, Point ulCorner)
{
    for(int i=0; i<4; i++){
        int x, y;
        x = ulCorner.x + blockSize * (t.blocks[i].x-1);
        y = ulCorner.y + blockSize * (20-t.blocks[i].y);
        Rect(x, y, blockSize, blockSize).draw(ColorF(blockColor[t.type]+U"7f"));
        Rect(x, y, blockSize, blockSize).drawFrame(2, 0, ColorF(0.3, 0.4));
    }
}
void drawFieldBlocks(TetrisField field, const int blockSize, Point ulCorner)
{
    for(int i=1; i<=10; i++){
        for(int j=1; j<=20; j++){
            if(field.getBlockC(i, j)){
                int x = ulCorner.x + blockSize * (i-1);
                int y = ulCorner.y + blockSize * (20-j);
                //ブロックの中を塗る
                Rect(x, y, blockSize, blockSize).draw(ColorF(blockColor[field.getBlockC(i, j)]));
                //ブロックの内枠を塗る
                Rect(x, y, blockSize, blockSize).drawFrame(2, 0, ColorF(0.3, 0.4));
            }
        }
    }
}
void getTetrisKeyInput(KeyInput& key)
{
    //テトリミノの移動のキー
    if(KeyUp.pressed())
	    key.up = true;
    else
        key.up = false;
    
	if(KeyDown.pressed())
		key.down = true;
    else
        key.down = false;
    
	if(KeyLeft.pressed())
		key.left = true;
    else
        key.left = false;
    
	if(KeyRight.pressed())
		key.right = true;
    else
        key.right = false;


	//テトリミノの回転のキー
	if(KeyC.pressed())
		key.turnR = true;
    else
        key.turnR = false;

	if(KeyX.pressed())
		key.turnL = true;
    else
        key.turnL = false;
    
	if(KeyZ.pressed())
		key.hold = true;
    else
        key.hold = false;
}
void getTetrisKeyInputOnlyTrue(KeyInput& key)
{
    //テトリミノの移動のキー
    if(KeyUp.pressed())
	    key.up = true;
    
	if(KeyDown.pressed())
		key.down = true;
    
	if(KeyLeft.pressed())
		key.left = true;
    
	if(KeyRight.pressed())
		key.right = true;


	//テトリミノの回転のキー
	if(KeyC.pressed())
		key.turnR = true;

	if(KeyX.pressed())
		key.turnL = true;
    
	if(KeyZ.pressed())
		key.hold = true;
}

//FPSクラスのメンバ関数の定義
void FPS::processFps()
{
    unsigned long long presentTime = Time::GetMillisec();
    flame++;
    
    unsigned long long dt = presentTime - lastTime;

    if(dt >= 1000){
        fps = (double)(flame - lastFlame) * 1000.0 / dt;

        lastTime = presentTime;
        lastFlame = flame;
    }
}
