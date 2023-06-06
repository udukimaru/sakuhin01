#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "CTitle.h"
#include "Encounter.h"
#include "CSceneMgr.h"
#include "game.h"
#include "Battle.h"
#include "SceneManager.h"
#include "M_Plain.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CCommand.h"

#include <thread>

CTitle title;
Encounter enc;
Battle battle;
//SceneManager	g_manager;
M_Plain plain;
CPlayer pl;

CCommand com;
float game_time = 0.0f;

void GameInit() {
	// DX11初期化
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		false);

	// カメラが必要
	DirectX::XMFLOAT3 eye(0, 20, -10);		// カメラの位置
	DirectX::XMFLOAT3 lookat(0, 0, 0);		// 注視点
	DirectX::XMFLOAT3 up(0, 1, 0);			// カメラの上向きベクトル

	CCamera::GetInstance()->Init(
		10.0f,							// ニアクリップ
		1000.0f,						// ファークリップ
		XM_PI / 5.0f,					// 視野角
		static_cast<float>(Application::CLIENT_WIDTH),		// スクリーン幅
		static_cast<float>(Application::CLIENT_HEIGHT),		// スクリーンの高さ
		eye, lookat, up);					// カメラのデータ

	CCamera::GetInstance()->CreateProjectionMatrix();
	CCamera::GetInstance()->CreateCameraMatrix();
	// 平行光源をセット
	DX11LightInit(
		DirectX::XMFLOAT4(1, 1, -1, 0));

	// DIRECTINPUT初期化
	CDirectInput::GetInstance().Init(
		Application::Instance()->GetHInst(),
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,			// スクリーン幅
		Application::CLIENT_HEIGHT			// スクリーンの高さ
		);

	//// アルファブレンド有効化
	//TurnOnAlphablend();
	//CSceneMgr::SCENE_ID::TITLE;
	//CSceneMgr::Init();
	// 空中戦初期化
	//Encounter::GetInstance().Init();
	//CTitle::GetInstance().Init();
	title.Init();

	// アルファブレンド有効化
	TurnOnAlphablend();

	/*pl.Init();
	plain.Init();*/
	
	// シーンマネージャにタイトルシーンを登録
	/*g_manager.add<CTitle>("TitleScene");
	g_manager.add<Encounter>("Encount");
	g_manager.add<Battle>("BattleScene");*/

	// 現在シーンをGameMainにする
	//g_manager.setCurrentScene("BattleScene");
}

void GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
	CDirectInput::GetInstance().GetMouseState();
}

void GameUpdate(uint64_t dt) {

	title.Update();
	// キー入力で遷移
	/*if (CDirectInput::GetInstance().GetMouseLButtonTrigger()) {

		if (g_manager.GetCurrentSceneKey() == "TitleScene") {
			g_manager.SetFadeColor(XMFLOAT4(0, 0, 0, 1));
			g_manager.changeScene<Encounter>("Encount", 2000, false);

		}
	}*/
	//// 敵に当たるとバトルシーンに
	////生きているときだけ当たり判定
	//if (plain.isActive== true && g_manager.GetCurrentSceneKey() == "Encount") {
	//	
	//		bool res = CCollider::Test(pl.GetPos(), plain.GetPos());
	//		if (res == true)
	//		{
	//			if (++game_time >= 0 && game_time <= 50) {
	//				g_manager.changeScene<Battle>("BattleScene", 1000, false);
	//			}
	//		}
	//}
	//if (g_manager.GetCurrentSceneKey() == "Encount") {
	//	pl.Update();
	//	plain.Update();
	//}
	//// タイトル画面→バトルシーン
	//if (CDirectInput::GetInstance().GetMouseLButtonTrigger()) {
	//	if (g_manager.GetCurrentSceneKey() == "TitleScene") {
	//		g_manager.changeScene<Battle>("BattleScene", 2000, false);
	//	}
	//}
	///*if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
	//	if (g_manager.GetCurrentSceneKey() == "TitleScene")
	//	{
	//		g_manager.changeScene<Encounter>("Encount", 1000, false);
	//	}
	//}*/
	///*if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
	//	if (g_manager.GetCurrentSceneKey() == "Encount") {
	//		g_manager.changeScene<Battle>("BattleScene", 1000, false);
	//	}
	//}*/

	//// カーソル位置取得
	//XMFLOAT2 cursor_pos = {};
	//cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
	//cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();

	//XMFLOAT2 exitpos = { 1120,com.g_buttunlist[3].y };

	//// にげる遷移
	//if (battle.current_turn==Battle::TURN_ID::EXIT)
	//{

	//	//if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
	//	//{
	//       // カレントシーンを更新
	//		if (g_manager.GetCurrentSceneKey() == "BattleScene")
	//		{
	//			g_manager.changeScene<Encounter>("Encount", 2000, false);
	//		}
	//	//}
	//}
	//g_manager.Update();

	//}
}

void GameRender(uint64_t dt) {

	//TurnOnZbuffer();
	float col[4] = { 1,0,0,1 };

	// 描画前処理
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;

	// プロジェクション変換行列取得
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// ビュー変換行列を取得
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);
	// カレントシーン描画
	//g_manager.Draw();
	// 空中戦描画
	//Encounter::GetInstance().Draw();
	//CTitle::GetInstance().Draw();
	//CSceneMgr::Render();
	title.Draw();
	// 描画後処理
	DX11AfterRender();
}

void GameDispose() {

	// 空中戦終了処理
	//Encounter::GetInstance().Finalize();
	//CTitle::GetInstance().Finalize();
	//CSceneMgr::Finalize();
	//Battle::GetInstance().Finalize();
	DX11Uninit();
}