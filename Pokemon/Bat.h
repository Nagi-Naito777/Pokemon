#pragma once
class BATTLE {
public:
	// 外部から入る用の出力関数
	void Out() {
		Cal();
		Cha();
	}
private:

	// 行動の選択肢列挙体
	enum ACT {
		ACT_00_Battle,
		ACT_01_Exchange,
		ACT_02_Tool,
		ACT_03_Give_up,
	};

	// 技の選択肢列挙体
	enum TEC {
		TEC_00,
		TEC_01,
		TEC_02,
		TEC_03,
	};

	// 何をしているかを判定する列挙体
	enum ENT {
		ENT_00_ACT,			// 行動の決定
		ENT_01_TEC,			// 技の決定
		ENT_02_FIR_CAL,		// 戦闘のモンスターの計算
		ENT_03_FIR_OUT,		// 戦闘のモンスターの結果
		ENT_04_SEC_CAL,		// 素早さが遅い側のダメージ計算
		ENT_05_SEC_OUT,		// 素早さが遅い側のダメージ計算の出力
	};

	enum STR {
		STR_00_FIR,
		STR_01_SEC,
	};

	struct {
		struct {
			int X = 300;
			int Y = 310;
		}Act;
		// カーソル
		struct {
			int X = 10;
			int Y = 310;
		}Tec;
	}Cur;

	// 先攻後攻を決める構造体
	struct {
		int Ent = 0;
		// 先攻後攻判定
		bool Str = false;
	}Fla;

	// 技のコピー用の構造体
	struct SUB {
		char Tec_n[100];
		int Tec_a = 0;
		char Poke_n[100];
		char Poke_a = 0;
		char Poke_b = 0;
		bool Fal = false;
	};

	SUB Fir;
	SUB Sec;

	// 計算系の関数
	void Cal();
	// パチモンを出力する関数
	void Cha();

	//CPU処理関数
	void CPU();

	// バトル処理関数
	void Bat();

	// ダメージ計算処理関数
	int Damage(int tec_a, int a, int b);

	// HPゲージ処理関数
	int HPgau(int h_i, int h, int dam);
};

// インスタンス宣言
BATTLE Bat;

// 計算系の関数
void BATTLE::Cal() {
	// カーソルの動き
	if (Key[KEY_INPUT_D] == 1) {
		switch (Fla.Ent) {
		case ENT::ENT_00_ACT:
			Cur.Act.X = 400;
			break;
		case ENT::ENT_01_TEC:
			Cur.Tec.X = 230;
			break;
		}
	}
	else if (Key[KEY_INPUT_A] == 1) {
		switch (Fla.Ent) {
		case ENT::ENT_00_ACT:
			Cur.Act.X = 300;
			break;
		case ENT::ENT_01_TEC:
			Cur.Tec.X = 10;
			break;
		}
	}
	else if (Key[KEY_INPUT_W] == 1) {
		switch (Fla.Ent) {
		case ENT::ENT_00_ACT:
			Cur.Act.Y = 310;
			break;
		case ENT::ENT_01_TEC:
			Cur.Tec.Y = 310;
			break;
		}
	}
	else if (Key[KEY_INPUT_S] == 1) {
		switch (Fla.Ent) {
		case ENT::ENT_00_ACT:
			Cur.Act.Y = 350;
			break;
		case ENT::ENT_01_TEC:
			Cur.Tec.Y = 350;
			break;
		}
	}

	// Enterキーの定義(押されている場合)
	if (Key[KEY_INPUT_NUMPADENTER] == 1) {
		switch (Fla.Ent) {
		case ENT::ENT_00_ACT:
			Fla.Ent = ENT::ENT_01_TEC;		// 技選択に切り替え
			break;
		case ENT::ENT_01_TEC:
			Fla.Ent = ENT::ENT_02_FIR_CAL;	//計算に切り替え
			break;
		case ENT::ENT_02_FIR_CAL:
			Fla.Ent = ENT::ENT_03_FIR_OUT;	//モンスターの計算表示に切り替え
			break;
		case ENT::ENT_03_FIR_OUT:
			Fla.Ent = ENT::ENT_04_SEC_CAL;	//ダメージ計算に切り替え
			break;
		case ENT::ENT_04_SEC_CAL:
			Fla.Ent = ENT::ENT_05_SEC_OUT;	//ダメージ計算表示に切り替え
			break;
		case ENT::ENT_05_SEC_OUT:
			Fla.Ent = ENT::ENT_00_ACT;		//行動選択に戻る
			break;
		}
	}
	// モンスターの行動を決める前にのみ一個前に戻れる処理
	else if (Key[KEY_INPUT_BACK] == 1) {
		if (Fla.Ent == ENT::ENT_01_TEC) { Fla.Ent = ENT::ENT_00_ACT; }
	}

	// 行動選択の判定処理
	if (Fla.Ent == ENT::ENT_00_ACT) {
		if (Cur.Act.X == 300 && Cur.Act.Y == 310) {
			Pla.Act = ACT::ACT_00_Battle;
		}
		else if (Cur.Act.X == 400 && Cur.Act.Y == 310) {
			Pla.Act = ACT::ACT_01_Exchange;
		}
		else if (Cur.Act.X == 300 && Cur.Act.Y == 350) {
			Pla.Act = ACT::ACT_02_Tool;
		}
		else if (Cur.Act.X == 400 && Cur.Act.Y == 350) {
			Pla.Act = ACT::ACT_03_Give_up;
		}
	}
	// 技選択や道具選択などの次の選択肢の判定処理
	else if (Fla.Ent == ENT::ENT_01_TEC) {
		switch (Pla.Act) {
		case ACT::ACT_00_Battle:		// 技発動
			if (Cur.Tec.X == 10 && Cur.Tec.Y == 310) {
				Pla.Tec = TEC::TEC_00;
			}
			else if (Cur.Tec.X == 130 && Cur.Tec.Y == 310) {
				Pla.Tec = TEC::TEC_01;
			}
			else if (Cur.Tec.X == 10 && Cur.Tec.Y == 350) {
				Pla.Tec = TEC::TEC_02;
			}
			else if (Cur.Tec.X == 130 && Cur.Tec.Y == 350) {
				Pla.Tec = TEC::TEC_03;
			}
			break;
		case ACT::ACT_01_Exchange:		// モンスター交換
			break;
		case ACT::ACT_02_Tool:			// 道具選択
			break;
		case ACT::ACT_03_Give_up:		// あきらめる選択肢
			break;
		}
	}
	else if (Fla.Ent >= ENT::ENT_02_FIR_CAL) {
		// コンピュータの処理関数
		CPU();
		// ダメージ計算処理関数
		Bat();
	}
}

