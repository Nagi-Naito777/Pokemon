#pragma once

//キャラ表示用の写真クラス
class {
public:
	int Tit;		//タイトルシーン変数
	int Bat;		//戦闘シーン変数
	int Poke[];		//パチモン配列

	void Read() {
		Tit = LoadGraph("");
		Bat = LoadGraph("");
		LoadDivGraph("./resource/puchimon.png", POKEMON_KIND, 3, 1, POKEMON_CELL, POKEMON_CELL, Poke);

	}
private:
}Pic;