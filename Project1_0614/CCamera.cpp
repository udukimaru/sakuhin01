#include "CCamera.h"
#include "M_Dog.h"
#include "DX11util.h"

M_Dog dog;

void CCamera::UpdateCamera()
{
	if (m_updateflag) {

		m_Eye.x += (m_EyeTargetPos.x - m_Eye.x) * 0.1f;
		m_Eye.y += (m_EyeTargetPos.y - m_Eye.y) * 0.1f;
		m_Eye.z += (m_EyeTargetPos.z - m_Eye.z) * 0.1f;



		//  十分目標位置に近づいたら

		CreateCameraMatrix();

		float lng;

		XMFLOAT3 vec;

		vec.x = m_EyeTargetPos.x - m_Eye.x;
		vec.y = m_EyeTargetPos.y - m_Eye.y;
		vec.z = m_EyeTargetPos.z - m_Eye.z;

		DX11Vec3Length(vec, lng);

		if (lng < 1.5f)
		{
			m_Eye = m_EyeTargetPos;
			m_updateflag = false;
		}

	}
}
void CCamera::AutoCamera()
{
    // 乱数生成
    std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(CCamera::ACTION::MAX_ACTION) - 1);
    std::uniform_int_distribution<int32_t> rand10(10, 50);

	//m_action = CCamera::ACTION::ACT_ZERO;

	switch (m_action)
	{
	case CCamera::ACTION::ACT_ZERO:
		m_Eye = { 15, 6, -18 };
		m_Lookat = { 0,0, 7.5f };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;

		//m_Eye = { 10, 8, 12 };
		//m_Lookat = { 5,0,-5 };
		////平行光源をセット
		//DX11LightUpdate(
		//	DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		//SetEye(m_Eye);
		//SetLookat(m_Lookat);
		//CreateCameraMatrix();
		//CreateProjectionMatrix();

		//break;
	case CCamera::ACTION::ACT_ENEMY:
		XMFLOAT4X4 mtx;
		m_Eye = { 8,6,-5};
		m_Lookat = { 5,5, 10 };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));


		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;
	case CCamera::ACTION::ACT_MY_MONSTER:

		m_Eye = { 15, 6, -18 };
		m_Lookat = { 0,0, 7.5f };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;

		//m_Eye = { 10, 8, 12 };
		//m_Lookat = { 5,0,-5 };
		////平行光源をセット
		//DX11LightUpdate(
		//	DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		//SetEye(m_Eye);
		//SetLookat(m_Lookat);
		//CreateCameraMatrix();
		//CreateProjectionMatrix();

		//break;
	case CCamera::ACTION::ACT_MOVE_1:
		m_Eye = { 25, 6, 7.5f };
		m_Lookat = { 0,0, 0 };
		m_Eye.z += 1.0f;

		//DX11MtxRotationY(45.0f, mtx);// Y軸回転行列

		//DX11Vec3MulMatrix(m_Eye, m_Eye, mtx);

		SetEyeTargetPos(m_Eye);

		//UpdateCamera();
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));

		break;
	case CCamera::ACTION::ACT_MOVE_2:
		m_Eye = { 10, 8, 12 };
		m_Lookat = { 5,0,-5 };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;
	}

	// カウンター減算
	if (--m_actionKeepTime <= 0) {
		// 乱数により次のアクションと持続時間を設定
		m_action = static_cast<ACTION>(rand4(m_mt));
		m_actionKeepTime = 180;
	}
}
void CCamera::AutoCameraUpdate()
{
	m_actionKeepTime++;
	if (m_actionKeepTime >= 0 &&m_actionKeepTime <= 120) {
		m_action = CCamera::ACTION::ACT_ZERO;
	}
	if (m_actionKeepTime > 120 && m_actionKeepTime <= 240) {
		m_action = CCamera::ACTION::ACT_ENEMY;
	}
	if (m_actionKeepTime > 240 && m_actionKeepTime <= 360) {
		m_action = CCamera::ACTION::ACT_MY_MONSTER;
	}
	if (m_actionKeepTime > 360 && m_actionKeepTime <= 480) {
		m_action = CCamera::ACTION::ACT_MOVE_1;
	}

	switch (m_action)
	{
	case CCamera::ACTION::ACT_ZERO:
		m_Eye = { 15, 6, -18 };
		m_Lookat = { 0,0, 7.5f };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;
	case CCamera::ACTION::ACT_ENEMY:
		XMFLOAT4X4 mtx;
		m_Eye = { 8,6,-5 };
		m_Lookat = { 5,5, 10 };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));


		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;
	case CCamera::ACTION::ACT_MY_MONSTER:


		m_Eye = { 10, 8, 12 };
		m_Lookat = { 5,0,-5 };
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		SetEye(m_Eye);
		SetLookat(m_Lookat);
		CreateCameraMatrix();
		CreateProjectionMatrix();

		break;
	case CCamera::ACTION::ACT_MOVE_1:
		m_Eye = { 15, 6, -20 };
		m_Lookat = { 0,0, 0 };
		m_Eye.z += 1.0f;

		DX11MtxRotationY(45.0f, mtx);// Y軸回転行列

		DX11Vec3MulMatrix(m_Eye, m_Eye, mtx);

		SetEyeTargetPos(m_Eye);

		UpdateCamera();
		//平行光源をセット
		DX11LightUpdate(
			DirectX::XMFLOAT4(m_Eye.x, m_Eye.y, m_Eye.z, 0));
		//m_actionKeepTime=0.0f;
		break;
	case CCamera::ACTION::ACT_MOVE_2:
		break;
	}
}
