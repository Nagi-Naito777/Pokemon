/*
参考動画
https://www.youtube.com/watch?v=2icpkNGaomY&t=139s
*/

//Preprocessor defimition
#define WIN_MAX_X 500		//ウィンドウの横方向サイズ
#define WIN_MAX_Y 400		//ウィンドウの縦方向サイズ
#define WIN_POS_X 0			//ウィンドウの横方向の原点座標
#define WIN_POS_Y 0			//ウィンドウの縦方向の原点座標

#define POKEMON_KIND 40		//パチモンの合計数
#define POKEMON_CELL 50		//パチモン1匹の画像サイズ

//ゲームシーン列挙体
enum MEN {
	MEN_00_TITLE,		//タイトル画面
	MEN_01_SELECT,		//セレクト画面
	MEN_02_ACTION		//バトル画面
};

//Scene initial value substitution
int Sce = MEN::MEN_00_TITLE;

//Insert header file
#include "DxLib.h" //一番上じゃないと下のインクルードに適用されない
#include<iostream>
#include<string>
#include "Poke.h"
#include "Sub.h"
#include "Pic.h"
#include "Tit.h"
#include "Tec.h"
#include "Bat.h"
#include "Sel.h"

//Main Function
int WINAPI WinMain(
	_In_ HINSTANCE hinstance,
	_In_opt_ HINSTANCE hPravInstance,
	_In_ LPSTR IpCmdLine,
	_In_ int nShowCmd)
{
	//Windowモードで起動
	ChangeWindowMode(TRUE);
	DxLib_Init();		//DxLibを初期化

	//Window Init (Windowの初期化)
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);	//背景ポジション
	SetWindowText("パチットモンスター");			//背景タイトル
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);			//背景サイズ
	SetBackgroundColor(255, 255, 255);				//背景色
	SetDrawScreen(DX_SCREEN_BACK);					//背景を表示

	//読み込み関数
	Col.Read();
	Fon.Read();
	Pic.Read();

	/*
	Case Select
	画像削除ループ処理だったり他のプログラムとの干渉を防ぐ
	*/
	while (ScreenFlip() == 0 &&			//全背景を消す
		ClearDrawScreen() == 0 &&		//画面に描かれたものを消去する
		ProcessMessage() == 0 &&		//ウィンドウズのメッセージ処理
		GetKey() == 0 &&				//キーボード情報の取得
		Key[KEY_INPUT_ESCAPE] == 0) {	//Escキーを押したらプログラム終了
		switch (Sce)
		{
		//シーンが00ならタイトル画面
		case MEN::MEN_00_TITLE:
			Tit.Out();
			break;
		//シーンが01なら選択画面
		case MEN::MEN_01_SELECT:
			Sel.Out();
			break;
		//シーンが02なら戦闘画面
		case MEN::MEN_02_ACTION:
			break;
		}
	}

	WaitKey();//キー入力待ち

	DxLib_End();		//DxLibを終了
	return 0;
}