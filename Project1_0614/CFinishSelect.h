#pragma once
#include "Command_Base.h"
class CFinishSelect :
    public Command_Base
{
	enum class COMMAND_FINISH {
		NONE,
		SELECT_YES,
		SELECT_NO,
		MAX,
	};
	using FinSelectDataList = UIData<COMMAND_FINISH>;
	Quad2D select_mon[(int)COMMAND_FINISH::MAX];

	bool joinmonster;
public:
	// èüóòå„ÇÃëIëéà
	std::vector<FinSelectDataList> g_finishlist = {
		{COMMAND_FINISH::SELECT_YES,"assets/UI/Battle/Command/Finish/ÇÕÇ¢.png",420, 360,300,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,true,false,{420, 360}},
		{COMMAND_FINISH::SELECT_NO,"assets/UI/Battle/Command/Finish/Ç¢Ç¢Ç¶.png",760, 360,300,150,{1,1}, {1,1,1,1},false,
		{uv[0],uv[1],uv[2],uv[3]},{uv0[0],uv0[1],uv0[2],uv0[3]},0,true,false,{760, 360}},
	};

	bool Init();
	void Draw();
	void Update();
	void Finalize();

	void IsUIActive(bool active)
	{
		for (int i = 0; i < g_finishlist.size(); i++)
		{
			if (active == true)g_finishlist[i].active = true;
			else g_finishlist[i].active = false;
		}
	}
};

