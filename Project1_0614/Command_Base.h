#pragma once
#include "quad2d.h"
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
	virtual bool Init()=0;
	virtual void Draw()=0;
	virtual void Update()=0;
	virtual void Finalize()=0;

	void UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4]);

};

