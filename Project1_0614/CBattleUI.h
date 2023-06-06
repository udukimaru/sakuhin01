#pragma once
#include "quad2d.h"
#include "Command_Base.h"
class CBattleUI :
	public Command_Base
{
private:
	bool Active;

	float sin_t = 0.0f;
public:

	enum class UI_ID {
		NONE,
		TEXTBASE,
		MYMONSTER_HP,
		ENEMY_HP,
		MYMONSTER_HP_BASE,
		ENEMY_HP_BASE,
		MAX
	};

	using BattleUIDataList = UIData<UI_ID>;
	Quad2D battleui_data[(int)UI_ID::MAX];
	XMFLOAT2 myHPpos = { 50,450 };
	XMFLOAT2 enemyHPpos = { 50,250 };

	std::vector<BattleUIDataList> uilist={
		//  ID                           ƒtƒ@ƒCƒ‹–¼            x    y   width height  size   color  active  uv                      t
		{UI_ID::TEXTBASE,"assets/UI/Battle/WindowUI/text2.png",530, 630, 1080, 360, {1,1}, {1,1,1,1},true,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{530,630}},
		{UI_ID::MYMONSTER_HP,"assets/UI/Battle/WindowUI/HPgauge.png",(200 - myHPpos.x),myHPpos.y,200,60, {1,1},{0,1,0,1},true,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0.0f,false,false,{50,450}},
		{UI_ID::MYMONSTER_HP_BASE,"assets/UI/Battle/WindowUI/HPgaugeBase.png",150,myHPpos.y,200,60, {1,1},{1,1,1,1},true,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0.0f,false,false,{150,450}},
		{UI_ID::ENEMY_HP,"assets/UI/Battle/WindowUI/HPgauge.png",1150,250,200,60, {1,1},{0,1,0,1},true,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0.0f,false,false,{50,250}},
		{UI_ID::ENEMY_HP_BASE,"assets/UI/Battle/WindowUI/HPgaugeBase.png",1150,250,200,60, {1,1},{1,1,1,1},true,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0.0f,false,false,{1150,250}},
	};
	
	void EnemyHPVib_Update();
	void myHPVib_Update();
	void HPVib_Update(std::vector<BattleUIDataList> &list,int i);
	void HBasePVib_Update(std::vector<BattleUIDataList>& list, int i);

	bool Init();
	void Draw();
	void Update();
	//void CreateUI(UI_ID type, float x, float y, float z, float xsize, float ysize, DirectX::XMFLOAT4 color);

	void HPCal(float damage, float maxhp,float hp, std::vector<BattleUIDataList>& list,int i,bool drawhp);

	void IsUIActive(bool active)
	{
		for (int i = 0; i < uilist.size(); i++)
		{
			if (active == true)uilist[i].active = true;
			else uilist[i].active = false;
		}
	}
};

