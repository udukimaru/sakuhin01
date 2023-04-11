#include "Encounter.h"
#include "M_Plain.h"
#include "CSkydome.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "DX11util.h"
#include "CBillBoard.h"
#include "Stage.h"
#include <vector>
#include "CCollider.h"
#include "CSceneMgr.h"
#include "Battle.h"

//#include "AnimatedHero.h"

M_Plain m_monster;
//AnimatedHero plain;
//CStage   m_stage;
CSkydome  m_skydome;
CPlayer m_player;
//CBall m_ball;

CBillBoard g_billboard[15];

Stage g_stage;

//SceneManager	manager;
//enum class GAMESTATUS {
//	MOTIONEDIT = 0,
//	MOTIONPLAY
//};
//GAMESTATUS	g_mode = GAMESTATUS::MOTIONEDIT;		// ゲームステータス


Encounter::Encounter()
{
}

Encounter::~Encounter()
{
}

void Encounter::Init()
{
	// カメラが必要
	DirectX::XMFLOAT3 eye(0, 25, 20);	// カメラの位置
	DirectX::XMFLOAT3 lookat(0, 0, 0);		// 注視点
	DirectX::XMFLOAT3 up(0, 1, 0);			// カメラの上向きベクトル

	CCamera::GetInstance()->Init(
		10.0f,							// ニアクリップ
		1000.0f,						// ファークリップ
		XM_PI / 5.0f,					// 視野角
		static_cast<float>(15),		// スクリーン幅
		static_cast<float>(10),		// スクリーンの高さ
		eye, lookat, up);

	eye = { 0, 20, -20 };
	lookat = m_player.GetPos();
	CCamera::GetInstance()->SetEye(eye);
	CCamera::GetInstance()->SetLookat(lookat);
	CCamera::GetInstance()->CreateCameraMatrix();
	CCamera::GetInstance()->CreateProjectionMatrix();


	//m_stage.Init();
	m_player.Init();
	m_monster.Init();
	for (int i = 0; i < 15; i++) {
		g_billboard[i].Init(0.0f, 0.0f, 0.0f, 15, 15, XMFLOAT4(0, 1, 0, 1));

		XMFLOAT2 uv[4] = {
			{0.0f,0.0f},
			{1.0f,0.0f},
			{0.0f,1.0f},
			{1.0f,1.0f}
		};

		g_billboard[i].SetUV(uv);
		g_billboard[i].LoadTexTure("assets/Grass/Grass.png");

	}
	g_stage.Init();
	m_skydome.Init();
}

void Encounter::Input()
{
}

void Encounter::Dispose()
{
	//m_stage.Finalize();
	m_player.Finalize();
	m_monster.Finalize();
	//m_ball.Finalize();
	g_stage.Finalize();
	m_skydome.Finalize();
}

void Encounter::Update()
{

	XMFLOAT3 lightpos = CCamera::GetInstance()->GetEye();

	//平行光源をセット
	DX11LightInit(
		DirectX::XMFLOAT4(lightpos.x, lightpos.y, lightpos.z, 0));

	XMFLOAT3 eye = DirectX::XMFLOAT3(0, 20, 5);
	XMFLOAT3 ground = { 0,-30,0 };
	/*if (eye.y < ground.y)
	{
		eye.y = ground.y;
	}*/
	m_player.Update();
	m_monster.Update();

	//CCamera::GetInstance()->SetEye(eye);
	/*CCamera::GetInstance()->CameraMoveUpdate();
	CCamera::GetInstance()->CreateProjectionMatrix();
	CCamera::GetInstance()->CreateCameraMatrix();*/
	// プロジェクション変換行列セット
	XMFLOAT4X4 prjmtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, prjmtx);

	//XMFLOAT4X4 vpmtx;
	//DX11MtxMultiply(vpmtx, m_monster.GetMtx(), prjmtx);

	//XMFLOAT3 pos = m_monster.GetPos();
	//bool sts = IsInFrustum(pos, vpmtx);
	//m_monster.SetInFrustumn(sts);
	//if (sts) {
	//	//g_enemy[i].Draw();
	//	printf("a");
	//}
	//XMFLOAT3 pos = { m_monster.GetLocalPoseMtx()->_41,m_monster.GetLocalPoseMtx()->_42,m_monster.GetLocalPoseMtx()->_43 };
	// 生きているときだけ当たり判定
	if (m_monster.IsActive() == true) {
		bool res = CCollider::Test(m_player.GetPos(), m_monster.GetPos());

		if (res == true)
		{
			change = true;
			//manager.changeScene<Battle>("Ending", 1000, false);
			/*XMFLOAT3 eye(0, 20, -25);

			CCamera::GetInstance()->SetEye(eye);
			CCamera::GetInstance()->CreateCameraMatrix();
			CCamera::GetInstance()->CreateProjectionMatrix();*/
			//printf("エンカウント");
			/*CSceneMgr::GetInstance()->ChangeScene(CSceneMgr::SCENE_ID::BATTLE);
			Battle::GetInstance().Init();*/
		}
	}

	//TPSCamera();
}

void Encounter::Draw()
{
	m_skydome.Draw();
	g_stage.Draw();

	for (int i = 0; i < 8; i++)
	{
		for(int j = 0;j < 8;j++)
		{
			g_billboard[i].SetPosition(-5 + i * 5, 6.5f, -5 + j * 5);
			g_billboard[i].DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
		}
	}
	m_player.Draw();
	m_monster.Draw();
	//m_ball.Draw();

}
