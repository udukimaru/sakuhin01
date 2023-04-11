#pragma once
#include "Command_Base.h"

class CMyMonster : public Command_Base
{
	enum class MY_MONSTER {
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

	using MonsterDataList = UIData<MY_MONSTER>;
	Quad2D monster[(int)MY_MONSTER::MAX];
public:
	// 手持ちモンスター
	std::vector<MonsterDataList> g_monsterlist = {
		{MY_MONSTER::BACK,"assets/UI/もどる_onoff.png",1120, 570,180,120,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 570}},
		{MY_MONSTER::BACK_SHADOW,"assets/UI/立体影_もどる2.png",1107, 580,180,120,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{1107, 580}},
		{MY_MONSTER::MONSTER_DATA_FRAME,"assets/UI/Battle/Command/Monster/枠_icon.png",180, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{180, 140}},
		{MY_MONSTER::MONSTER_DATA1,"assets/UI/Battle/Command/Monster/icon.png",180, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{180, 140}},
		{MY_MONSTER::MONSTER_DATA2,"assets/UI/Battle/Command/Monster/icon.png",360, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{360, 140}},
		{MY_MONSTER::MONSTER_DATA3,"assets/UI/Battle/Command/Monster/icon.png",540, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{540, 140}},
		{MY_MONSTER::MONSTER_DATA4,"assets/UI/Battle/Command/Monster/icon.png",720, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{720, 140}},
		{MY_MONSTER::MONSTER_DATA5,"assets/UI/Battle/Command/Monster/icon.png",900, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{900, 140}},
		{MY_MONSTER::MONSTER_DATA6,"assets/UI/Battle/Command/Monster/icon.png",1080, 140,130,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{1080, 140}},
		{MY_MONSTER::MONSTER_WINDOW,"assets/UI/Battle/Command/Monster/monster_window_basever2.png",640,360,1360,800,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{640,360}},
		{MY_MONSTER::NONE,"assets/UI/Battle/Command/Monster/none.png",640,360,1360,800,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},0,false,false,{640,360}},
	};
	bool Init();        // 初期化
	void Update();      // 更新処理
	void Draw();        // 描画
	void Finalize();    // 終了処理

	void IsUIActive(bool active)
	{
		for (int i = 0; i < g_monsterlist.size(); i++)
		{
			if (active == true)g_monsterlist[i].active = true;
			else g_monsterlist[i].active = false;
		}
	}

	// 初期位置にもどす
	void SetStartMonsterSize();
};

