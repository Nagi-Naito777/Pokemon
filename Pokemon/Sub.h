#pragma once

//Color Function(色クラス)
class Color {
public:
	int Whi;	//白
	int Bla;	//黒
	int Gre;	//緑
	int Red;	//赤
	int Blu;	//青

	//色表示関数
	void Read() {
		Whi = GetColor(255, 255, 255);
		Bla = GetColor(0, 0, 0);
		Gre = GetColor(0, 255, 0);
		Red = GetColor(255, 0, 0);
		Blu = GetColor(0, 0, 255);

	}

private:
};
//ColorクラスでColを定義
Color Col;

//Chara Font Function(フォントクラス)
class Font
{
public:
	int c[50 + 1];

	void Read() {
		for (int i = 0; i < 50 + 1; i++) {
			c[i] = CreateFontToHandle("MS ゴシック", i, 6, DX_FONTTYPE_NORMAL);
		}
	}
};
//FontクラスでFonを定義
Font Fon;

//Key Info
int Key[256];

//Key Function
int GetKey() {
	char allkey[256];
	GetHitKeyStateAll(allkey);
	for (int i = 0; i < 256; i++) {
		if (allkey[i] == 1) { Key[i] = Key[i] + 1; }
		else if (allkey[i] == 0) { Key[i] = 0; }
	}
	return 0;		//無くても可
}