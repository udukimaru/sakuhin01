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
		SHADOW,
		MAX
	};
	enum class STATE {
		MOVE,
		NOMAL,
	};
	STATE state = STATE::MOVE;
	using ButtunDataList = UIData<COMMAND_ID>;
	Quad2D sp[(int)COMMAND_ID::MAX];

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
		{COMMAND_ID::BATTLE,"assets/UI/Battle/Command/ボタンUI2.png",1120,390,220,120,{1,1}, {1,1,1,1},false,
		{{0.0f,0.0f},{1.0f / 4.0f,0.0f},{0.0f / 4.0f,1.0f / 2},{1.0f / 4.0f,1.0f / 2}},{uv1[0],uv1[1],uv1[2],uv1[3]},0,false,false,{1120,390}},
		{COMMAND_ID::MONSTER,"assets/UI/Battle/Command/ボタンUI2.png",1120, 490,220,120,{1,1}, {1,1,1,1},false,
		{{1.0f / 2.0f , 0.05f},{1.0f / 1.33f,0.05f },{1.0f / 2.0f ,1.05f / 2.0f},{1.0f / 1.33f ,1.05f / 2.0f}},{uv2[0],uv2[1],uv2[2],uv2[3]},0,false,false,{1120, 490}},
		{COMMAND_ID::BAG,"assets/UI/Battle/Command/ボタンUI2.png",1120, 570,220,120,{1,1}, {1,1,1,1},false,
		{{1.0f / 2.0f,0.45f},{1.0f / 1.33f ,0.45f},{1.0f / 2.0f ,0.95f},{1.0f / 1.33f ,0.95f}},{uv3[0],uv3[1],uv3[2],uv3[3]},0,false,false,{1120, 570}},
		{COMMAND_ID::EXIT,"assets/UI/Battle/Command/ボタンUI2.png",1120, 670,220,120,{1,1}, {1,1,1,1},false,
		{{0.0f , 1.0f / 2},{1.0f / 4 ,1.0f / 2 },{0.0f  ,1.0f},{1.0f / 4 ,1.0f}},{uv4[0],uv4[1],uv4[2],uv4[3]},0,false,false,{1120, 670}},
		{COMMAND_ID::SHADOW,"assets/UI/Battle/Command/立体影_ボタンUI.png",1120, 650,220,120,{1,1}, {1,1,1,1},false,
		{{0.0f , 1.0f / 2},{1.0f / 4 ,1.0f / 2 },{0.0f  ,1.0f},{1.0f / 4 ,1.0f}},{uv4[0],uv4[1],uv4[2],uv4[3]},0,false,false,{1120, 650}},
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
			g_buttunlist[i].x = 0.0f;
		}
	}

private:

};

