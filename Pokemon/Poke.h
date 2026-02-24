#pragma once
#include <string>

using namespace std;

//パチモンの構造体を定義
struct POKEMON {
	int No = -1;					//図鑑No.
	string Name;					//名前
	string Type1;					//タイプ1
	string Type2;					//タイプ2
	int H = 0;						//HP
	int A = 0;						//こうげき
	int B = 0;						//ぼうぎょ
	int C = 0;						//とくこう
	int D = 0;						//とくぼう
	int S = 0;						//すばやさ
	int Tec[4] = { -1,-1,-1,-1 };	//所持技格納変数

};

POKEMON Pokemon[3] = {
	{0,"マグリュウ","炎","",
	39,52,43,60,50,65,
	0,1,2,3},
	{1,"テツマグドン","炎","鋼",
	58,64,58,80,65,80,
	0,1,2,3},
	{2,"イグラドガネ","炎","鋼",
	78,84,78,109,85,100,
	0,1,2,3},
};