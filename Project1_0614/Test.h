#pragma once
#include "CSceneMgr.h"
class Test :
    public BaseScene
{
public:
	void Init();
	void Input();
	void Finalize();
	void Update();
	void Draw();

	static Test& GetInstance() {
		static Test Instance;
		return Instance;
	}
};

