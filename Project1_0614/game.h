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

void GameInit();
void GameInput(uint64_t dt);
void GameUpdate(uint64_t dt);
void GameRender(uint64_t dt);
void GameDispose();