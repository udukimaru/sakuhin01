#pragma once
#include	"SceneManager.h"


static bool is_finish = false;

class Battle : public IScene
{
private:
	unsigned int m_TextKeepTime;
public:
	//
	void RandAttack();
	void TurnAction();
	void EnemyTurnBattle();
	void Init();
	void Input();
	void Draw();
	void Update();
	void Dispose();

	/*bool FinishBattle()
	{
		return is_finish;
	}*/


	/*static Battle& GetInstance() {
		static Battle Instance;
		return Instance;
	}*/
};

