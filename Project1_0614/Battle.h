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
	// �o�g���J�n�����܂��ȗ���
	enum class TURN_ID {
		NONE,
		START,           // �����o�������������`��

		BATTLE,

		SELLECT,         // �s���I��
		COMMAND_SKILL,   // waza�R�}���h
		CHHECK_SPEED,
		MY_TURN,         // �����̃^�[���J�n
		MY_TURN_END,     // �����̃^�[���I���
		ENEMY_TURN,      // �G�̃^�[���J�n
		ENEMY_TURN_END,  // �G�̃^�[���I���

		BAG,             // ��������

		MONSTER,         // �莝�������X�^�[

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