void BATTLE::CPU() {
	Ene.Tec = 0;
	// ループで攻撃力が一番高い攻撃を選択するようにする
	for (int i = 0; i < 3; i++) {
		if (Tecnique[Ene.Out.Tec[i]].A
			< Tecnique[Ene.Out.Tec[i + 1]].A) {
			Ene.Tec = i + 1;
		}
	}
}

void BATTLE::Bat() {
	// 素早さ比較
	if (Fla.Ent == ENT::ENT_02_FIR_CAL) {
		if (Pla.Out.S > Ene.Out.S) {
			Fla.Str = STR::STR_00_FIR;
		}
		else if (Pla.Out.S < Ene.Out.S) {
			Fla.Str = STR::STR_01_SEC;
		}
		if (Pla.Out.S = Ene.Out.S) {
			int r = GetRand(99);
			if (0 <= r && r <= 49) { Fla.Str = STR::STR_00_FIR; }
			else if (50 <= r && r <= 99) { Fla.Str = STR::STR_01_SEC; }
		}
	}

	// プレイヤーが先攻の場合
	if (Fla.Str == STR::STR_00_FIR) {
		// Playerの場合
		if (Tecnique[Pla.Out.Tec[Pla.Tec]].A != 0) {
			Fir.Tec_a = Tecnique[Pla.Out.Tec[Pla.Tec]].A;
			Fir.Poke_a = Pla.Out.A;
			Fir.Poke_b = Ene.Out.B;
		}
		else if (Tecnique[Pla.Out.Tec[Pla.Tec]].C != 0) {
			Fir.Tec_a = Tecnique[Pla.Out.Tec[Pla.Tec]].C;
			Fir.Poke_a = Pla.Out.C;
			Fir.Poke_b = Ene.Out.D;
		}
		// Enemyの場合
		if (Tecnique[Ene.Out.Tec[Ene.Tec]].A != 0) {
			Sec.Tec_a = Tecnique[Ene.Out.Tec[Pla.Tec]].A;
			Sec.Poke_a = Ene.Out.A;
			Sec.Poke_b = Pla.Out.B;
		}
		else if (Tecnique[Ene.Out.Tec[Ene.Tec]].C != 0) {
			Sec.Tec_a = Tecnique[Ene.Out.Tec[Ene.Tec]].C;
			Sec.Poke_a = Ene.Out.C;
			Sec.Poke_b = Pla.Out.D;
		}
	}
	// 敵が先攻の場合
	else if (Fla.Str==STR::STR_01_SEC) {
		// Enemyの場合
		if (Tecnique[Ene.Out.Tec[Ene.Tec]].A != 0) {
			Fir.Tec_a = Tecnique[Ene.Out.Tec[Ene.Tec]].A;
			Fir.Poke_a = Ene.Out.A;
			Fir.Poke_b = Pla.Out.B;
		}
		else if (Tecnique[Ene.Out.Tec[Ene.Tec]].C != 0) {
			Fir.Tec_a = Tecnique[Ene.Out.Tec[Ene.Tec]].C;
			Fir.Poke_a = Ene.Out.C;
			Fir.Poke_b = Pla.Out.D;
		}
		// Playerの場合
		if (Tecnique[Pla.Out.Tec[Pla.Tec]].A != 0) {
			Sec.Tec_a = Tecnique[Pla.Out.Tec[Pla.Tec]].A;
			Sec.Poke_a = Pla.Out.A;
			Sec.Poke_b = Ene.Out.B;
		}
		else if (Tecnique[Pla.Out.Tec[Pla.Tec]].C != 0) {
			Sec.Tec_a = Tecnique[Pla.Out.Tec[Pla.Tec]].C;
			Sec.Poke_a = Pla.Out.C;
			Sec.Poke_b = Ene.Out.D;
		}
	}

	// 名前情報の取得
	if (Fla.Str == STR::STR_00_FIR) {
		for (int n = 0; n < 100; n++) {
			// モンスターの名前を取得
			Fir.Poke_n[n] = Pla.Out.Name[n];
			Sec.Poke_n[n] = Ene.Out.Name[n];
			// 技の名前を取得
			Fir.Tec_n[n] = Tecnique[Pla.Out.Tec[Pla.Tec]].name[n];
			Sec.Tec_n[n] = Tecnique[Ene.Out.Tec[Ene.Tec]].name[n];
		}
	}
	else if (Fla.Str == STR::STR_01_SEC) {
		for (int n = 0; n < 100; n++) {
			// モンスターの名前を取得
			Fir.Poke_n[n] = Ene.Out.Name[n];
			Sec.Poke_n[n] = Pla.Out.Name[n];
			// 技の名前を取得
			Fir.Tec_n[n] = Tecnique[Ene.Out.Tec[Ene.Tec]].name[n];
			Sec.Tec_n[n] = Tecnique[Pla.Out.Tec[Pla.Tec]].name[n];
		}
	}

	// ダメージ計算処理
	// 先攻がプレイヤーの場合
	if (Fla.Str == STR::STR_00_FIR) {
		if (Fla.Ent == ENT::ENT_02_FIR_CAL) {
			Ene.Dam = Damage(Fir.Tec_a, Fir.Poke_a, Fir.Poke_b);
			Ene.HPg = HPgau(Pokemon[Ene.Out.No].H, Ene.Out.H, Ene.Dam);
			Ene.Out.H = Ene.Out.H - Ene.Dam;
			Fla.Ent = ENT::ENT_02_FIR_CAL + 1;

		}
		else if (Fla.Ent == ENT::ENT_04_SEC_CAL) {
			Pla.Dam = Damage(Sec.Tec_a, Sec.Poke_a, Sec.Poke_b);
			Pla.HPg = HPgau(Pokemon[Pla.Out.No].H, Pla.Out.H, Pla.Dam);
			Pla.Out.H = Pla.Out.H - Pla.Dam;
			Fla.Ent = ENT::ENT_04_SEC_CAL + 1;

		}
	}

}

