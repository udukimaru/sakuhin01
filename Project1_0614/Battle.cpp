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
#include "CSceneMgr.h"
#include "CMonsterMgr.h"
#include "ModelMgr.h"
#include "CBattleUI.h"
#include "Easing.h"
#include "Encounter.h"

#include "Command_Base.h"
#include "CCommandSelect.h"
#include "CSkill.h"
#include "CMyMonster.h"
#include "CBag.h"
#include "CFinishSelect.h"


//CPlayer* g_player;
M_Plain g_plain;
M_Dog g_dog;
CSkydome g_skydome;
Stage stage;

M_Dog* m_dog;
//CMonsterMgr* monsters;

CCreateString* write;
CCreateString* monsterSta;

CCommandSelect* cselect;
CSkill* cskill;
CMyMonster* cmonster;
CBag* cbag;
CFinishSelect* cfinish;

CBattleUI* battle_ui;

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

// �e�L�X�g���ꊇ����
void TextClear()
{
	for (int k = 0; k < textbox.size(); k++)
	{
		textbox[k].text_active = false;
	}
}

void DrawHP_a()
{
	g_plain.MAttackDamage(m_dog);
	plain_damage--;
	if (plain_damage > 0 && drawhp == true) {
		g_plain.HP -= 1.0f;
		battle_ui->uilist[3].size.x = 1.0f * (g_plain.HP / g_plain.GetMAXHP());
		battle_ui->uilist[3].x = battle_ui->uilist[3].x - (1.0f + 0.1f);
		printf("�GHP%f\n", g_plain.HP);
	}
	else
	{
		drawhp = false;
	}
}

void DrawHP()
{
	//g_plain.MAttackDamage(g_dog);
	plain_damage--;
	if (plain_damage > 0&& drawhp == true) {
		g_plain.HP -= 1.0f;
		battle_ui->uilist[3].size.x = 1.0f * (g_plain.HP / g_plain.GetMAXHP());
		battle_ui->uilist[3].x = battle_ui->uilist[3].x - (1.0f+0.1f);
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
		g_dog.HP -= 1.0f;
		battle_ui->uilist[1].size.x = 1.0f * (g_dog.HP / g_dog.GetMAXHP());
		battle_ui->uilist[1].x= battle_ui->uilist[1].x - (1.0f + 0.1f);
		printf("�GHP%f\n", g_dog.HP);
	}
	else
	{
		drawhpdog = false;
	}
}

void Battle::Init()
{
	m_TextKeepTime = 0;
	current_turn = TURN_ID::START;

	// �R�}���h������
	cselect = new CCommandSelect();
	cselect->Init();

	cskill = new CSkill;
	cskill->Init();

	cmonster = new CMyMonster;
	cmonster->Init();

	cbag = new CBag;
	cbag->Init();

	cfinish = new CFinishSelect;
	cfinish->Init();

	battle_ui = new CBattleUI;
	battle_ui->Init();

	g_plain.Init();
	g_dog.Init();
	g_skydome.Init();
	stage.Init();


	is_finish = false;
	//monsters = new CMonsterMgr;
	//monsters->Init();
	
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
}

void Battle::Input()
{
	CDirectInput::GetInstance().GetKeyBuffer();
	CDirectInput::GetInstance().GetMouseState();
}

