#include <random> 
#include <iostream>
#include <set>
#include "Battle.h"
#include "M_Plain.h"
#include "M_Dog.h"
#include "CSkydome.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "quad2d.h"
#include "CCollider.h"
#include "CDirectInput.h"
#include "Stage.h"
#include "CCreateString.h"
#include "CCommand.h"
#include "CSceneMgr.h"
#include "CMonsterMgr.h"
#include "ModelMgr.h"
#include "CBattleUI.h"
#include "Easing.h"
#include "CMyMonster.h"
#include "Encounter.h"

#include "Command_Base.h"
#include "CCommandSelect.h"
#include "CSkill.h"
#include "CMyMonster.h"
#include "CBag.h"

CMonsterMgr* m_monsters;

CPlayer g_player;
M_Plain g_plain;
M_Dog g_monster2;
CSkydome g_skydome;
Stage stage;

CCreateString* write;
CCreateString* monsterSta;

//Command_Base* command; 

/// 
/// commandselect��IsUIActive�͂ł���
/// ���Fg_ui�����ƃ}�E�X�J�[�\������ł��񂩂�ǂ����邩
/// 
CCommandSelect* cselect;
CSkill* cskill;
CMyMonster* cmonster;
CBag* cbag;

CCommand g_ui;
CBattleUI battle_ui;

//SceneManager b_SceneMgr;

bool drawhp = false;
bool drawhpdog = false;

int plain_damage;
int dog_damage;


bool nakaminisuru = false;

typedef struct Text_Data
{
	std::string text;
	bool text_active;
	XMFLOAT2 pos;
	float t;
};

std::vector<Text_Data> textbox = {
	{"���Ƃт����Ă����I",false,{330, 590},0},
	{"�����I�C�b�k�I",false,{200, 650},0},
	{"�Ȃɂ������Ă��Ȃ��I",false,{200, 590},0},
	{"�_���[�W�^�����I",false, {260, 590},0 },
	{"�C�b�k�̂���������I",false, {200, 590},0},
	{"�������� ? ",false, {200, 590},0},
	{"�v���C���̂���������I",false, {200, 590},0},
	{"���Ԃɂ��܂����H",false, {200, 590},0},
};

//bool turn_cnt1 = false;
//bool turn_cnt2 = false;



//bool is_select = false;

//TURN_ID ChangeTurn(TURN_ID id)
//{
//	current_turn = id;
//	return current_turn;
//}


// �e�L�X�g���ꊇ����
void TextClear()
{
	cselect->IsUIActive(false);
	/*for (int i = 0; i < g_ui.g_buttunlist.size(); i++)
	{
		g_ui.g_buttunlist[i].active = false;
	}
	for (int j = 0; j < g_ui.g_skilllist.size(); j++)
	{
		g_ui.g_skilllist[j].active = false;
	}*/
	for (int k = 0; k < textbox.size(); k++)
	{
		textbox[k].text_active = false;
	}
}


void ShowString(std::string message)
{
	int cnt = 0;
	clock_t start = 0, end = 0;
	start = clock();
	while (cnt < (int)message.size())
	{
		if (((end - start)) >= 70)
		{
			std::cout << message[cnt] << std::endl;
			//write->DrawString(message, XMFLOAT2(330, 580), D2D1_DRAW_TEXT_OPTIONS_NONE);
			cnt++;
			start = end;
		}
		end = clock();
	}
}

void test(CCommand* com)
{
	CCommand* command = com;
	command->g_baglist[0].active = true;
}

void DrawHP()
{
	//plain_damage = DamageDraw();// ���Ԃ񂱂ꂪ����
	plain_damage--;
	if (plain_damage > 0&& drawhp == true) {
		g_plain.HP -= 1.0f;
		battle_ui.uilist[3].size.x = 1.0f * (g_plain.HP / g_plain.GetMAXHP());
		battle_ui.uilist[3].x = battle_ui.uilist[3].x - (1.0f+0.1f);
		printf("�GHP%f\n", g_plain.HP);
	}
	else
	{
		drawhp = false;
	}
}
void DrawHPDog()
{
	dog_damage--;
	if (dog_damage > 0 && drawhpdog == true) {
		g_monster2.HP -= 1.0f;
		battle_ui.uilist[1].size.x = 1.0f * (g_monster2.HP / g_monster2.GetMAXHP());
		battle_ui.uilist[1].x= battle_ui.uilist[1].x - (1.0f + 0.1f);
		printf("�GHP%f\n", g_monster2.HP);
	}
	else
	{
		drawhpdog = false;
	}
}