// ダメージ計算処理関数
int BATTLE::Damage(int tec_a, int a, int b) {
	// モンスターのレベルは50固定にする
	int level = 50;
	// ポケモンの方の計算式を元にした計算を返す
	return (int)((((level + 2, 0 / 5.0 + 2.0)
		* tec_a * a) / b / 50.0 + 2.0));
}

// HPゲージ処理関数
int BATTLE::HPgau(int h_i, int h, int dam) {
	double rate;
	double gau;

	rate = 145.0 / (double)h_i;
	gau = rate * (h - dam);
	if (gau < 0.0)gau = 0.0;
	return (int)gau;
}

// 描画系の関数
void BATTLE::Cha() {
	DrawGraph(0, 0, Pic.Bat, TRUE);

	if (Ene.Out.H < 0) { Ene.Out.H = 0; }
	if (Pla.Out.H < 0) { Pla.Out.H = 0; }

	// HPゲージ描画(Enemy)
	DrawBox(20, 30, 20 + 200, 30 + 80, Col.Whi, TRUE);
	DrawBox(20, 30, 20 + 200, 30 + 80, Col.Bla, FALSE);
	DrawBox(65, 70, 65 + Ene.HPg, 70 + 20, Col.Gre, TRUE);
	DrawBox(65, 70, 65 + 145, 70 + 20, Col.Bla, FALSE);
	// Enemy側の名前表示
	DrawFormatString(25, 35, Col.Red, "Enemy");
	// Enemy側のモンスターの名前表示
	DrawFormatString(65, 50, Col.Bla, 
		"%s", Ene.Out.Name);
	// Enemy側のモンスター体力数値表示
	DrawFormatString(65, 90, Col.Bla, 
		"%d/%d", Ene.Out.H, Pokemon[Ene.Out.No].H);
	// Enemy側のモンスターの画像
	DrawRotaGraph(365, 80, 2.5, 0.0,
		Pic.Poke[Ene.Out.No], TRUE);

	// HPゲージ描画(Player)
	DrawBox(280, 180, 280 + 200, 180 + 80, Col.Whi, TRUE);
	DrawBox(280, 180, 280 + 200, 180 + 80, Col.Bla, FALSE);
	DrawBox(330, 220, 330 + Pla.HPg, 220 + 20, Col.Gre, TRUE);
	DrawBox(330, 220, 330 + 145, 220 + 20, Col.Bla, FALSE);
	// Player側の名前表示
	DrawFormatString(285, 185, Col.Blu, "Player");
	// Player側のモンスターの名前表示
	DrawFormatString(330, 200, Col.Bla,
		"%s", Pla.Out.Name);
	// Player側のモンスター体力数値表示
	DrawFormatString(330, 240, Col.Bla,
		"%d/%d", Pla.Out.H, Pokemon[Pla.Out.No].H);
	// Player側のモンスターの画像
	DrawRotaGraph(120, 200, 2.5, 0.0,
		Pic.Poke[Pla.Out.No], TRUE);

	switch (Fla.Ent){
	case ENT::ENT_00_ACT:
		DrawBox(20, 300, 250, 350, Col.Whi, TRUE);
		DrawBox(20, 300, 250, 350, Col.Bla, FALSE);
		DrawBox(290, 300, 495, 380, Col.Whi, TRUE);
		DrawBox(290, 300, 495, 380, Col.Bla, FALSE);
		DrawFormatString(30, 310, Col.Bla, "%s",
			Pla.Out.Name);
		DrawFormatString(130, 310, Col.Blu, "(Player)",
			Pla.Out.Name);
		DrawFormatString(30, 330, Col.Bla, "はどうする？",
			Pla.Out.Name);
		DrawFormatString(Cur.Act.X, Cur.Act.Y, Col.Bla, "→");
		DrawFormatString(320, 310, Col.Bla, "たたかう");
		DrawFormatString(420, 310, Col.Bla, "ポケモン");
		DrawFormatString(320, 350, Col.Bla, "どうぐ");
		DrawFormatString(420, 350, Col.Bla, "にげる");
		break;
	case ENT::ENT_01_TEC:
		switch (Pla.Act) {
		case ACT::ACT_00_Battle:
			DrawFormatString(Cur.Tec.X, Cur.Tec.Y, Col.Bla, "→");
			DrawFormatString(30, 310, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[0]].name);
			DrawFormatString(250, 310, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[1]].name);
			DrawFormatString(30, 350, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[2]].name);
			DrawFormatString(250, 350, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[3]].name);
			break;
		case ACT::ACT_01_Exchange:
			DrawFormatString(30, 310, Col.Bla, 
				"パチモン交換処理は無いよん");
			break;
		case ACT::ACT_02_Tool:
			DrawFormatString(30, 310, Col.Bla,
				"道具を所持していません");
			break;
		case ACT::ACT_03_Give_up:
			DrawFormatString(30, 310, Col.Bla,
				"降参処理はありません");
			break;
		}
		break;
	case ENT::ENT_02_FIR_CAL:
		break;
	case ENT::ENT_03_FIR_OUT:
		DrawFormatString(30, 310, Col.Bla,
			"%sの%s!", Fir.Poke_n, Fir.Tec_n);
		DrawFormatString(30, 330, Col.Bla,
			"効果はふつうだ");
		DrawFormatString(30, 350, Col.Bla,
			"%dのダメージを与えた", Damage(Fir.Tec_a, Fir.Poke_a, Fir.Poke_b));
		// 倒したときの分岐
		if (Sec.Fal == 1) {
			Sec.Fal = 0;
			DrawFormatString(30, 370, Col.Bla,
				"%sは倒れた", Sec.Poke_n);
		}
		break;
	case ENT::ENT_04_SEC_CAL:
		break;
	case ENT::ENT_05_SEC_OUT:
		DrawFormatString(30, 310, Col.Bla,
			"%sの%s!", Sec.Poke_n, Sec.Tec_n);
		DrawFormatString(30, 330, Col.Bla,
			"効果はふつうだ");
		DrawFormatString(30, 350, Col.Bla,
			"%dのダメージを与えた", Damage(Sec.Tec_a, Sec.Poke_a, Sec.Poke_b));
		// 倒したときの分岐
		if (Fir.Fal == 1) {
			Fir.Fal = 0;
			DrawFormatString(30, 370, Col.Bla,
				"%sは倒れた", Fir.Poke_n);
		}
		break;
	}
}