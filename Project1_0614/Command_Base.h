#pragma once
#include "quad2d.h"
#include <vector>
#include "CCollider.h"
#include "CDirectInput.h"

class Command_Base
{
protected:
	//XMFLOAT2 slide;

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
		const DirectX::XMFLOAT2 fixedPos;
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

	enum class STATE {
		MOVE,
		NOMAL,
		NOMALTOMOVE,
	};
	STATE state = STATE::MOVE;

	virtual ~Command_Base() {}
	virtual bool Init();        // 初期化
	virtual void Update();      // 更新処理
	virtual void Draw();        // 描画
	virtual void Finalize();    // 終了処理


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
			if (CCollider::Col(pos, list[i].width, list[i].height, cursor_pos) && list[i].active == true)
			{
				list[i].on_off = true;

				if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
				{
					return i;
				}
			}
			else
			{
				list[i].on_off = false;
			}
		}
	}

	void SlidePos(float x,float y);
};

