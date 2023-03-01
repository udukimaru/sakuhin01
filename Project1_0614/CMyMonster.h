#pragma once
class CMyMonster
{
	enum class MY_MONSTER {
		NONE,
		MONSTER_WINDOW,
		MONSTER_DATA1,
		MONSTER_DATA2,
		MONSTER_DATA3,
		MONSTER_DATA4,
		MONSTER_DATA5,
		MONSTER_DATA6,
		MONSTER_DATA_FRAME,
		BACK,
		BACK_SHADOW,
		MAX,
	};
public:
	bool Init();
	void Draw();
	void Update();
};

