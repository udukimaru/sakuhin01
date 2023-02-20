#pragma once
#include	"SceneManager.h"

class Encounter :public IScene {

public:

	Encounter();
	~Encounter();

	void Init();
	void Input();
	void Dispose();
	void Update();
	void Draw();

	bool change = false;

	bool EncToBattle() {
		return change;
	}
	/*static Encounter& GetInstance() {
		static Encounter Instance;
		return Instance;
	}*/
};