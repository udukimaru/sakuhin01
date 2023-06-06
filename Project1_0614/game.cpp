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
	// DX11������
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		false);

	// �J�������K�v
	DirectX::XMFLOAT3 eye(0, 20, -10);		// �J�����̈ʒu
	DirectX::XMFLOAT3 lookat(0, 0, 0);		// �����_
	DirectX::XMFLOAT3 up(0, 1, 0);			// �J�����̏�����x�N�g��

	CCamera::GetInstance()->Init(
		10.0f,							// �j�A�N���b�v
		1000.0f,						// �t�@�[�N���b�v
		XM_PI / 5.0f,					// ����p
		static_cast<float>(Application::CLIENT_WIDTH),		// �X�N���[����
		static_cast<float>(Application::CLIENT_HEIGHT),		// �X�N���[���̍���
		eye, lookat, up);					// �J�����̃f�[�^

	CCamera::GetInstance()->CreateProjectionMatrix();
	CCamera::GetInstance()->CreateCameraMatrix();
	// ���s�������Z�b�g
	DX11LightInit(
		DirectX::XMFLOAT4(1, 1, -1, 0));

	// DIRECTINPUT������
	CDirectInput::GetInstance().Init(
		Application::Instance()->GetHInst(),
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,			// �X�N���[����
		Application::CLIENT_HEIGHT			// �X�N���[���̍���
		);

	//// �A���t�@�u�����h�L����
	//TurnOnAlphablend();
	//CSceneMgr::SCENE_ID::TITLE;
	//CSceneMgr::Init();
	// �󒆐평����
	//Encounter::GetInstance().Init();
	//CTitle::GetInstance().Init();
	title.Init();

	// �A���t�@�u�����h�L����
	TurnOnAlphablend();

	/*pl.Init();
	plain.Init();*/
	
	// �V�[���}�l�[�W���Ƀ^�C�g���V�[����o�^
	/*g_manager.add<CTitle>("TitleScene");
	g_manager.add<Encounter>("Encount");
	g_manager.add<Battle>("BattleScene");*/

	// ���݃V�[����GameMain�ɂ���
	//g_manager.setCurrentScene("BattleScene");
}

void GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
	CDirectInput::GetInstance().GetMouseState();
}

void GameUpdate(uint64_t dt) {

	title.Update();
	// �L�[���͂őJ��
	/*if (CDirectInput::GetInstance().GetMouseLButtonTrigger()) {

		if (g_manager.GetCurrentSceneKey() == "TitleScene") {
			g_manager.SetFadeColor(XMFLOAT4(0, 0, 0, 1));
			g_manager.changeScene<Encounter>("Encount", 2000, false);

		}
	}*/
	//// �G�ɓ�����ƃo�g���V�[����
	////�����Ă���Ƃ����������蔻��
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
	//// �^�C�g����ʁ��o�g���V�[��
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

	//// �J�[�\���ʒu�擾
	//XMFLOAT2 cursor_pos = {};
	//cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
	//cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();

	//XMFLOAT2 exitpos = { 1120,com.g_buttunlist[3].y };

	//// �ɂ���J��
	//if (battle.current_turn==Battle::TURN_ID::EXIT)
	//{

	//	//if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
	//	//{
	//       // �J�����g�V�[�����X�V
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

	// �`��O����
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;

	// �v���W�F�N�V�����ϊ��s��擾
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// �r���[�ϊ��s����擾
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);
	// �J�����g�V�[���`��
	//g_manager.Draw();
	// �󒆐�`��
	//Encounter::GetInstance().Draw();
	//CTitle::GetInstance().Draw();
	//CSceneMgr::Render();
	title.Draw();
	// �`��㏈��
	DX11AfterRender();
}

void GameDispose() {

	// �󒆐�I������
	//Encounter::GetInstance().Finalize();
	//CTitle::GetInstance().Finalize();
	//CSceneMgr::Finalize();
	//Battle::GetInstance().Finalize();
	DX11Uninit();
}