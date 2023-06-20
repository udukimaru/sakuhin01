#pragma once
#include <cinttypes>
#include "CTitle.h"
#include "Encounter.h"
#include "Battle.h"
class GameMain
{
public:
	enum class SCENE
	{
		SCENE_TITLE_INIT,
		SCENE_TITLE,

		SCENE_ENCOUNTER_INIT,
		SCENE_ENCOUNTER,

		SCENE_BATTLE_INIT,
		SCENE_BATTLE,

		SCENE_GAMECLEAR_START,
		SCENE_GAMECLEAR,

		SCENE_GAMEOVER_START,
		SCENE_GAMEOVER,

		SCENE_FADE,

	};
	static SCENE Current_scene;

	void GameInit();
	void GameInput(uint64_t dt);
	void GameUpdate(uint64_t dt);
	void GameRender(uint64_t dt);
	void GameDispose();

	void ChangeScene(SCENE id) {
		Next_scene = id;
	}
	SCENE* Change(SCENE &id) {
		return &id;
	}
private:
	SCENE Next_scene;

	CTitle* title;
	Encounter* enc;
	Battle* battle;
};

