#pragma once
#include "quad2d.h"
#include <vector>
#include "CCollider.h"
#include "CDirectInput.h"

//#include "CCommandSelect.h"
//#include "CSkill.h"
//#include "CMyMonster.h"
class Command_Base
{
public:

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
	XMFLOAT2 uv2D[4] = {
	{0.0f,0.0f},
	{1.0f,0.0f},
	{0.0f,1.0f},
	{1.0f,1.0f}
	};
	XMFLOAT2 uv0[4] = {
			{1.0f / 2,0.0f},
			{1.0f,0.0f},
			{1.0f / 2,1.0f},
			{1.0f,1.0f}
	};
	XMFLOAT2 uv[4] = {
			{0.0f,0.0f},
			{1.0f / 2,0.0f},
			{0.0f,1.0f},
			{1.0f / 2,1.0f}
	};

	virtual ~Command_Base() {}
	virtual bool Init();
	virtual void Draw();
	virtual void Update();
	virtual void Finalize();

	//virtual bool IsUIActive(bool is);

	void UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4]);

	template<typename T>
	int CheckOnOff(std::vector<T>& list) {
		// カーソル位置取得
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
	// UIを表示するかしないか
	template<typename T>
	void IsActive(std::vector<T>& list, bool is)
	{
		for (int i = 0; i < list.size(); i++) {
			list[i].active = is;
		}
	}


	//// 初期位置にもどす
	//template<typename T>
	//void SetStartPos(std::vector<T>& list)
	//{
	//	for (int i = 0; i < list.size(); i++)
	//	{
	//		list[i].t = 0.0f;
	//		list[i].x = 0.0f;
	//	}
	//}
	//// 初期サイズにもどす
	//template<typename T>
	//void SetStartFade(std::vector<T>& list)
	//{
	//	for (int i = 0; i < list.size(); i++)
	//	{
	//		list[i].size.x = 0.0f;
	//		list[i].size.y = 0.0f;
	//		list[i].color.w = 0.0f;
	//	}
	//}
};