void Battle::TurnAction()
{
	m_TextKeepTime++;
	if (m_TextKeepTime >= 0&& m_TextKeepTime <= 50)
	{
		textbox[4].text_active = true;
	}
	if (m_TextKeepTime >= 51 && m_TextKeepTime <= 60)
	{
		// �U�����[�V�����J�n
		g_monster2.BattleUpdate();
		printf("motion");
	}
	if (m_TextKeepTime >= 61&&m_TextKeepTime<=62)
	{
		g_monster2.SetPos({ g_monster2.GetPos().x,g_monster2.GetPos().y,-5 });
		TextClear();
		drawhp = true;
		plain_damage = g_monster2.AttackDamage();
	}
	// ���[�V�����I���ΑJ��
	if (m_TextKeepTime >= 120 && m_TextKeepTime <= 140)
	{
		textbox[3].text_active = true;
	}
	if (m_TextKeepTime >= 200)
	{
		TextClear();
		current_turn = TURN_ID::MY_TURN_END;
		m_TextKeepTime = 0;
	}
}

void Battle::EnemyTurnBattle()
{
	TextClear();
	if (m_TextKeepTime >= 0 && m_TextKeepTime <= 180)
	{
		//printf("tekinokougeki\n");
		textbox[6].text_active = true;
	}
	if (++m_TextKeepTime >= 200 && m_TextKeepTime <= 249)
	{
		///////////////////////////////////////////////
		// �U�����[�V�����J�n
		g_plain.BattleUpdate();
		printf("motion");
	    //////////////////////////////////////////////
	}
	if (++m_TextKeepTime >= 252 && m_TextKeepTime <= 253)
	{
		g_plain.SetPos({ g_plain.GetPos().x,g_plain.GetPos().y,10 });
		TextClear();

		drawhpdog = true;

		dog_damage = g_plain.AttackDamage();

	}
	if (++m_TextKeepTime >= 255 && m_TextKeepTime <= 257)
	{

	}
	// ���[�V�����I���ΑJ��
	if (++m_TextKeepTime >= 500 && m_TextKeepTime <= 700)
	{
		textbox[3].text_active = true;
	}
	
	if (++m_TextKeepTime >= 1000)
	{
		TextClear();
		ChangeTurn(TURN_ID::ENEMY_TURN_END);
		m_TextKeepTime = 0;

	}

}
void Battle::Init()
{
	m_TextKeepTime = 0;
	current_turn = TURN_ID::START;

	/*command = new Command_Base();
	command->Init();*/

	cselect = new CCommandSelect();
	cselect->Init();

	cskill = new CSkill;
	cskill->Init();

	cmonster = new CMyMonster;
	cmonster->Init();

	cbag = new CBag;
	cbag->Init();


	g_plain.Init();
	g_monster2.Init();
	g_skydome.Init();
	stage.Init();


	//g_ui.InitButton();
	battle_ui.Init();
	
	// �����`��
	FontData* data = new FontData();
	data->fontSize = 30;
	data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;

	write = new CCreateString(data);
	write->Init();


	// �����`��
	FontData* data2 = new FontData();
	data2->fontSize = 20;
	data2->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	data2->Color = { 1,1,1,1 };
	monsterSta = new CCreateString(data2);
	monsterSta->Init();
	// IMGUI������
	//imguiInit();
	//b_SceneMgr.add<Encounter>("Encount");
}

void Battle::Input()
{
	CDirectInput::GetInstance().GetKeyBuffer();
	CDirectInput::GetInstance().GetMouseState();
}

