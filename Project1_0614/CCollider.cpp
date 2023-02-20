#include "CCollider.h"


// 球　球
bool CCollider::Test(XMFLOAT3 pos1, XMFLOAT3 pos2)
{
	float length_x = pos1.x - pos2.x;
	float length_y = pos1.y - pos2.y;
	float length_z = pos1.z - pos2.z;

	if (5 >= length_x * length_x + length_y * length_y + length_z * length_z)
	{
		return true;
	}
    return false;
}

// 矩形　カーソル
bool CCollider::Col(XMFLOAT2 pos1, float width, float height, XMFLOAT2 pos2)
{
	float half_x = width / 2.4;
	float half_y = height / 2.4;

	if ((pos1.x -half_x<= pos2.x &&pos2.x<= pos1.x + half_x) && (pos1.y - half_y <= pos2.y && pos2.y<=pos1.y + half_y))
	{
		return true;
	}
	return false;
}

// カメラ　地面orオブジェクト
bool CCollider::CameraCol(XMFLOAT3 camerapos, XMFLOAT3 pos)
{

	return true;
}
