//*****************************************************************************
//!	@file	Application.cpp
//!	@brief	
//!	@note	アプリケーションクラス
//!	@author	
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
//#include <cinttypes>
#include "Application.h"
#include "CWindow.h"
#include "macro.h"
#include "game.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "dx11util.h"
#include "CDirectInput.h"
#include "CTitle.h"
#include "Battle.h"
#include "CSceneMgr.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
const char* Application::WINDOW_TITLE = "作品";
const char* Application::WINDOW_CLASS_NAME = "win32app";

const uint32_t		Application::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t		Application::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t		Application::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t		Application::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t		Application::CLIENT_WIDTH = 1280;//1280
const uint32_t		Application::CLIENT_HEIGHT = 720;//720

uint32_t			Application::SYSTEM_WIDTH = 0;
uint32_t			Application::SYSTEM_HEIGHT = 0;

const float			Application::FPS = 60;

//==============================================================================
//!	@fn		CApplication
//!	@brief	コンストラクタ
//!	@param	
//!	@retval	
//==============================================================================
Application :: Application(): m_SystemCounter		( 0 )
{}

//==============================================================================
//!	@fn		~Application
//!	@brief	デストラクタ
//!	@param	
//!	@retval	
//==============================================================================
Application :: ~Application()
{
	Dispose();
}

//==============================================================================
//!	@fn		GetInstance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
Application* Application::Instance()
{
	static Application Instance;

	return &Instance;
}

