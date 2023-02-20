#pragma once

#include	<string>
#include	<unordered_map>
#include	<functional>
#include	<iostream>
#include	<memory>
#include	<directxmath.h>
#include	<chrono>
#include	<thread>
#include	"SceneManager.h"
#include	"uncopyable.h"
#include	"StopWatch.h"
#include	"quad2d.h"
#include	"Application.h"

class SceneManager;

class IScene : Uncopyable {
private:
	SceneManager* m_manager;
public:
	IScene();
	void SetSceneManager(SceneManager* sm) {
		m_manager = sm;
	}

	virtual ~IScene() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Dispose() = 0;

	virtual void updateFadeIn(double t);
	virtual void updateFadeOut(double t);

	virtual void drawFadeIn(double t);
	virtual void drawFadeOut(double t);
};