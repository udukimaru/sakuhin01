#pragma once
#include "BaseScene.h"
class CSceneMgr
{
public:
	enum class SCENE_ID {
		TITLE,
		MAIN,
		ENCOUNTER,
		BATTLE,

		TEST,

		MOTION_EDIT,
	};

	SCENE_ID ChangeScene(SCENE_ID id);

	SCENE_ID current_scene = SCENE_ID::TITLE;
	SCENE_ID old_scene;
	SCENE_ID next_scene;

	static CSceneMgr* GetInstance() {
		static CSceneMgr instance;
		return &instance;
	}
private:

	//static BaseScene* mp_scene;
};