//==============================================================================
//!	@fn		InitSystemWH
//!	@brief	システム領域の幅と高さを初期化
//!	@param	
//!	@retval	
//==============================================================================
void Application :: InitSystemWH()
{
	
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	インスタンスハンドル
//!	@retval	
//==============================================================================
bool Application :: Init( HINSTANCE h_Instance )
{
	// メモリーリークを検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

	// コンソールを割り当てる
	AllocConsole();

	// 標準出力の割り当て
	freopen_s(&m_fp, "CON", "w", stdout);    

	// 幅と高さ初期化
	InitSystemWH();

	// ウインドウ作成
	CWindow* window = CWindow::Instance();
	window->RegisterClass( h_Instance, WINDOW_CLASS_NAME, CS_OWNDC );

	window->SetWindow( h_Instance,
					   WINDOW_STYLE_WINDOWED,
					   WINDOW_EX_STYLE_WINDOWED,
					   NULL,
					   CLIENT_WIDTH + SYSTEM_WIDTH,
					   CLIENT_HEIGHT + SYSTEM_HEIGHT,
					   WINDOW_CLASS_NAME,
					   WINDOW_TITLE,
					   false);
			
	// HWND
	m_hWnd = window->GetHandle();

	//
	m_hInst = h_Instance;
	return true;
}

//==============================================================================
//!	@fn		Dispose
//!	@brief  終了処理
//!	@param	
//!	@retval	
//==============================================================================
void Application :: Dispose()
{
	// 標準出力クローズ
	fclose(m_fp);
	// コンソール開放
	::FreeConsole();

	return;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	メインループ
//!	@param	
//!	@retval	メッセージID
//==============================================================================
unsigned long Application :: MainLoop()
{
	MSG		msg;	
	ZeroMemory( &msg, sizeof( msg ) );	

	CWindow* window = CWindow::Instance();

	uint64_t current_time = 0;
	uint64_t last_time = 0;

	//// DX11初期化
	//DX11Init(
	//	Application::Instance()->GetHWnd(),
	//	Application::CLIENT_WIDTH,
	//	Application::CLIENT_HEIGHT,
	//	false);

	////// カメラが必要
	////DirectX::XMFLOAT3 eye(0, 0, -30);		// カメラの位置
	////DirectX::XMFLOAT3 lookat(0, 0, 0);		// 注視点
	////DirectX::XMFLOAT3 up(0, 1, 0);			// カメラの上向きベクトル

	////CCamera::GetInstance()->Init(
	////	10.0f,							// ニアクリップ
	////	1000.0f,						// ファークリップ
	////	XM_PI / 5.0f,					// 視野角
	////	static_cast<float>(Application::CLIENT_WIDTH),		// スクリーン幅
	////	static_cast<float>(Application::CLIENT_HEIGHT),		// スクリーンの高さ
	////	eye, lookat, up);					// カメラのデータ

	//// 平行光源をセット
	//DX11LightInit(
	//	DirectX::XMFLOAT4(1, 1, -1, 0));

	//// DIRECTINPUT初期化
	//CDirectInput::GetInstance().Init(
	//	Application::Instance()->GetHInst(),
	//	Application::Instance()->GetHWnd(),
	//	Application::CLIENT_WIDTH,			// スクリーン幅
	//	Application::CLIENT_HEIGHT			// スクリーンの高さ
	//);

	//// アルファブレンド有効化
	//TurnOnAlphablend();


	// ゲームの初期処理
	GameInit();
	//CTitle::GetInstance().Init();

	// タイマ解像度をミリ秒に
	::timeBeginPeriod(1);

	while (window->ExecMessage()) {

		// timeGetTime関数は、ミリ秒単位でシステム時刻を取得します。 
		// システム時間は、Windowsを起動してからの経過時間です。
		current_time = ::timeGetTime();	

		uint64_t delta_time = current_time - last_time;

		last_time = current_time;


		//switch (CSceneMgr::GetInstance()->current_scene)
		//{
		//case CSceneMgr::SCENE_ID::TITLE:
		//	CTitle::GetInstance().Input();
		//	CTitle::GetInstance().Update();
		//	CTitle::GetInstance().Draw();
		//	break;
		//case CSceneMgr::SCENE_ID::ENCOUNTER:
		//	GameInput(delta_time);		// ｹﾞｰﾑ入力	
		//	GameUpdate(delta_time);		// ｹﾞｰﾑ更新
		//	GameRender(delta_time);		// ｹﾞｰﾑ描画
		//	break;
		//case CSceneMgr::SCENE_ID::BATTLE:
		//	Battle::GetInstance().Input();
		//	Battle::GetInstance().Update();
		//	Battle::GetInstance().Draw();
		//	break;
		//case CSceneMgr::SCENE_ID::TEST:
		//	Test::GetInstance().Input();
		//	Test::GetInstance().Update();
		//	Test::GetInstance().Draw();
		//	break;
		//}
		GameInput(delta_time);		// ｹﾞｰﾑ入力	
		GameUpdate(delta_time);		// ｹﾞｰﾑ更新
		GameRender(delta_time);		// ｹﾞｰﾑ描画

		int64_t sleep_time = 16666 - delta_time;

		if (sleep_time > 0) {
			float tt = sleep_time / 1000.0f;
//			printf("sleep:%f \n", tt);
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
			//指定した相対時間だけ現スレッドをブロックする (function template)
		}
	}

	// タイマ解像度を元に戻す
	::timeEndPeriod(1);

	// ゲームの終了処理
	GameDispose();
	/*switch (CSceneMgr::GetInstance()->current_scene)
	{
	case CSceneMgr::SCENE_ID::TITLE:
		CTitle::GetInstance().Finalize();
		break;
	case CSceneMgr::SCENE_ID::ENCOUNTER:
		GameDispose();
		break;
	case CSceneMgr::SCENE_ID::BATTLE:
		Battle::GetInstance().Finalize();
		break;
	case CSceneMgr::SCENE_ID::TEST:
		Test::GetInstance().Finalize();
		break;
	}*/

	return window->GetMessage();
}

//==============================================================================
//!	@fn		Input
//!	@brief	キー入力
//!	@param	
//!	@retval	
//==============================================================================
void Application :: Input(uint64_t deltataime)
{
}

//==============================================================================
//!	@fn		Update
//!	@brief	更新
//!	@param	
//!	@retval	
//==============================================================================
void Application :: Update(uint64_t deltataime)
{
	// システムカウンタ
	m_SystemCounter ++;
}

//==============================================================================
//!	@fn		Render
//!	@brief	描画
//!	@param	
//!	@retval	
//==============================================================================
void Application :: Render(uint64_t deltatime)
{
}

//==============================================================================
//!	@fn		GetHWnd
//!	@brief	HWND 取得
//!	@param	
//!	@retval	HWND
//==============================================================================
HWND Application :: GetHWnd()
{
	return m_hWnd;
}

//==============================================================================
//!	@fn		GetHInst
//!	@brief	HINSTANCE 取得
//!	@param	
//!	@retval	HINSTANCE
//==============================================================================
HINSTANCE Application::GetHInst()
{
	return m_hInst;
}

//******************************************************************************
//	End of file.
//******************************************************************************
