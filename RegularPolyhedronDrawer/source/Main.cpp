//Main.cpp

# include <Siv3D.hpp> // OpenSiv3D v0.4.0
# include "RPRotation.hpp"
# include "DrawRPBySiv3D.hpp"

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	// 大きさ 14 のフォントを用意
	const Font font(14);
	

	//Viewを作成
	View view;

	//RPDrawerの準備
	Point drawerPoint(500, 300);
	int drawerRpSize = 200;
	RPDrawer drawer(drawerPoint.x, drawerPoint.y, drawerRpSize);
	

	while (System::Update())
	{
		
		//正多面体の変更
		if (Key1.down() || SimpleGUI::Button(U"正四面体(1)", Vec2(20, 20), 170)){
			view.changeRP(4);
			view.resetViewpoint();
			drawer.origin = drawerPoint;
		}
		else if (Key2.down() || SimpleGUI::Button(U"正六面体(2)", Vec2(20, 80), 170)){
			view.changeRP(6);
			view.resetViewpoint();
			drawer.origin = drawerPoint;
		}
		else if (Key3.down() || SimpleGUI::Button(U"正八面体(3)", Vec2(20, 140), 170)){
			view.changeRP(8);
			view.resetViewpoint();
			drawer.origin = drawerPoint;
		}
		else if (Key4.down() || SimpleGUI::Button(U"正十二面体(4)", Vec2(20, 200), 170)){
			view.changeRP(12);
			view.resetViewpoint();
			drawer.origin = drawerPoint;
		}
		else if (Key5.down() || SimpleGUI::Button(U"正二十面体(5)", Vec2(20, 260), 170)){
			view.changeRP(20);
			view.resetViewpoint();
			drawer.origin = drawerPoint;
		}

		//正多面体の向きのリセット
		if (KeyR.down() || SimpleGUI::Button(U"回転・座標のリセット(R)", Vec2(20, 540))){
			view.resetViewpoint();
			drawer.origin = drawerPoint;
		}

		//正多面体の回転
		Vector3 rotateVec = mouseLDistance() / drawerRpSize;
		if(rotateVec.absolute() != 0.0){
			view.rotateViewpoint(rotateVec);
		}
		view.operateViewRp();

		//正多面体の移動
		Vector3 moveVec = mouseRDistance();
		drawer.origin.x += moveVec.x;
		drawer.origin.y += moveVec.y;

		//正多面体の描画
		drawer.drawRP(view.viewRp);


		// テキストを描く
		font(U"左クリック＋ドラッグ：回転\n右クリック＋ドラッグ：移動").draw(20, 320, Palette::Black);
		
	}
}
