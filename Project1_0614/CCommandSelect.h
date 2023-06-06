#pragma once
#include "Command_Base.h"
class CCommandSelect :
    public Command_Base
{
	enum class COMMAND_ID {
		NONE,
		BATTLE,
		MONSTER,
		BAG,
		EXIT,
		BATTLE_SHADOW,
		MONSTER_SHADOW,
		BAG_SHADOW,
		EXIT_SHADOW,
		MAX
	};
	enum class STATE {
		MOVE,
		NOMAL,
	};
	STATE state = STATE::MOVE;
	using ButtunDataList = UIData<COMMAND_ID>;
	Quad2D sp[(int)COMMAND_ID::MAX];

	bool isupdate = false;

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
public:
	std::vector<ButtunDataList> g_buttunlist = {
		// 行動コマンド
		{COMMAND_ID::BATTLE,"assets/UI/Battle/Command/たたかう.png",1120,390,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120,390}},
		{COMMAND_ID::MONSTER,"assets/UI/Battle/Command/モンスター.png",1120, 480,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 480}},
		{COMMAND_ID::BAG,"assets/UI/Battle/Command/もちもの.png",1120, 570,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 570}},
		{COMMAND_ID::EXIT,"assets/UI/Battle/Command/にげる.png",1120, 660,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 660}},
		{COMMAND_ID::BATTLE_SHADOW,"assets/UI/Battle/Command/たたかう_影.png",1120,390,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 390}},
		{COMMAND_ID::MONSTER_SHADOW,"assets/UI/Battle/Command/モンスター_影.png",1120, 480,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 480}},
		{COMMAND_ID::BAG_SHADOW,"assets/UI/Battle/Command/もちもの_影.png",1120, 570,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 570}},
		{COMMAND_ID::EXIT_SHADOW,"assets/UI/Battle/Command/にげる_影.png",1120, 660,200,90,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false,false,{1120, 660}},

	};
	bool Init();        // 初期化
	void Update();      // 更新処理
	void Draw();        // 描画
	void Finalize();    // 終了処理

	void IsUIActive(bool active)
	{
		for (int i = 0; i < g_buttunlist.size(); i++)
		{
			if (active == true)g_buttunlist[i].active = true;
			else g_buttunlist[i].active = false;
		}
	}

	void SetStartPos()
	{
		for (int i = 0; i < g_buttunlist.size(); i++)
		{
			g_buttunlist[i].t = 0.0f;
			g_buttunlist[i].x = 1500.0f;
			g_buttunlist[i].y = g_buttunlist[i].fixedPos.y;
			state = STATE::MOVE;
		}
	}

private:

};

