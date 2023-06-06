#pragma once
#include "Command_Base.h"
class CSkill :
    public Command_Base
{

	bool special;

	bool isupdate = false;

public:
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

	/*enum class STATE {
		MOVE,
		NOMAL,
		NOMALTOMOVE,
	};
	STATE state = STATE:: MOVE;*/
	using SkillDataList = UIData<COMMAND_SKILL>;
	Quad2D skill[(int)COMMAND_SKILL::MAX];
	XMFLOAT2 move[(int)COMMAND_SKILL::MAX];
	// ãZ
	std::vector<SkillDataList> g_skilllist = {
		{COMMAND_SKILL::ATTACK,"assets/UI/Battle/Command/Skill/ãZ1.png",1120, 390,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120,390}},
		{COMMAND_SKILL::SPECIAL,"assets/UI/Battle/Command/Skill/ïKéEãZ1.png",1120, 490,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 490}},
		{COMMAND_SKILL::BACK,"assets/UI/Ç‡Ç«ÇÈ_onoff.png",1120, 670,120,80,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 670}},
		{COMMAND_SKILL::SHADOW1,"assets/UI/Battle/Command/Skill/óßëÃâe_ãZver2.png",1120, 390,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 390}},
		{COMMAND_SKILL::SHADOW2,"assets/UI/Battle/Command/Skill/óßëÃâe_ïKéEãZ1ver2.png",1120, 490,220,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 490}},
		{COMMAND_SKILL::BACK_SHADOW,"assets/UI/óßëÃâe_Ç‡Ç«ÇÈ2.png",1120, 670,120,80,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{1120, 670}},
	};

	bool Init();        // èâä˙âª
	void Update();      // çXêVèàóù
	void Draw();        // ï`âÊ
	void Finalize();    // èIóπèàóù

	void SpecialOn(bool is);
	bool IsSpecial();
	void IsUIActive(bool active)
	{
		for (int i = 0; i < g_skilllist.size(); i++)
		{
			if (active == true)g_skilllist[i].active = true;
			else g_skilllist[i].active = false;
		}
	}
	void SetStartPos()
	{
		for (int i = 0; i < g_skilllist.size(); i++)
		{
			g_skilllist[i].t = 0.0f;
			g_skilllist[i].x = 1500.0f;
			g_skilllist[i].y = g_skilllist[i].fixedPos.y;
		}
	}
	void SetState()
	{
		state = STATE::MOVE;
	}
};
