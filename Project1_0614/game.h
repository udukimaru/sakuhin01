#pragma once
#include <cinttypes>

//enum class SCENEID {
//	TITLE,
//	MAIN,
//	ENCOUNTER,
//	BATTLE,
//};
//
//SCENEID next_current;

static bool change = false;

//enum class SCENE
//{
//	SCENE_TITLE_INIT,
//	SCENE_TITLE,
//
//	SCENE_ENCOUNTER_INIT,
//	SCENE_ENCOUNTER,
//
//	SCENE_BATTLE_INIT,
//	SCENE_BATTLE,
//
//	SCENE_GAMECLEAR_START,
//	SCENE_GAMECLEAR,
//
//	SCENE_GAMEOVER_START,
//	SCENE_GAMEOVER,
//
//	SCENE_FADE,
//
//};
//SCENE mnext_scene;
//SCENE mcurrent_scene;

void GameInit();
void GameInput(uint64_t dt);
void GameUpdate(uint64_t dt);
void GameRender(uint64_t dt);
void GameDispose();