#pragma once
#include	"SceneManager.h"


//static bool is_finish = false;

class Battle : public IScene
{
private:
	unsigned int m_TextKeepTime;
	bool is_finish = false;
public:
	
	void Init();
	void Input();
	void Draw();
	void Update();
	void Dispose();

	bool FinishBattle()
	{
		return &is_finish;
	}
	// バトル開始から大まかな流れ
	enum class TURN_ID {
		NONE,
		START,           // 何が出現したか文字描画

		BATTLE,

		SELLECT,         // 行動選択
		COMMAND_SKILL,   // wazaコマンド
		CHHECK_SPEED,
		MY_TURN,         // 自分のターン開始
		MY_TURN_END,     // 自分のターン終わり
		ENEMY_TURN,      // 敵のターン開始
		ENEMY_TURN_END,  // 敵のターン終わり

		BAG,             // もちもの

		MONSTER,         // 手持ちモンスター

		EXIT,

		FINISH,

	};

	//TURN_ID current_turn = TURN_ID::START;
	TURN_ID current_turn;
	TURN_ID ChangeTurn(TURN_ID id)
	{
		current_turn = id;
		return current_turn;
	}
};

