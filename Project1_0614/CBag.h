#pragma once
#include "Command_Base.h"
class CBag : public Command_Base
{

	enum class COMMAND_BAG {
		NONE,
		BAG_WINDOW,
		BAG_DATA,
		BACK,
		BACK_SHADOW,
		MAX,
	};
	using BagDataList = UIData<COMMAND_BAG>;
	Quad2D bag[(int)CBag::COMMAND_BAG::MAX];

public:
	// ƒoƒbƒO
	std::vector<BagDataList> g_baglist = {
		{COMMAND_BAG::BACK,"assets/UI/‚à‚Ç‚é_onoff.png",1120, 570,180,120,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,false},
		{COMMAND_BAG::BACK_SHADOW,"assets/UI/—§‘Ì‰e_‚à‚Ç‚é2.png",1107, 580,180,120,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
		{COMMAND_BAG::BAG_DATA,"assets/UI/Battle/Command/Bag/bag_bar.png",360, 160,560,130,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
		{COMMAND_BAG::BAG_WINDOW,"assets/UI/Battle/Command/Bag/bag_window_base.png",640,380,1360,780,{1,1}, {1,1,1,1},false,
		{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},{uv2D[0],uv2D[1],uv2D[2],uv2D[3]},false},
	};
	bool Init();
	void Update();
	void Draw();
	void SetStartSize();

	void IsUIActive(bool active)
	{
		for (int i = 0; i < g_baglist.size(); i++)
		{
			if (active == true)g_baglist[i].active = true;
			else g_baglist[i].active = false;
		}
	}
private:

};

