#include "CTitle.h"
#include "quad2d.h"
#include "CDirectInput.h"
#include "CSceneMgr.h"
#include "Encounter.h"
#include "CCamera.h"
#include "Test.h"
#include "Easing.h"
#include "CTitleUI.h"

//Quad2D title;
//Quad2D click;
//Quad2D click_niji;
//Quad2D star;
//Quad2D star2;
//Quad2D star3;
//Quad2D titlelogo;
CTitleUI g_title_UI;

XMFLOAT2 starPos = { 200,20 };
float star_t = 0;
float fade_t = 0.0f;

XMFLOAT4 color = { 1,1,1,1 };
XMFLOAT2 title_uv2[4] = {

		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
};

void Blink_Update() {
	fade_t += 0.01f;
	float alphaParam = fade_t - (int)fade_t;

	if (alphaParam < 0.5) {
		color.w = alphaParam * 2.0f;
	}
	else {
		color.w = 1.0f - (alphaParam - 0.5f) * 2.0f;
	}
}

void CTitle::Init()
{
	XMFLOAT2 uv2D[4] = {
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f}
	};
	//  UI
	/*title.Init(10, 10, XMFLOAT4(1, 1, 1, 1), uv2D);
	title.LoadTexture("assets/UI/title_background.png");

	click.Init(10, 4, XMFLOAT4(1, 1, 1, 1), uv2D);
	click.LoadTexture("assets/UI/start.png");

	click_niji.Init(10, 10, color, uv2D);
	click_niji.LoadTexture("assets/UI/start_niji.png");

	star.Init(1, 1, XMFLOAT4(1, 1, 1, 1), uv2D);
	star.LoadTexture("assets/UI/star.tga");
	star2.Init(1, 1, XMFLOAT4(1, 1, 1, 1), uv2D);
	star2.LoadTexture("assets/UI/star.tga");
	star3.Init(1, 1, XMFLOAT4(1, 1, 1, 1), uv2D);
	star3.LoadTexture("assets/UI/star.tga");

	titlelogo.Init(1, 1, XMFLOAT4(1, 1, 1, 1), uv2D);
	titlelogo.LoadTexture("assets/UI/title.tga");*/
	
	g_title_UI.InitTitle_UI();
	
}

void CTitle::Input()
{
	CDirectInput::GetInstance().GetKeyBuffer();
	CDirectInput::GetInstance().GetMouseState();
}

void CTitle::Draw()
{
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

	TurnOffZbuffer();
	XMFLOAT2 uv2[4] = {

		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};

	for (int i = 0; i < g_title_UI.uilist.size(); i++) {

		g_title_UI.DrawTitle_UI();
	}
	/*title.updateVertex(1300, 760, XMFLOAT4(1, 1, 1, 1), uv2);
	title.updateVbuffer();
	title.SetPosition(650, 380, 0);
	title.Draw();

	click.updateVertex(600, 280, color, title_uv2);
	click.updateVbuffer();
	click.SetPosition(640, 540, 0);
	click.Draw();*/

	/*click_niji.updateVertex(600, 280, color, title_uv2);
	click_niji.updateVbuffer();
	click_niji.SetPosition(640, 540, 0);
	click_niji.Draw();*/

	/*star.updateVertex(100, 100, XMFLOAT4(1, 1, 1, 1), uv2);
	star.updateVbuffer();
	star.SetPosition(starPos.x, starPos.y, 0);
	star.Draw();*/
	//star2.updateVertex(60, 60, XMFLOAT4(1, 1, 1, 1), uv2);
	//star2.updateVbuffer();
	//star2.SetPosition(starPos.x+50, starPos.y, 0);
	//star2.Draw();
	//star3.updateVertex(60, 60, XMFLOAT4(1, 1, 1, 1), uv2);
	//star3.updateVbuffer();
	//star3.SetPosition(starPos.x+100, starPos.y, 0);
	//star3.Draw();

	/*titlelogo.updateVertex(1200, 200, XMFLOAT4(1, 1, 1, 1), uv2);
	titlelogo.updateVbuffer();
	titlelogo.SetPosition(640, 250, 0);
	titlelogo.Draw();*/

	TurnOnZbuffer();

	// 描画後処理
	DX11AfterRender();
}

void CTitle::Update()
{
		star_t += 0.005f;
		starPos.y += CEasing::GetInstance().SinVibe(10,2, star_t);
		starPos.x += 3.0f;
	
	g_title_UI.UpdateTitle_UI();
	/*if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
	{
		Encounter::GetInstance().Init();
		CSceneMgr::GetInstance()->ChangeScene(CSceneMgr::SCENE_ID::ENCOUNTER);
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_E))
	{
		Test::GetInstance().Init();
		CSceneMgr::GetInstance()->ChangeScene(CSceneMgr::SCENE_ID::TEST);
	}*/
}

void CTitle::Dispose()
{
	//title.UnInit();
	DX11Uninit();
}
