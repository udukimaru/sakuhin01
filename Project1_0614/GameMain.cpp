#include "GameMain.h"
#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"

#include "CFade.h"
#include"CCreateString.h"

GameMain::SCENE GameMain::Current_scene;
CFade* mFade;
CCreateString* load;

void GameMain::GameInit()
{
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

	Next_scene = SCENE::SCENE_TITLE_INIT;

	title = new CTitle();
	enc = new Encounter();
	battle = new Battle();
	mFade = new CFade();
	mFade->Init();

	// 文字描画
	FontData* data = new FontData();
	data->fontSize = 30;
	data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;

	load = new CCreateString(data);
	load->Init();
	// アルファブレンド有効化
	TurnOnAlphablend();
}

void GameMain::GameInput(uint64_t dt)
{
	CDirectInput::GetInstance().GetKeyBuffer();
	CDirectInput::GetInstance().GetMouseState();
}

void GameMain::GameUpdate(uint64_t dt)
{
	switch (Current_scene)
	{
	case SCENE::SCENE_TITLE_INIT:
		title->Init();
		Current_scene = SCENE::SCENE_FADE;
		Next_scene = SCENE::SCENE_TITLE;
		break;
	case SCENE::SCENE_TITLE:
		title->Update();
		if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
		{
			Current_scene = SCENE::SCENE_FADE;
			Next_scene = SCENE::SCENE_ENCOUNTER_INIT;
		}
		break;
	case SCENE::SCENE_ENCOUNTER_INIT:
		//mFade->FadeIn();
		enc->Init();
		Current_scene = SCENE::SCENE_FADE;
		Next_scene = SCENE::SCENE_ENCOUNTER;
		break;
	case SCENE::SCENE_ENCOUNTER:
		enc->Update();
		if (enc->EncToBattle() == true)
		{
			Current_scene = SCENE::SCENE_FADE;
			Next_scene = SCENE::SCENE_BATTLE_INIT;
		}
		break;
	case SCENE::SCENE_BATTLE_INIT:
		mFade->FadeOut();
		battle->Init();
		Current_scene = SCENE::SCENE_FADE;
		Next_scene = SCENE::SCENE_BATTLE;
		break;
	case SCENE::SCENE_BATTLE:
		battle->Update();
		if (battle->FinishBattle() == true)
		{
			Current_scene = SCENE::SCENE_FADE;
			Next_scene = SCENE::SCENE_TITLE;
		}
		break;
	case SCENE::SCENE_GAMECLEAR_START:
		break;
	case SCENE::SCENE_GAMECLEAR:
		break;
	case SCENE::SCENE_GAMEOVER_START:
		break;
	case SCENE::SCENE_GAMEOVER:
		break;
	case SCENE::SCENE_FADE:
	mFade->Update();

	if (mFade->GetState() == CFade::FADE_STATE::NONE)
	{
		Current_scene = Next_scene;
	}
		break;
	default:
		break;
	}
}

void GameMain::GameRender(uint64_t dt)
{
	float col[4] = { 0,0,0,1 };

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
	//title.Draw();

	switch (Current_scene)
	{
	case SCENE::SCENE_TITLE_INIT:
		load->DrawString("Loading", XMFLOAT2(200, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
		//title->Draw();
		break;
	case SCENE::SCENE_TITLE:
		title->Draw();
		break;
	case SCENE::SCENE_ENCOUNTER_INIT:
		load->DrawString("Loading", XMFLOAT2(200, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
		break;
	case SCENE::SCENE_ENCOUNTER:
		enc->Draw();
		break;
	case SCENE::SCENE_BATTLE_INIT:
		break;
	case SCENE::SCENE_BATTLE:
		battle->Draw();
		break;
	case SCENE::SCENE_GAMECLEAR_START:
		break;
	case SCENE::SCENE_GAMECLEAR:
		break;
	case SCENE::SCENE_GAMEOVER_START:
		break;
	case SCENE::SCENE_GAMEOVER:
		break;
	case SCENE::SCENE_FADE:
		mFade->Draw();
		load->DrawString("Loading", XMFLOAT2(200, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
		break;
	default:
		break;
	}
	// 描画後処理
	DX11AfterRender();
}

void GameMain::GameDispose()
{
	delete mFade;
}
