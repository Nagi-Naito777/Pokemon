#pragma once

class TITLE {
public:
	void Out() {
		DrawGraph(0, 0, Pic.Tit, TRUE);
		DrawFormatStringToHandle(150, 300, Col.Bla,
			Fon.c[20], "Press Enter Key.");
		if (Key[KEY_INPUT_NUMPADENTER] == 1) {
			Sce = MEN::MEN_01_SELECT;
		}
	}
	
private:
};

//TITLEƒNƒ‰ƒX‚ÅTit‚ð’è‹`
TITLE Tit;