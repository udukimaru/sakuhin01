#pragma once
#include <vector>
#include "quad2d.h"
#include "CCollider.h"
#include "CDirectInput.h"
class CCommand
{
public:

	enum class COMMAND_ID {
		NONE,
		BATTLE,
		MONSTER,
		BAG,
		EXIT,
		SHADOW,
		MAX
	};

	enum class COMMAND_SKILL {
		NONE,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		ATTACK,
		SPECIAL,
		BACK,
		SHADOW1,
		SHADOW2,
		BACK_SHADOW,
		MAX
	};

	enum class COMMAND_MONSTER {
		NONE,
		MONSTER_WINDOW,
		MONSTER_DATA1,
		MONSTER_DATA2,
		MONSTER_DATA3,
		MONSTER_DATA4,
		MONSTER_DATA5,
		MONSTER_DATA6,
		MONSTER_DATA_FRAME,
		BACK,
		BACK_SHADOW,
		MAX,
	};

	enum class COMMAND_BAG {
		NONE,
		BAG_WINDOW,
		BAG_DATA,
		BACK,
		BACK_SHADOW,
		MAX,
	};

	enum class COMMAND_FINISH {
		NONE,
		SELECT_YES,
		SELECT_NO,
		MAX,
	};

	//BUTTON_SWITCH button_switch;

	template<typename T>
	struct UIData
	{
		T id;
		const char* texfolder;
		float x;
		float y;
		float width;
		float height;
		DirectX::XMFLOAT2 size;
		DirectX::XMFLOAT4 color = { 1,1,1,1 };
		bool active;
		XMFLOAT2 uv_off[4];
		XMFLOAT2 uv_on[4];
		float t;
		bool on_off;
		bool wait;
	};
	using ButtunDataList = UIData<COMMAND_ID>;
	using SkillDataList = UIData<COMMAND_SKILL>;
	using MonsterDataList = UIData<COMMAND_MONSTER>;
	using BagDataList = UIData<COMMAND_BAG>;
	using FinSelectDataList = UIData<COMMAND_FINISH>;


	COMMAND_ID current_buttun = COMMAND_ID::NONE;
	COMMAND_ID ChangeCommand(COMMAND_ID id);

	// UV�܂Ƃ߁@�@�����ƊȒP�ɂ�����
	XMFLOAT2 uv2D[4] = {
	{0.0f,0.0f},
	{1.0f,0.0f},
	{0.0f,1.0f},
	{1.0f,1.0f}
	};
	/// <summary>
	/// ////////////////////////////////
	/// </summary>
	XMFLOAT2 uv[4] = {
			{0.0f,0.0f},
			{1.0f / 2,0.0f},
			{0.0f,1.0f},
			{1.0f / 2,1.0f}
	};
	XMFLOAT2 uv0[4] = {
			{1.0f / 2,0.0f},
			{1.0f,0.0f},
			{1.0f / 2,1.0f},
			{1.0f,1.0f}
	};
	/////////////////////////////////
	XMFLOAT2 uv1[4] = {
		{0.25f,0.0f},
		{2.0f / 4.0f,0.0f},
		{0.25f,1.0f / 2},
		{2.0f / 4.0f,1.0f / 2},
	};

	XMFLOAT2 uv2[4] = {
		{0.75f,0.05f},
		{1.0f,0.05f},
		{0.75f ,1.05f / 2},
		{1.0f,1.05f / 2},
	};

	XMFLOAT2 uv3[4] = {
		{0.75f , 0.45f},
		{1.0f,0.45f },
		{0.75f ,0.95f},
		{1.0f ,0.95f},
	};
	XMFLOAT2 uv4[4] = {
		{0.25f , 1.0f / 2},
		{1.0f / 2 ,1.0f / 2 },
		{0.25f  ,1.0f},
		{1.0f / 2 ,1.0f},
	};

