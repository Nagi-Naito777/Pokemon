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

	// 計算系の関数
	void Cal();
	// パチモンを出力する関数
	void Cha();
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
			Cur.Tec.X = 130;
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

	// ダメージ計算関係処理

}

// 描画系の関数
void BATTLE::Cha() {
	DrawGraph(0, 0, Pic.Bat, TRUE);

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
			DrawFormatString(150, 310, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[1]].name);
			DrawFormatString(30, 350, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[2]].name);
			DrawFormatString(150, 350, Col.Bla, "%s",
				Tecnique[Pla.Out.Tec[3]].name);
			break;
		case ACT::ACT_01_Exchange:
			DrawFormatString(30, 310, Col.Bla, 
				"ポケモンを交換する処理は無いよん");
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
		break;
	case ENT::ENT_04_SEC_CAL:
		break;
	case ENT::ENT_05_SEC_OUT:
		break;
	}
}