#pragma once

class SELECT {
public:
	void Out() {
		//Pokemon Select Cal
		Cal();
		//Pokemon Output
		Cha();
	}
private:

	struct Cursol {
		int X = 0;				//X座標
		int Y = 0;				//Y座標
		const int X_Lim = 10;	//X座標の限界値
		const int Y_Lim = 4;	//Y座標の限界値
	};
	Cursol Cur;

	struct Flag {
		bool Ent = 0;
		bool Pla = 0;
	};
	Flag Fla;

	//今何匹目？かを格納する構造体
	struct Count {
		int Pla = 0;
		int Ene = 0;
	};
	Count Cou;

	void Cal();
	void Cha();
};

SELECT Sel; 

//計算パート
void SELECT::Cal() {
	//選択カーソルの動き処理(WASD操作)
	if (Key[KEY_INPUT_D] == 1) {
		Cur.X += POKEMON_CELL;
	}
	if (Key[KEY_INPUT_A] == 1) {
		Cur.X -= POKEMON_CELL;
	}
	if (Key[KEY_INPUT_W] == 1) {
		Cur.Y -= POKEMON_CELL;
	}
	if (Key[KEY_INPUT_S] == 1) {
		Cur.Y += POKEMON_CELL;
	}

	//無限に移動しないための範囲設定分岐
	if (Cur.X < 0) { Cur.X = 0; }
	if (Cur.X > (Cur.X_Lim - 1) * POKEMON_CELL) { Cur.X = (Cur.X_Lim - 1) * POKEMON_CELL; }
	if (Cur.Y < 0) { Cur.Y = 0; }
	if (Cur.Y > (Cur.Y_Lim - 1) * POKEMON_CELL) { Cur.Y = (Cur.Y_Lim - 1) * POKEMON_CELL; }
	
	//エンターキーを押したらフラグを立たせる
	if (Key[KEY_INPUT_NUMPADENTER] == 1) {
		Fla.Ent = 1;
	}

	int p = 0;
	for (int y = 0; y < Cur.Y_Lim; y++) {
		for (int x = 0; x < Cur.X_Lim; x++) {
			//フラグエンターが立っているなおかつ選ばれたモンスターの座標が等しい場合
			if (Fla.Ent == 1 &&
				x == Cur.X / POKEMON_CELL &&
				y == Cur.Y / POKEMON_CELL) {
				//プレイヤー分岐
				switch (Fla.Pla) {
				case 0:
					Fla.Pla = 1;
					Pla.Sel[Cou.Pla] = Pokemon[p];
					Cou.Pla++;
					break;
				case 1:
					Fla.Pla = 0;
					Pla.Sel[Cou.Ene] = Pokemon[p];
					Cou.Ene++;
					//それぞれのモンスターが3匹選ばれたときにバトルシーンに移行
					if (Cou.Pla == 3 && Cou.Ene == 3) {
						Sce = MEN::MEN_02_ACTION;
						Pla.Out = Pla.Sel[0];
						Ene.Out = Ene.Sel[0];
					}

					break;
				}
			}
			p++;
		}
	}
}

//描画パート
void SELECT::Cha() {

	//どちらのプレイヤーがモンスターを選んだかを分かりやすくする
	switch (Fla.Pla){
	case 0:
		DrawFormatString(20, Cur.Y_Lim * POKEMON_CELL + 0, Col.Blu, "Enter Choosing");
	case 1:
		DrawFormatString(20, Cur.Y_Lim * POKEMON_CELL + 0, Col.Red, "Enter Choosing");
	}

	//Pokemon Image Output
	int p = 0;
	for (int y = 0; y < Cur.Y_Lim; y++) {
		for (int x = 0; x < Cur.X_Lim; x++) {
			//キャラクター表示用のDrawGraph関数
			DrawGraph(x * POKEMON_CELL, y * POKEMON_CELL,
				Pic.Poke[p], TRUE);
			/*
			//キャラクター表示を分割するためのDrawBox関数
			DrawBox(x * POKEMON_CELL, y * POKEMON_CELL,
				x * POKEMON_CELL + POKEMON_CELL,
				y * POKEMON_CELL + POKEMON_CELL, Col.Bla, FALSE);
			*/
			//キャラクター選択カーソル表示分岐
			if (x == Cur.X / POKEMON_CELL &&
				y == Cur.Y / POKEMON_CELL) {
				//選択された部分だけ違う色で表示
				DrawBox(x * POKEMON_CELL, y * POKEMON_CELL,
					x * POKEMON_CELL + POKEMON_CELL,
					y * POKEMON_CELL + POKEMON_CELL, 
					Col.Red, FALSE);

				//カーソルが合わさった時に名前を表示するDrawFormatStringToHandle関数
				DrawFormatStringToHandle(200, Cur.Y_Lim * POKEMON_CELL + 20,
					Col.Bla, Fon.c[15], "%s", Pokemon[p].Name);
				//カーソルが合わさった時にステータスを表示するDrawFormatStringToHandle関数
				DrawFormatStringToHandle(200, Cur.Y_Lim * POKEMON_CELL + 40,
					Col.Bla, Fon.c[15], "%s %s",
					Pokemon[p].Type1, Pokemon[p].Type2);
				DrawFormatStringToHandle(200, Cur.Y_Lim * POKEMON_CELL + 60,
					Col.Bla, Fon.c[15], "H(%d) C(%d)",
					Pokemon[p].H, Pokemon[p].C);
				DrawFormatStringToHandle(200, Cur.Y_Lim * POKEMON_CELL + 80,
					Col.Bla, Fon.c[15], "A(%d) D(%d)",
					Pokemon[p].A, Pokemon[p].D);
				DrawFormatStringToHandle(200, Cur.Y_Lim * POKEMON_CELL + 100,
					Col.Bla, Fon.c[15], "B(%d) S(%d)",
					Pokemon[p].B, Pokemon[p].S);
				//カーソルが合わさった時に技を表示するDrawFormatStringToHandle関数(ループ処理)
				for (int i = 0; i < 4; i++) {
					DrawFormatStringToHandle(200, Cur.Y_Lim * POKEMON_CELL + 120+15*i,
						Col.Bla, Fon.c[13], "Tec%d:%s",
						i,Tecnique[Pokemon[p].Tec[i]].name);
				}
				//選択したモンスターの拡大画像を表示する関数
				DrawRotaGraph(100, 300, 2.5, 0.0, Pic.Poke[p], TRUE);
			}
			p++;
		}
	}
}