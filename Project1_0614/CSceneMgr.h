#pragma once
#include "BaseScene.h"
class CSceneMgr
{
public:
	enum class SCENE_ID {
		TITLE,
		ENCOUNTER,
		BATTLE,

	};

	SCENE_ID current_scene = SCENE_ID::TITLE;
	SCENE_ID old_scene;
	SCENE_ID next_scene;

	void ChangeScene(SCENE_ID id)
	{
		current_scene = id;
	}

	SCENE_ID Change(SCENE_ID id)
	{

	}


	static CSceneMgr* GetInstance() {
		static CSceneMgr instance;
		return &instance;
	}
private:
	//BaseScene* m_pScene;
	//static BaseScene* mp_scene;
};

