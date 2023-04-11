#include "CPlayer.h"
#include "CCamera.h"
#include "ModelMgr.h"

// 移動方向
enum class DIRECTION {
	NEUTRAL,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

XMFLOAT3 operator+(XMFLOAT3 left, XMFLOAT3 right)
{
	XMFLOAT3 temp;
	temp.x = left.x + right.x;
	temp.y = left.y + right.y;
	temp.z = left.z + right.z;

	return temp;
}
XMFLOAT3 operator-(XMFLOAT3 left, XMFLOAT3 right)
{
	XMFLOAT3 temp;
	temp.x = left.x - right.x;
	temp.y = left.y - right.y;
	temp.z = left.z - right.z;

	return temp;
}

// モデルを読み込んだかどうか
bool CPlayer::m_modelloadflag = false;

bool CPlayer::Init()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	// モデルの読み込みm
	bool sts = m_model.Init(
		"assets/player/player.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/ps.hlsl",			// ピクセルシェーダー
		"assets/player/");	// テクスチャの格納フォルダ

	XMFLOAT3 size = { 1.03f,1.03f,1.03f };
	XMFLOAT3 rote = { -90,180,0 };
	//m_mtx._11 = size.x;
	//m_mtx._22 = size.y;
	//m_mtx._33 = size.z;
	//m_mtx._44 = 1.0f;

	return sts;
}

void CPlayer::Draw()
{
	m_model.Draw(m_mtx);
}

POINT oldpos{};

void CPlayer::Update()
{
	auto camera = CCamera::GetInstance();
	CDirectInput& input = CDirectInput::GetInstance();

	bool keyinput = false;

	XMFLOAT3 axis(0, 0, 0);

	XMFLOAT4X4 CameraMtx = camera->GetCameraMatrix();

		if (input.CheckKeyBuffer(DIK_W)) {
			keyinput = true;
			axis.x -= CameraMtx._31;
			axis.y -= CameraMtx._32;
			axis.z += CameraMtx._33;
			//SetDirection(0);
		}
		else if (input.CheckKeyBuffer(DIK_S)) {
			keyinput = true;
			axis.x += CameraMtx._31;
			axis.y += CameraMtx._32;
			axis.z -= CameraMtx._33;
			//SetDirection(180);
		}
		else if (input.CheckKeyBuffer(DIK_D))
		{
			keyinput = true;
			axis.x += CameraMtx._11;
			axis.y += CameraMtx._12;
			axis.z -= CameraMtx._13;
			//SetDirection(90);
		}
		else if (input.CheckKeyBuffer(DIK_A))
		{
			keyinput = true;
			axis.x -= CameraMtx._11;
			axis.y -= CameraMtx._12;
			axis.z += CameraMtx._13;
			//SetDirection(-90);
		}

		// キー入力があったときだけ移動する
		if (keyinput)
		{
			axis.y = 0;
			DX11Vec3Normalize(axis, axis);
			m_pos.x += axis.x * 0.2f;
			m_pos.y += axis.y * 0.2f;
			m_pos.z += axis.z * 0.2f;
			SetPos(m_pos);
		}

		// マウスの処理
		XMFLOAT3 lookat = camera->GetLookat();
		XMFLOAT3 eye = camera->GetEye();
		//XMFLOAT3 eye(0, 20, -30);	
		//eye.y = 20;
		XMFLOAT3 distance;

		auto pos = GetPos();

		distance = lookat - pos;
		lookat = lookat - distance;
		eye = eye - distance;

		POINT currentpos{};
		if (input.GetMouseLButtonCheck())
		{
			// 一度押したときだけマウス位置を前回のものにする
			if (input.GetMouseLButtonTrigger())
			{
				oldpos.x = input.GetMousePosX();
				oldpos.y = input.GetMousePosY();
			}
			//現在のマウス位置
			currentpos.x = input.GetMousePosX();
			currentpos.y = input.GetMousePosY();

			// 前回と現在のマウス位置の距離を求める
		distance.x = currentpos.x - oldpos.x;
		distance.y = currentpos.y - oldpos.y;

		// 
		float angleY = 1.0f * (static_cast<float>(distance.x) / 5.0f);
		float angleX = 1.0f * (static_cast<float>(distance.y) / 5.0f);
		auto dis = eye;

		dis.x -= lookat.x;
		dis.y -= lookat.y;
		dis.z -= lookat.z;

		XMFLOAT4X4 mtxX;
		XMFLOAT4X4 mtxY;

		DX11MtxRotationX(angleX, mtxX);
		DX11MtxRotationY(angleY, mtxY);

		DX11MtxMultiply(mtxY, mtxY, mtxX);

		DX11Vec3MulMatrix(dis, dis, mtxY);

		dis.x += lookat.x;
		dis.y += lookat.y;
		dis.z += lookat.z;

		eye = dis;
		oldpos = currentpos;
;
		}
		camera->SetEye(eye);
		camera->SetLookat(lookat);
		camera->CreateCameraMatrix();
		camera->CreateProjectionMatrix();

		//UpdateLocalpose();

		//CaliculateParentChildMtx();

}

void CPlayer::Order()
{
}

void CPlayer::Finalize()
{

}
