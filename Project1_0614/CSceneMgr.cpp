#include "CSceneMgr.h"
#include "CTitle.h"
#include "Encounter.h"
#include "Battle.h"

//BaseScene *CSceneMgr::mp_scene = nullptr;

CSceneMgr::SCENE_ID CSceneMgr::ChangeScene(SCENE_ID id)
{

	current_scene = id;
	return current_scene;
}

//void CSceneMgr::Init()
//{
//	CSceneMgr::mp_scene->Init();
//}
//
//void CSceneMgr::Update()
//{
//	CSceneMgr::mp_scene->Update();
//}
//
//void CSceneMgr::Render()
//{
//	CSceneMgr::mp_scene->Draw();
//}
//
//void CSceneMgr::Finalize()
//{
//	CSceneMgr::mp_scene->Finalize();
//}
