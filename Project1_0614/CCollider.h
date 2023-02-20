#pragma once
#include	"dx11mathutil.h"
class CCollider
{
public:
	static bool Test(XMFLOAT3 pos1, XMFLOAT3 pos2);

	static bool Col(XMFLOAT2 pos1,float width,float height, XMFLOAT2 pos2);

	static bool CameraCol(XMFLOAT3 camerapos, XMFLOAT3 pos);
};