void Battle::Draw()
{
	//auto command = CCommand::GetInstance();

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

	//command->Draw();
	cselect->Draw();
	cskill->Draw();
	cmonster->Draw();
	cbag->Draw();


	if (g_plain.IsActive() == true) {
		g_plain.Draw();
	}
	g_monster2.Draw();
	g_skydome.Draw();
	stage.Draw();

	//g_ui.DrawButton();
	battle_ui.Draw();
	
		//char name[20] = "�v���C��";
	if (textbox[0].text_active == true) {
		
		write->DrawString("�v���C��", XMFLOAT2(200, textbox[0].pos.y), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}

	for (int i = 0; i < textbox.size(); i++)
	{
		if (textbox[i].text_active == true)
		{
			write->DrawString(textbox[i].text, textbox[i].pos, D2D1_DRAW_TEXT_OPTIONS_NONE);
		}
	}
	if (battle_ui.uilist[3].active == true) {
		monsterSta->DrawString(("Lv. 5"), XMFLOAT2(1060, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);
		monsterSta->DrawString(("�v���C��"), XMFLOAT2(1120, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
	if (battle_ui.uilist[1].active == true) {
		monsterSta->DrawString(("Lv. 5"), XMFLOAT2(100, 400), D2D1_DRAW_TEXT_OPTIONS_NONE);
		monsterSta->DrawString(("�C�b�k"), XMFLOAT2(160, 400), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
	//imguiDraw(imguidebug);
	// �`��㏈��
	DX11AfterRender();
}

// �X�V����
void Battle::Update()
{
	XMFLOAT3 eye{};
	XMFLOAT3 lookat{};

	auto command = CCommand::GetInstance();
	//g_monster->Update();

	CCamera::GetInstance()->CameraMoveUpdate();
	//�����Ă���Ƃ������A�b�v�f�[�g
	if (g_plain.IsActive() == true) {
		g_plain.MosionUpdate();
	}
	g_monster2.Update();

	// �J�[�\���ʒu�擾
	XMFLOAT2 cursor_pos = {};
	cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
	cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();


	bool keyinput = CDirectInput::GetInstance().GetMouseLButtonCheck();
	keyinput = false;

	command->Update();
	battle_ui.Update();
	//CCamera::GetInstance()->AutoCameraUpdate();

	for (int i = 0; i < textbox.size(); i++) {
		if (textbox[i].text_active == true) {
			//textbox[i].t -= 0.01f;
			textbox[i].pos.y = textbox[i].pos.y + CEasing::GetInstance().SinVibe(0.5f, 4, battle_ui.uilist[0].t);
		}
	}

	switch (current_turn)
	{
	case TURN_ID::NONE:
		break;
	case TURN_ID::START:
		if (m_TextKeepTime <= 0)
		{
			eye = { 5, 6, -5 };
			//lookat = CCamera::GetInstance()->GetLookat();
			lookat = { 5,5, 10 };

			CCamera::GetInstance()->SetEye(eye);
			CCamera::GetInstance()->SetLookat(lookat);
			CCamera::GetInstance()->CreateCameraMatrix();
			CCamera::GetInstance()->CreateProjectionMatrix();

			textbox[0].text_active = true; // �O�b�ȏ�o�Ă΃e�L�X�g�\��
			for (int i = 1; i < battle_ui.uilist.size(); i++) {
				battle_ui.uilist[i].active = false;
			}
		}
		
		if (++m_TextKeepTime >= 180) {       //180�t���[����
			textbox[0].text_active = false;  //�e�L�X�g��\��
			current_turn = TURN_ID::BATTLE;  //�o�g���J�n
			m_TextKeepTime = 0;
		}
		break;
	case TURN_ID::BATTLE:
		if (m_TextKeepTime <= 0)
		{
			eye={ 15, 6, -18 };
			lookat = { 0,0, 7.5f };

			CCamera::GetInstance()->SetEye(eye);
			CCamera::GetInstance()->SetLookat(lookat);
			CCamera::GetInstance()->CreateCameraMatrix();
			CCamera::GetInstance()->CreateProjectionMatrix();


			for (int i = 0; i < battle_ui.uilist.size(); i++) {
				battle_ui.uilist[i].active = true;
			}
			textbox[5].text_active = true;
			current_turn = TURN_ID::SELLECT;
			m_TextKeepTime = 0;
		}
	case TURN_ID::BATTLE_START:
		// �����Ƀ^�[���o�g���̏���
		
		break;

	case TURN_ID::SELLECT:

		CCamera::GetInstance()->AutoCamera();

		/*g_ui.IsActive(g_ui.g_buttunlist, true);
		g_ui.Update();*/

		cselect->IsUIActive(true);
		cselect->Update();
		textbox[5].text_active = true;

		//cmonster->IsUIActive(true);
		if (cselect->CheckOnOff(cselect->g_buttunlist) == 0)
		{
			// �Z�I����
			current_turn = TURN_ID::COMMAND_SKILL;
			printf("��������\n");
			cskill->SetStartPos();
		}
		//if (g_ui.CheckOnOff(g_ui.g_buttunlist) == 0)
		//{
		//	// �Z�I����
		//	current_turn = TURN_ID::COMMAND_SKILL;
		//	printf("��������\n");
		//	g_ui.SetStartPos(g_ui.g_skilllist);
		//}
		if (cselect->CheckOnOff(cselect->g_buttunlist) == 1)
		{
			// �Z�I����
			current_turn = TURN_ID::MONSTER;
			printf("�����X�^�[\n");
			cmonster->SetStartMonsterSize();
		}
		//if (g_ui.CheckOnOff(g_ui.g_buttunlist) == 1)
		//{
		//	// �����X�^�[��ʂ�
		//	current_turn = TURN_ID::MONSTER;
		//	printf("�����X�^�[\n");
		//	g_ui.SetStartFade(g_ui.g_monsterlist);
		//}
		if (cselect->CheckOnOff(cselect->g_buttunlist) == 2)
		{
			// �Z�I����
			current_turn = TURN_ID::BAG;
			printf("�o�b�O\n");
			cbag->SetStartSize();
			//cmonster->SetStartMonsterSize();
		}
		//if (g_ui.CheckOnOff(g_ui.g_buttunlist) == 2)
		//{
		//	// �o�b�O��ʂ�
		//	current_turn = TURN_ID::BAG;
		//	printf("�o�b�O\n");
		//}
		//if (g_ui.CheckOnOff(g_ui.g_buttunlist) == 3)
		//{
		//	// �ɂ���
		//	current_turn = TURN_ID::EXIT;
		//	printf("�ɂ���\n");
		//}

		break;
	case TURN_ID::COMMAND_SKILL:
		eye = { 15, 6, -18 };
		lookat = { 0,0, 7.5f };
		//���s�������Z�b�g
		DX11LightUpdate(
			DirectX::XMFLOAT4(eye.x, eye.y, eye.z, 0));
		CCamera::GetInstance()->SetEye(eye);
		CCamera::GetInstance()->SetLookat(lookat);
		CCamera::GetInstance()->CreateCameraMatrix();
		CCamera::GetInstance()->CreateProjectionMatrix();

		/*g_ui.IsActive(g_ui.g_buttunlist, false);
		g_ui.IsActive(g_ui.g_skilllist, true);
		g_ui.Update();*/

		cselect->IsUIActive(false);
		cskill->IsUIActive(true);
		cskill->Update();

		//if (m_TextKeepTime <= 0)
		//{

			//m_TextKeepTime = 0;
		//}

		//�킴�P
		if (cskill->CheckOnOff(cskill->g_skilllist) == 0)
		{
			cskill->IsUIActive(false);

			current_turn = TURN_ID::CHHECK_SPEED;
			printf("�킴\n"); 
			cskill->SetStartPos();
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
		}
		/*if (g_ui.CheckOnOff(g_ui.g_skilllist) == 0)
		{
			g_ui.IsActive(g_ui.g_skilllist, false);

			current_turn = TURN_ID::CHHECK_SPEED;
			printf("�킴\n");
			g_ui.SetStartPos(g_ui.g_skilllist);
			for (int i = 0; i < textbox.size(); i++)
		    {
		    	textbox[i].text_active = false;
		    }
		}*/
		//�킴2
		if (cskill->CheckOnOff(cskill->g_skilllist) == 1)
		{
			cskill->IsUIActive(false);

			current_turn = TURN_ID::CHHECK_SPEED;
			printf("�킴\n");
			cskill->SetStartPos();
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
		}
		/*if (g_ui.CheckOnOff(g_ui.g_skilllist) == 1)
		{
			g_ui.IsActive(g_ui.g_skilllist, false);

			current_turn = TURN_ID::CHHECK_SPEED;
			printf("�킴\n");
			g_ui.SetStartPos(g_ui.g_skilllist);
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
		}*/
		//���ǂ�
		if (cskill->CheckOnOff(cskill->g_skilllist) == 2)
		{
			cskill->IsUIActive(false);

			current_turn = TURN_ID::SELLECT;
			printf("���ǂ�\n");
			cskill->SetStartPos();
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[2].text_active = false;
				textbox[5].text_active = true;;
			}
			cselect->SetStartPos();
		}
		/*if (g_ui.CheckOnOff(g_ui.g_skilllist) == 2)
		{
			g_ui.IsActive(g_ui.g_skilllist, false);

			current_turn = TURN_ID::SELLECT;
			printf("���ǂ�\n");
			g_ui.SetStartPos(g_ui.g_skilllist);
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[2].text_active = false;
				textbox[5].text_active = true;;
			}
			g_ui.SetStartPos(g_ui.g_buttunlist);
		}*/

		break;
	case TURN_ID::CHHECK_SPEED:
		//g_ui.IsActive(g_ui.g_skilllist, false);
		cskill->IsUIActive(false);
		if (g_plain.GetSpeed() < g_monster2.GetSpeed())
		{
			current_turn = TURN_ID::MY_TURN;
			//turn_cnt1 = true;
		}
		else
		{
			current_turn = TURN_ID::ENEMY_TURN;
			//turn_cnt2 = true;
		}
		break;
	case TURN_ID::MY_TURN:

		TurnAction();
		if (drawhp == true)
		{
			//battle_ui.HPCal(plain_damage, g_plain.GetMAXHP(), g_plain.HP, battle_ui.uilist, 3, drawhp);
			DrawHP();
			battle_ui.HPVib_Update(battle_ui.uilist,3);
		}
		else
		{
			//battle_ui.enemyHPpos.x = 1150.0f;
			battle_ui.uilist[3].y = 250.0f;
			battle_ui.uilist[3].color.x = 0.0f;
			battle_ui.uilist[3].color.y = 1.0f;
		}
		//DrawHP();
		break;

	case TURN_ID::MY_TURN_END:
		printf("�U������");

		if(g_plain.HP>0) current_turn = TURN_ID::ENEMY_TURN;
		else
		{
			current_turn = TURN_ID::FINISH;
			// ����
			printf("���Ԃɂ��܂����H");
		}
		//�@��YES or NO
		//
		// if ()  YES�Ȃ�莝���ɉ�����
		//{
									  // ��������ɃG���J�E���g�ɖ߂�or���[���h�ς��
		//}
		// NO����������̃e�L�X�g�\�����G���J�E���g�ɖ߂�
		

		break;

	case TURN_ID::ENEMY_TURN:

		// �P�F �`�̂�������
		// �Q�F�v�Z����
		EnemyTurnBattle();
		// �R�FHP����
		if (drawhpdog == true)
		{
			//battle_ui.HPCal(dog_damage, g_monster2.GetMAXHP(), g_monster2.GetHP(), battle_ui.uilist, 1, drawhpdog);
			DrawHPDog();
			battle_ui.HPVib_Update(battle_ui.uilist,1);
		}
		else
		{
			battle_ui.myHPpos.y = 450.0f;
			battle_ui.uilist[1].color.x = 0.0f;
			battle_ui.uilist[1].color.y = 1.0f;
		}
		// �S�F�`�_���[�W�������

		// �T�F�I���
		//ChangeTurn(TURN_ID::ENEMY_TURN_END);
		break;

	case TURN_ID::ENEMY_TURN_END:

		if (g_monster2.HP > 0)
		{
			cselect->SetStartPos();
			//g_ui.SetStartPos(g_ui.g_buttunlist);
			current_turn = TURN_ID::SELLECT;
		}
		else
		{
			current_turn = TURN_ID::FINISH;
			
		}
		//�@��YES or NO
		//
		// if ()  YES�Ȃ�莝���ɉ�����
		//{
		                              // ��������ɃG���J�E���g�ɖ߂�or���[���h�ς��
		//}
		// NO����������̃e�L�X�g�\�����G���J�E���g�ɖ߂�

		break;

	/// <summary>
	///�@�@�@�@�@                            ��������
	/// </summary>
	case TURN_ID::BAG:
		eye = { 15, 6, -18 };
		lookat = { 0,0, 7.5f };
		//���s�������Z�b�g
		DX11LightUpdate(
			DirectX::XMFLOAT4(eye.x, eye.y, eye.z, 0));
		CCamera::GetInstance()->SetEye(eye);
		CCamera::GetInstance()->SetLookat(lookat);
		CCamera::GetInstance()->CreateCameraMatrix();
		CCamera::GetInstance()->CreateProjectionMatrix();

		cselect->IsUIActive(false);
		cbag->IsUIActive(true);
		cbag->Update();
		//g_ui.IsActive(g_ui.g_buttunlist, false);
		//g_ui.IsActive(g_ui.g_baglist, true);

		for (int i = 1; i < battle_ui.uilist.size(); i++) {
			battle_ui.uilist[i].active = false;
		}
		textbox[5].text_active = false;

		cbag->g_baglist[0].wait = true;
		if (cbag->CheckOnOff(cbag->g_baglist) == 0)
		{
			cbag->IsUIActive(false);

			current_turn = TURN_ID::SELLECT;
			printf("���ǂ�\n");
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[2].text_active = false;
				textbox[5].text_active = true;;
			}
			cselect->SetStartPos();
		}


		//XMFLOAT2 bagpos = { g_ui.g_baglist[0].x,g_ui.g_baglist[0].y };
		//// ���ǂ�{�^���������ꂽ��SELECT��
		//if (CCollider::Col(bagpos, 180, 120, cursor_pos) && g_ui.g_baglist[0].active == true)
		//{
		//	g_ui.g_baglist[0].on_off = true;
		//	if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
		//	{
		//		textbox[5].text_active = true;
		//		printf("���ǂ�");
		//		for (int i = 0; i < g_ui.g_baglist.size(); i++)
		//		{
		//			g_ui.g_baglist[i].active = false;
		//		}
		//		for (int i = 1; i < battle_ui.uilist.size(); i++) {
		//			battle_ui.uilist[i].active = true;
		//		}
		//		//batletet = true;
		//		current_turn = TURN_ID::SELLECT;
		//		g_ui.SetStartPos(g_ui.g_buttunlist);
		//	}
		//}
		//else
		//{
		//	g_ui.g_baglist[0].on_off = false;
		//}
		break;
		
	/// <summary>
	///                                         �莝�������X�^�[
	/// </summary>
	case TURN_ID::MONSTER:
		eye = { 15, 6, -18 };
		lookat = { 0,0, 7.5f };
		//���s�������Z�b�g
		DX11LightUpdate(
			DirectX::XMFLOAT4(eye.x, eye.y, eye.z, 0));
		CCamera::GetInstance()->SetEye(eye);
		CCamera::GetInstance()->SetLookat(lookat);
		CCamera::GetInstance()->CreateCameraMatrix();
		CCamera::GetInstance()->CreateProjectionMatrix();

		cselect->IsUIActive(false);
		cmonster->IsUIActive(true);
		cmonster->Update();
		/*g_ui.IsActive(g_ui.g_buttunlist, false);
		g_ui.IsActive(g_ui.g_monsterlist, true);*/

		//g_ui.Update();
			for (int i = 1; i < battle_ui.uilist.size(); i++) {
				battle_ui.uilist[i].active = false;
			}
		//what = false;
		textbox[5].text_active = false;

			//XMFLOAT2 pos = { g_ui.g_monsterlist[0].x,g_ui.g_monsterlist[0].y };

			//g_ui.UpdateColTest(pos.x, pos.y, g_ui.g_monsterlist[0].width, g_ui.g_monsterlist[0].height);



		cmonster->g_monsterlist[0].wait = true;
			// 
			 //���ǂ�{�^���������ꂽ��SELECT��
		if (cmonster->CheckOnOff(cmonster->g_monsterlist) == 0)
		{
			textbox[2].text_active = false;
			textbox[5].text_active = true;
			cmonster->IsUIActive(false);

			for (int i = 1; i < battle_ui.uilist.size(); i++) {
				battle_ui.uilist[i].active = true;
			}
			current_turn = TURN_ID::SELLECT;
			printf("���ǂ�\n");
			cselect->SetStartPos();
		}
			//if (g_ui.CheckOnOff(g_ui.g_monsterlist) == 0)
			//{
			//	textbox[5].text_active = true;;
			//	printf("���ǂ�");
			//	g_ui.IsActive(g_ui.g_monsterlist, false);

			//	for (int i = 1; i < battle_ui.uilist.size(); i++) {
			//		battle_ui.uilist[i].active = true;
			//	}
			//	//batletet = true;
			//	current_turn = TURN_ID::SELLECT;
			//	g_ui.SetStartPos(g_ui.g_buttunlist);
			//}
		
		break;
	case TURN_ID::FINISH:
		// �o�g������UI���I�t�ɂ���
		for (int i = 1; i < battle_ui.uilist.size(); i++)
		{
			battle_ui.uilist[i].active = false;
		}
		// ���Ԃɂ��邩�ǂ����̑I�������o�Ă���
		for (int i = 0; i < g_ui.g_finishlist.size(); i++) {

			g_ui.g_finishlist[i].active = true;
		}
		textbox[7].text_active = true;
		textbox[5].text_active = false;
		// 
		// 
		//�@��YES or NO
		XMFLOAT2 yesPos = { g_ui.g_finishlist[0].x,g_ui.g_finishlist[0] .y};
		XMFLOAT2 noPos = { g_ui.g_finishlist[1].x,g_ui.g_finishlist[1].y };
		// YES
		if (CCollider::Col(yesPos, g_ui.g_finishlist[0].width, g_ui.g_finishlist[0].height, cursor_pos))
		{
			if (g_ui.g_finishlist[0].active == true) {
				g_ui.g_finishlist[0].on_off = true;
				g_ui.SelectUpdate();
				//textbox[5].text_active = false;
				if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
				{
					for (int i = 0; i < textbox.size(); i++)
					{
						textbox[i].text_active = false;
					}
					nakaminisuru = true;
				}
			}
		}
		else
		{
			g_ui.g_finishlist[0].on_off = false;
			g_ui.g_finishlist[0].y = 360;
			g_ui.g_finishlist[0].t = 0.0f;
		}
		// NO
		if (CCollider::Col(noPos, g_ui.g_finishlist[1].width, g_ui.g_finishlist[1].height, cursor_pos) && g_ui.g_finishlist[1].active == true)
		{
			g_ui.g_finishlist[1].on_off = true;
			g_ui.SelectUpdate();
			//textbox[5].text_active = false;

			if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
			{
				for (int i = 0; i < textbox.size(); i++)
				{
					textbox[i].text_active = false;
				}
				nakaminisuru = false;
			}
		}
		else
		{
			g_ui.g_finishlist[1].on_off = false;
			g_ui.g_finishlist[1].y = 360;
			g_ui.g_finishlist[1].t = 0.0f;
		}
		 if (nakaminisuru==true)  //YES�Ȃ�莝���ɉ�����
		{
			 is_finish = true;						  // ��������ɃG���J�E���g�ɖ߂�or���[���h�ς��
		}
		 else // NO����������̃e�L�X�g�\�����G���J�E���g�ɖ߂�
		 {
			// battle_ui.uilist[0].active = true;

			 is_finish = true;
		 }

		// �G���J�E���^�[�ɖ߂�

		break;
	case TURN_ID::EXIT:
		// �G���J�E���^�[�ɖ߂�
		if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
		{
			is_finish = true;
		}
		/*XMFLOAT3 pl_pos = { g_player.GetPos().x,g_player.GetPos().y,g_player.GetPos().z +10};
		g_player.SetPos(pl_pos);*/
		//b_SceneMgr.changeScene<Encounter>("Encount", 2000, false);
		break;
    }

}

void Battle::Dispose()
{
	g_player.Finalize();
	g_plain.Finalize();
	g_monster2.Finalize();
	//M_dog.Finalize();
	//M_Plane.Finalize();
	//g_monster->Finalize();
	g_skydome.Finalize();
	stage.Finalize();
	//g_ball.Finalize();

	//battle_buttun.UnInit();
	write->Release();

	delete cselect;
	delete cskill;
	delete cmonster;
	delete cbag;

	//imguiExit();
	DX11Uninit();
}