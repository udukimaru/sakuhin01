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

	typedef struct UI_List
	{
		UI_ID id;
		const char* texfolder;
		float x;
		float y;
		float width;
		float height;
		XMFLOAT2 size;
		XMFLOAT4 color;
		bool active;
		XMFLOAT2 uv[4];  //uv座標
		float t;         //時間
		XMFLOAT2 aPos;
	};

	XMFLOAT2 uv[4] = {

			{0.0f ,0.0f},
			{1.0f ,0.0f},
			{0.0f ,1.0f},
			{1.0f ,1.0f}
	};

	XMFLOAT2 myHPpos = { 50,450 };
	XMFLOAT2 enemyHPpos = { 50,250 };
	std::vector<UI_List> uilist{
		//  ID                           ファイル名            x    y   width height  size   color  active  uv                      t
		{UI_ID::TEXTBASE,"assets/UI/Battle/WindowUI/text2.png",530, 630, 1080, 360, {1,1}, {1,1,1,1},true,{uv[0],uv[1],uv[2],uv[3]},0.0f},
		{UI_ID::MYMONSTER_HP,"assets/UI/Battle/WindowUI/HPgauge.png",(200 - myHPpos.x),myHPpos.y,200,60, {1,1},{0,1,0,1},true,{uv[0],uv[1],uv[2],uv[3]},0.0f,{50,450}},
		{UI_ID::MYMONSTER_HP_BASE,"assets/UI/Battle/WindowUI/HPgaugeBase.png",150,myHPpos.y,200,60, {1,1},{1,1,1,1},true,{uv[0],uv[1],uv[2],uv[3]},0.0f},
		{UI_ID::ENEMY_HP,"assets/UI/Battle/WindowUI/HPgauge.png",1150,250,200,60, {1,1},{0,1,0,1},true,{uv[0],uv[1],uv[2],uv[3]},0.0f,{50,250}},
		{UI_ID::ENEMY_HP_BASE,"assets/UI/Battle/WindowUI/HPgaugeBase.png",1150,250,200,60, {1,1},{1,1,1,1},true,{uv[0],uv[1],uv[2],uv[3]},0.0f},
	};
	
	std::vector <std::shared_ptr<Quad2D>> list;

	//std::vector<Quad2D>g_UserInterfaces = {};

	void EnemyHPVib_Update();
	void myHPVib_Update();
	void HPVib_Update(std::vector<UI_List> &list,int i);
	void HBasePVib_Update(std::vector<UI_List>& list, int i);

	bool Init();
	void Draw();
	void Update();
	//void CreateUI(UI_ID type, float x, float y, float z, float xsize, float ysize, DirectX::XMFLOAT4 color);

	void HPCal(float damage, float maxhp,float hp, std::vector<UI_List>& list,int i,bool drawhp);


	
	/*bool IsActive() {
		return Active;
	}*/
	/*static CBattleUI& GetInstance() {
		static CBattleUI Instance;
		return Instance;
	}*/

	////モデルのキーを取得
	//std::shared_ptr<Quad2D> GetUIPtr(UI_ID type) {
	//	// 存在するかを確かめる
	//	return GetInstance().list[(int)type];
	//}

	//void UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4]);

};

