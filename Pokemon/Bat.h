#pragma once
class BATTLE {
public:
	// 外部から入る用の出力関数
	void Out() {
		Cal();
		Cha();
	}
private:
	//
	void Cal();
	// パチモンを出力する関数
	void Cha();
};

// インスタンス宣言
BATTLE Bat;

void BATTLE::Cal() {

}

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
}