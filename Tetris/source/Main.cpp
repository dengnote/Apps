//Main.cpp	Tetris ver.1.0
# include <Siv3D.hpp> // OpenSiv3D v0.4.0
# include "library.hpp"
# include "Tetrimino.hpp"
# include "TetrisOperation.hpp"
# include "TetrisUI.hpp"
# include "HumanPlay.hpp"


void Main()
{
	//Siv3Dの描画設定
	// 背景を灰色にする
	Scene::SetBackground(ColorF(0.8, 1.0));
	// 大きさ 30 のフォントを用意
	const Font font(20);


	//テトリス実行の準備
	//乱数の初期化
	srandamInt();
	//TetrisOperationクラスのオブジェクトを宣言(ゲームの初期化処理)
	TetrisOperation tetrisOpe;

	//テトリスの描画準備
	GraphicSet graphSet(tetrisOpe.Output);


	while (System::Update())
	{
		
        //テトリスのプレイの実行関数
		humanPlay(tetrisOpe, graphSet);

		//操作方法の表示
		int fontInterval = 24;
		int fontOriginX = 580;
		int fontOriginY = 370;
		int lineNum = 0;
		font(U"操作方法").draw(Arg::topLeft = Vec2(fontOriginX-20, fontOriginY+fontInterval*lineNum), ColorF(U"#000000"));
		lineNum++;
		font(U"左・右・下：移動").draw(Arg::topLeft = Vec2(fontOriginX, fontOriginY+fontInterval*lineNum), ColorF(U"#000000"));
		lineNum++;
		font(U"上：ハードドロップ").draw(Arg::topLeft = Vec2(fontOriginX, fontOriginY+fontInterval*lineNum), ColorF(U"#000000"));
		lineNum++;
		font(U"X・C：回転").draw(Arg::topLeft = Vec2(fontOriginX, fontOriginY+fontInterval*lineNum), ColorF(U"#000000"));
		lineNum++;
		font(U"Z：ホールド").draw(Arg::topLeft = Vec2(fontOriginX, fontOriginY+fontInterval*lineNum), ColorF(U"#000000"));
		lineNum++;
		font(U"R：リセット").draw(Arg::topLeft = Vec2(fontOriginX, fontOriginY+fontInterval*lineNum), ColorF(U"#000000"));
		lineNum++;


	}
}