void Battle::Draw()
{
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
	// �I�u�W�F�N�g�`��
	if (g_plain.IsActive() == true) {
		g_plain.Draw();
	}
	g_dog.Draw();
	g_skydome.Draw();
	stage.Draw();

	// �R�}���h�`��
	cselect->Draw();
	cskill->Draw();
	cmonster->Draw();
	cbag->Draw();
	cfinish->Draw();

	battle_ui->Draw();
	
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
	if (battle_ui->uilist[3].active == true) {
		monsterSta->DrawString(("Lv. 5"), XMFLOAT2(1060, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);
		monsterSta->DrawString(("�v���C��"), XMFLOAT2(1120, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
	if (battle_ui->uilist[1].active == true) {
		monsterSta->DrawString(("Lv. 5"), XMFLOAT2(100, 400), D2D1_DRAW_TEXT_OPTIONS_NONE);
		monsterSta->DrawString(("�C�b�k"), XMFLOAT2(160, 400), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
	// �`��㏈��
	DX11AfterRender();
}

// �X�V����
void Battle::Update()
{
	XMFLOAT3 eye{};
	XMFLOAT3 lookat{};

	CCamera::GetInstance()->CameraMoveUpdate();
	
	g_dog.Update();

	// �J�[�\���ʒu�擾
	XMFLOAT2 cursor_pos = {};
	cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
	cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();


	bool keyinput = CDirectInput::GetInstance().GetMouseLButtonCheck();
	keyinput = false;

	battle_ui->Update();

	for (int i = 0; i < textbox.size(); i++) {
		if (textbox[i].text_active == true) {
			textbox[i].pos.y = textbox[i].pos.y + CEasing::GetInstance().SinVibe(0.5f, 4, battle_ui->uilist[0].t);
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
			lookat = { 5,5, 10 };

			CCamera::GetInstance()->SetEye(eye);
			CCamera::GetInstance()->SetLookat(lookat);
			CCamera::GetInstance()->CreateCameraMatrix();
			CCamera::GetInstance()->CreateProjectionMatrix();

			textbox[0].text_active = true; // �O�b�ȏ�o�Ă΃e�L�X�g�\��
			for (int i = 1; i < battle_ui->uilist.size(); i++) {
				battle_ui->uilist[i].active = false;
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

			battle_ui->IsUIActive(true);
			textbox[5].text_active = true;
			current_turn = TURN_ID::SELLECT;
			m_TextKeepTime = 0;
		}
	case TURN_ID::SELLECT:

		CCamera::GetInstance()->AutoCamera();

		cselect->IsUIActive(true);
		cselect->Update();
		textbox[5].text_active = true;

		if (cselect->CheckOnOff(cselect->g_buttunlist) == 0)
		{
			// �Z�I����
			current_turn = TURN_ID::COMMAND_SKILL;
			printf("��������\n");
			cskill->SetStartPos();
			cskill->SetState();
		}
		if (cselect->CheckOnOff(cselect->g_buttunlist) == 1)
		{
			// �莝�������X�^�[
			current_turn = TURN_ID::MONSTER;
			printf("�����X�^�[\n");
			cmonster->SetStartMonsterSize();
		}
		if (cselect->CheckOnOff(cselect->g_buttunlist) == 2)
		{
			// ���΂�
			current_turn = TURN_ID::BAG;
			printf("�o�b�O\n");
			cbag->SetStartSize();
		}
		if (cselect->CheckOnOff(cselect->g_buttunlist) == 3)
		{
			// �ɂ���
			current_turn = TURN_ID::EXIT;
			printf("�ɂ���\n");
		}

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

		cselect->IsUIActive(false);
		cskill->IsUIActive(true);
		cskill->Update();

		//�킴�P
		if (cskill->CheckOnOff(cskill->g_skilllist) == 0)
		{
			cskill->IsUIActive(false);

			current_turn = TURN_ID::CHHECK_SPEED;
			printf("�킴\n"); 
			cskill->SetStartPos();
			cskill->SpecialOn(false);
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
		}
		//�킴2
		if (cskill->CheckOnOff(cskill->g_skilllist) == 1)
		{
			cskill->IsUIActive(false);

			current_turn = TURN_ID::CHHECK_SPEED;
			printf("�킴\n");
			cskill->SetStartPos();
			cskill->SpecialOn(true);
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
		}
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
		break;

	case TURN_ID::CHHECK_SPEED:
		cskill->IsUIActive(false);
		if (g_plain.GetSpeed() < g_dog.GetSpeed())
		{
			current_turn = TURN_ID::MY_TURN;
		}
		else
		{
			current_turn = TURN_ID::ENEMY_TURN;
		}
		break;
	case TURN_ID::MY_TURN:

		m_TextKeepTime++;
		if (m_TextKeepTime >= 0 && m_TextKeepTime <= 50)
		{
			textbox[4].text_active = true;
		}
		if (m_TextKeepTime >= 51 && m_TextKeepTime <= 60)
		{
			// �U�����[�V�����J�n
			g_dog.BattleUpdate();
			printf("motion");
		}
		if (m_TextKeepTime >= 61 && m_TextKeepTime <= 62)
		{
			g_dog.SetPos({ g_dog.GetPos().x,g_dog.GetPos().y,-5 });
			TextClear();
			drawhp = true;
			// �ʏ�U��or�K�E�Z
			if (cskill->IsSpecial() == false)plain_damage = g_dog.AttackDamage();
			else plain_damage = g_dog.SpecialDamage();
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
		if (drawhp == true)
		{
			DrawHP();
			battle_ui->HPVib_Update(battle_ui->uilist,3);
		}
		else
		{
			battle_ui->uilist[3].y = 250.0f;
			battle_ui->uilist[3].color.x = 0.0f;
			battle_ui->uilist[3].color.y = 1.0f;
		}
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
		break;

	case TURN_ID::ENEMY_TURN:

		TextClear();
		if (m_TextKeepTime >= 0 && m_TextKeepTime <= 180)
		{
			textbox[6].text_active = true;
		}
		if (++m_TextKeepTime >= 200 && m_TextKeepTime <= 249)
		{
			// �U�����[�V�����J�n
			g_plain.BattleUpdate();
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
		// �R�FHP����
		if (drawhpdog == true)
		{
			DrawHPDog();
			battle_ui->HPVib_Update(battle_ui->uilist,1);
		}
		else
		{
			battle_ui->myHPpos.y = 450.0f;
			battle_ui->uilist[1].color.x = 0.0f;
			battle_ui->uilist[1].color.y = 1.0f;
		}
		break;

	case TURN_ID::ENEMY_TURN_END:

		if (g_dog.HP > 0)
		{
			cselect->SetStartPos();
			current_turn = TURN_ID::SELLECT;
		}
		else
		{
			current_turn = TURN_ID::FINISH;
			
		}
		break;

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

		battle_ui->IsUIActive(false);
		textbox[5].text_active = false;

		cmonster->g_monsterlist[0].wait = true;
		//���ǂ�{�^���������ꂽ��SELECT��
		if (cmonster->CheckOnOff(cmonster->g_monsterlist) == 0)
		{
			textbox[2].text_active = false;
			textbox[5].text_active = true;
			cmonster->IsUIActive(false);

			battle_ui->IsUIActive(true);
			current_turn = TURN_ID::SELLECT;
			printf("���ǂ�\n");
			cselect->SetStartPos();
		}
		break;
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
		
		battle_ui->IsUIActive(false);
		textbox[5].text_active = false;

		cbag->g_baglist[0].wait = true;
		// ���ǂ�
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

		break;
		
	case TURN_ID::FINISH:
		// �o�g������UI���I�t�ɂ���
		battle_ui->IsUIActive(false);
		// ���Ԃɂ��邩�ǂ����̑I�������o�Ă���

		cfinish->IsUIActive(true);
		textbox[7].text_active = true;
		textbox[5].text_active = false;

		// YES
		if (cfinish->CheckOnOff(cfinish->g_finishlist) == 0)
		{
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
			nakaminisuru = true;
		}
		else
		{
			cfinish->g_finishlist[0].on_off = false;
			cfinish->g_finishlist[0].y = 360;
			cfinish->g_finishlist[0].t = 0.0f;
		}
		// NO
		if (cfinish->CheckOnOff(cfinish->g_finishlist) == 1)
		{
			for (int i = 0; i < textbox.size(); i++)
			{
				textbox[i].text_active = false;
			}
			nakaminisuru = false;
		}
		else
		{
			cfinish->g_finishlist[1].on_off = false;
			cfinish->g_finishlist[1].y = 360;
			cfinish->g_finishlist[1].t = 0.0f;
		}
		 if (nakaminisuru==true)  //YES�Ȃ�莝���ɉ�����
		{
			 is_finish = true;						  // ��������ɃG���J�E���g�ɖ߂�or���[���h�ς��
		}
		 else // NO����������̃e�L�X�g�\�����G���J�E���g�ɖ߂�
		 {
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
		break;
    }

}

void Battle::Dispose()
{
	//g_player->Finalize();
	g_plain.Finalize();
	g_dog.Finalize();
	g_skydome.Finalize();
	stage.Finalize();

	write->Release();

	delete cselect;
	delete cskill;
	delete cmonster;
	delete cbag;
	delete cfinish;
	delete battle_ui;

	DX11Uninit();
}