	std::vector<ButtunDataList> g_buttunlist = {
		// �s���R�}���h
		{COMMAND_ID::BATTLE,"assets/UI/Battle/Command/�{�^��UI2.png",0,390,220,120,{1,1}, {1,1,1,1},false,
		{{0.0f,0.0f},{1.0f / 4.0f,0.0f},{0.0f / 4.0f,1.0f / 2},{1.0f / 4.0f,1.0f / 2}},{uv1[0],uv1[1],uv1[2],uv1[3]},0,false,false},
		{COMMAND_ID::MONSTER,"assets/UI/Battle/Command/�{�^��UI2.png",0, 490,220,120,{1,1}, {1,1,1,1},false,
		{{1.0f / 2.0f , 0.05f},{1.0f / 1.33f,0.05f },{1.0f / 2.0f ,1.05f / 2.0f},{1.0f / 1.33f ,1.05f / 2.0f}},{uv2[0],uv2[1],uv2[2],uv2[3]},0,false,false},
		{COMMAND_ID::BAG,"assets/UI/Battle/Command/�{�^��UI2.png",0, 570,220,120,{1,1}, {1,1,1,1},false,
		{{1.0f / 2.0f,0.45f},{1.0f / 1.33f ,0.45f},{1.0f / 2.0f ,0.95f},{1.0f / 1.33f ,0.95f}},{uv3[0],uv3[1],uv3[2],uv3[3]},0,false,false},
		{COMMAND_ID::EXIT,"assets/UI/Battle/Command/�{�^��UI2.png",0, 670,220,120,{1,1}, {1,1,1,1},false,
		{{0.0f , 1.0f / 2},{1.0f / 4 ,1.0f / 2 },{0.0f  ,1.0f},{1.0f / 4 ,1.0f}},{uv4[0],uv4[1],uv4[2],uv4[3]},0,false,false},
		{COMMAND_ID::SHADOW,"assets/UI/Battle/Command/���̉e_�{�^��UI.png",1120, 650,220,120,{1,1}, {1,1,1,1},false,
		{{0.0f , 1.0f / 2},{1.0f / 4 ,1.0f / 2 },{0.0f  ,1.0f},{1.0f / 4 ,1.0f}},{uv4[0],uv4[1],uv4[2],uv4[3]},0,false,false},
	};
	// �Z
	std::vector<SkillDataList> g_skilllist = {
		{COMMAND_SKILL::ATTACK,"assets/UI/Battle/Command/Skill/�Z1.png",1120, 390,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false},
		{COMMAND_SKILL::SPECIAL,"assets/UI/Battle/Command/Skill/�K�E�Z1.png",1120, 490,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false},
		{COMMAND_SKILL::BACK,"assets/UI/���ǂ�_onoff.png",1120, 670,120,80,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false},
		{COMMAND_SKILL::SHADOW1,"assets/UI/Battle/Command/Skill/���̉e_�Z.png",1120, 650,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false},
		{COMMAND_SKILL::SHADOW2,"assets/UI/Battle/Command/Skill/���̉e_�K�E�Z.png",1120, 650,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false},
		{COMMAND_SKILL::BACK_SHADOW,"assets/UI/���̉e_���ǂ�2.png",1107, 660,120,80,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
	};
	// �莝�������X�^�[
	std::vector<MonsterDataList> g_monsterlist = {
		{COMMAND_MONSTER::BACK,"assets/UI/���ǂ�_onoff.png",1120, 570,180,120,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false},
		{COMMAND_MONSTER::BACK_SHADOW,"assets/UI/���̉e_���ǂ�2.png",1107, 580,180,120,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA_FRAME,"assets/UI/Battle/Command/Monster/�g_icon.png",180, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA1,"assets/UI/Battle/Command/Monster/icon.png",180, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA2,"assets/UI/Battle/Command/Monster/icon.png",360, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA3,"assets/UI/Battle/Command/Monster/icon.png",540, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA4,"assets/UI/Battle/Command/Monster/icon.png",720, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA5,"assets/UI/Battle/Command/Monster/icon.png",900, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_DATA6,"assets/UI/Battle/Command/Monster/icon.png",1080, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
		{COMMAND_MONSTER::MONSTER_WINDOW,"assets/UI/Battle/Command/Monster/monster_window_base.png",640,360,1360,800,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false,false},
	};
	// �o�b�O
	std::vector<BagDataList> g_baglist = {
		{COMMAND_BAG::BACK,"assets/UI/���ǂ�_onoff.png",1120, 570,180,120,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false},
		{COMMAND_BAG::BACK_SHADOW,"assets/UI/���̉e_���ǂ�2.png",1107, 580,180,120,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
		{COMMAND_BAG::BAG_DATA,"assets/UI/Battle/Command/Bag/bag_bar.png",360, 160,560,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
		{COMMAND_BAG::BAG_WINDOW,"assets/UI/Battle/Command/Bag/bag_window_base.png",640,380,1360,780,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
	};

	// ������̑I����
	std::vector<FinSelectDataList> g_finishlist = {
		{COMMAND_FINISH::SELECT_YES,"assets/UI/Battle/Command/Finish/�͂�.png",420, 360,300,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false},
		{COMMAND_FINISH::SELECT_NO,"assets/UI/Battle/Command/Finish/������.png",760, 360,300,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false},
	};

	bool InitButton();	// ������
	//void DrawCommandID(std::vector<ButtunDataList> battle);

	void DrawButton();  // 2D�`�揈��

	template<typename T>
	void DrawUI(std::vector<T>& list) {

	}
	//void DrawShadow(float y);

	void Update();	// �X�V����
	void SelectUpdate();// �Ō�̎���X�V����

	template<typename T>
	int CheckOnOff(std::vector<T>& list) {
		// �J�[�\���ʒu�擾
		XMFLOAT2 cursor_pos = {};
		cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
		cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();


		for (int i = 0; i < list.size(); i++)
		{
			XMFLOAT2 pos = { list[i].x,list[i].y };
			if (CCollider::Col(pos, list[i].width, list[i].height, cursor_pos) && list[i].active == true && list[i].wait == true && list[i].x <= list[i].x + 10)
			{
				//OnOff(list);
				list[i].on_off = true;

				if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
				{
					//SetStartSkillPos();
					//list[i].active = false;

					return i;
				}
			}
			else
			{
				list[i].on_off = false;
			}
		}
	}
	// UI��\�����邩���Ȃ���
	template<typename T>
	void IsActive(std::vector<T>& list,bool is) 
	{
		for (int i = 0; i < list.size(); i++) {
			list[i].active = is;
		}
	}

	bool OnOff(std::vector<ButtunDataList> list);


	// �����ʒu�ɂ��ǂ�
	template<typename T>
	void SetStartPos(std::vector<T>& list)
	{
		for (int i = 0; i < list.size(); i++)
		{
			list[i].t = 0.0f;
			list[i].x = 0.0f;
		}
	}
	// �����T�C�Y�ɂ��ǂ�
	template<typename T>
	void SetStartFade(std::vector<T>& list)
	{
		for (int i = 0; i < list.size(); i++)
		{
			list[i].size.x = 0.0f;
			list[i].size.y = 0.0f;
			list[i].color.w = 0.0f;
		}
	}
	//// �����ʒu�ɂ��ǂ�
	//void SetStartPos();
	//// �����ʒu�ɂ��ǂ�
	//void SetStartSkillPos();
	// �����ʒu�ɂ��ǂ�
	void SetStartMonsterSize();

	//std::vector<Quad2D*> m_ui;
	XMFLOAT2 SetUV();
	void SetSadowPos(float y);
	XMFLOAT2 SetPositionUI(float x,float y);

	static CCommand* GetInstance() {
		static CCommand Instance;
		return &Instance;
	}
   /* float BattleaPos[(int)COMMAND_ID::MAX-1] = { 0.0f };*/
	//float SkillPos[(int)COMMAND_SKILL::MAX - 1] = { 0.0f };
private:
	//bool active;
	
	//XMFLOAT2 MonsterWindowSize = {0,0};
	//XMFLOAT2 MonsterWindowPos = { g_monsterlist[2].x,g_monsterlist[2].y };
	//float monster_color = 0.0f;
	//float monster_icon_y;


	void UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4]);
};

