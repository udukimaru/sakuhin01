#pragma once
#include	<DirectXMath.h>
#include <vector>
#include "quad2d.h"
class CTitleUI
{

private:
	//UIデータ格納
	//std::vector<std::shared_ptr<Quad2D>>g_uihash;
	//float t = 0;
	//XMFLOAT4 color = { 1,1,1,1 };
public:

	enum class TitleUI_ID {
		NONE,
		TITLE_LOGO,
		TITLE_BACKGROUND,
		TITLE_CLICK,
		TITLE_STAR,
		MAX
	};
	// 構造体
	struct TitleUI
	{
		TitleUI_ID id;
		const char* texfolder;
		float x;
		float y;
		float width;
		float height;
		DirectX::XMFLOAT2 size;
		DirectX::XMFLOAT4 color={1,1,1,1};
		bool active;
		//DirectX::XMFLOAT2 uv[4];
		float t;
	};
	DirectX::XMFLOAT2 uv[4] = {

			{0.0f ,0.0f},
			{1.0f ,0.0f},
			{0.0f ,1.0f},
			{1.0f ,1.0f}
	};
	std::vector<TitleUI> uilist{
		//  ID                                 ファイル名            x    y   width height size  color  active
		{TitleUI_ID::TITLE_BACKGROUND,"assets/UI/Title/title_background.png",650,380,1300,760, {1,1},{1,1,1,1},true,0},
		{TitleUI_ID::TITLE_LOGO,"assets/UI/Title/title.tga",640, 250, 1200, 200, {1,1}, {1,1,1,1},true,0},
		{TitleUI_ID::TITLE_CLICK,"assets/UI/Title/start.png",640, 540,600, 280, {1,1},{1,1,1,1},true,0},
		{TitleUI_ID::TITLE_STAR,"assets/UI/Title/star.tga",200,20,100, 100, {1,1},{1,1,1,1},true,0},
		//{TitleUI_ID::ENEMY_HP,"assets/UI/HPgauge.png",0,100,200,60, {1,1},{1,1,1,1},true},
	};

	void Update_Blink();

	bool InitTitle_UI();
	void UpdateTitle_UI();
	void DrawTitle_UI();
	//void DrawTitle_UI(float width, float height, XMFLOAT2* uv, float x, float y);
};

