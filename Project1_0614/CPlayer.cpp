#include "CPlayer.h"
#include "CCamera.h"
#include "ModelMgr.h"

// �ړ�����
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

// ��Ԃ̐e�q�֌W�y�я����ʒu�E�����p�x���`�����f�[�^
CPlayer::HeroInitData	CPlayer::ObjectInitData[] = {
	//   �e							���f���ԍ�						�����ʒu				�����p�x	// ���ӁF���Ȃ炸�q�����e����ɂȂ�Ԃ���
	{ HEROPARTS::NONE,	HEROPARTS::HIP,	{ 0.0f,   5.0f,	  0.0f },	{ 0,-180,0 }	},			// ��
	{ HEROPARTS::HIP,		HEROPARTS::BODY,	{ 0.0f,   0.8f,   -0.1f },	{ 0,0,0 }	},			// ��
	{ HEROPARTS::BODY,	HEROPARTS::HEAD,	{ 0.0f,   1.3f,   -0.1f },	{ 0,0,0 }	},			// ��					
	{ HEROPARTS::BODY,	HEROPARTS::ARMR0,	{ -0.4f,  0.9f,    0.1f },	{ 0,0,0 }	},			// �E�r�O
	{ HEROPARTS::BODY,	HEROPARTS::ARML0,	{ 0.4f,   0.9f,    0.1f },	{ 0,0,0 }	},			// ���r�O
	{ HEROPARTS::HIP,		HEROPARTS::LEGR0,	{ -0.4f, -0.3f,  -0.05f },	{ 0,0,0 }	},			// �E���O
	{ HEROPARTS::HIP,		HEROPARTS::LEGL0,	{ 0.4f,  -0.3f,  -0.05f },	{ 0,0,0 }	},			// �����O
	{ HEROPARTS::ARMR0,	HEROPARTS::ARMR1,	{ -0.8f, -1.2f,   0.1f },	{ 0,0,0 }	},			// �E�r�P
	{ HEROPARTS::ARML0,	HEROPARTS::ARML1,	{ 0.8f,  -1.2f,   0.1f },	{ 0,0,0 }	},			// ���r�P
	{ HEROPARTS::LEGR0,	HEROPARTS::LEGR1,	{ -0.3f, -1.9f,   0.05f },	{ 0,0,0 }	},			// �E���P
	{ HEROPARTS::LEGL0,	HEROPARTS::LEGL1,	{ 0.3f,  -1.9f,   0.05f },	{ 0,0,0 }	},			// �����P
	//{ HEROPARTS::ARMR1,	HEROPARTS::BLADE, { -0.4f, -1.3f,   -2.0f },	{ 90,30,90 }   },		// ��
	{ HEROPARTS::END,		HEROPARTS::END,	{ 0.0f,   0.0f,   0.0f },	{ 0,0,0 }	}		// �I��
};

// ���f���t�@�C�������X�g
CPlayer::HeroModelData			CPlayer::XFileData[] = {
	{ HEROPARTS::HIP,  "assets/player/hero/c0_hip.x" },		// ��
	{ HEROPARTS::BODY, "assets/player/hero/c0_body.x" },		// ��
	{ HEROPARTS::HEAD, "assets/player/hero/c0_head.x" },		// ��
	{ HEROPARTS::ARMR0,"assets/player/hero/c0_armr0.x" },	// �E�r�O
	{ HEROPARTS::ARML0,"assets/player/hero/c0_arml0.x" },	// ���r�O
	{ HEROPARTS::LEGR0,"assets/player/hero/c0_legr0.x" },	// �E���O
	{ HEROPARTS::LEGL0,"assets/player/hero/c0_legl0.x" },	// �����O
	{ HEROPARTS::ARMR1,"assets/player/hero/c0_armr1.x" },	// �E�r�P
	{ HEROPARTS::ARML1,"assets/player/hero/c0_arml1.x" },	// ���r�P
	{ HEROPARTS::LEGR1,"assets/player/hero/c0_legr1.x" },	// �E���P
	{ HEROPARTS::LEGL1,"assets/player/hero/c0_legl1.x" },	// �����P
	//{ HEROPARTS::BLADE,"assets/model/hero/c0_blade.x" },	// ��
	{ HEROPARTS::END,nullptr }
};

// ���f����ǂݍ��񂾂��ǂ���
bool CPlayer::m_modelloadflag = false;

bool CPlayer::Init()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	// ���f���̓ǂݍ���m
	bool sts = m_model.Init(
		"assets/player/player_noBone.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/player/");	// �e�N�X�`���̊i�[�t�H���_

	XMFLOAT3 size = { 1.03f,1.03f,1.03f };
	XMFLOAT3 rote = { -90,180,0 };
	//m_mtx._11 = size.x;
	//m_mtx._22 = size.y;
	//m_mtx._33 = size.z;
	//m_mtx._44 = 1.0f;

	return sts;

	//bool sts = true;

	//// �s�񏉊���
	//DX11MtxIdentity(m_mtx);	// ���f����ǂݍ���

	////// �ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	////if (CPlayer::m_modelloadflag == false) {
	////	// ���f���ǂݍ��݁iHERO�p�j
	////	for (int i = 0; i < static_cast<int>(CPlayer::PARTSMAX) - 2; i++) {
	////		sts = ModelMgr::GetInstance().LoadModel(
	////			CPlayer::XFileData[i].XfileName,	// �t�@�C���� 
	////			"shader/vs.hlsl",				// ���_�V�F�[�_�[
	////			"shader/ps.hlsl",				// �s�N�Z���V�F�[�_�[
	////			"assets/player/hero/");				// �e�N�X�`���̊i�[�t�H���_
	////		if (!sts) {
	////			char str[128];
	////			sprintf_s<128>(str, "%s", CPlayer::XFileData[i].XfileName);
	////			MessageBox(nullptr, str, "load error", MB_OK);
	////		}
	////	}
	////	CPlayer::m_modelloadflag = true;
	////}

	////// ���f���|�C���^�[���Z�b�g
	////for (int i = 0; i < static_cast<int>(CPlayer::PARTSMAX) - 2; i++) {
	////	SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	////}

	////// �v���C���s�񏉊���(�����ʒu)�i�����̂��Ƃ������l�����s����쐬�j
	////for (int i = 0; i < static_cast<int>(CPlayer::PARTSMAX) - 2; i++) {
	////	XMFLOAT3 size = { 0.5f,0.5f,0.5f };
	////	m_mtxlocalpose[i]._11 = size.x;
	////	m_mtxlocalpose[i]._22 = size.y;
	////	m_mtxlocalpose[i]._33 = size.z;
	////	m_mtxlocalpose[i]._44 = 0.0f;

	////	DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	////}

	////// �e�q�֌W���l�������s����v�Z����
	////CaliculateParentChildMtx();


	return sts;
}

void CPlayer::Draw()
{
	m_model.Draw(m_mtx);
	/*for (int i = 0; i < static_cast<int>(CPlayer::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}*/
}

void CPlayer::DrawWithAxis()
{
}

POINT oldpos{};

void CPlayer::Update()
{
	auto camera = CCamera::GetInstance();
	CDirectInput& input = CDirectInput::GetInstance();

	
	bool keyinput = false;

	XMFLOAT3 axis(0, 0, 0);



	XMFLOAT4X4 CameraMtx = camera->GetCameraMatrix();

	//float speed = 0.3f;

	//
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

		// �L�[���͂��������Ƃ������ړ�����
		if (keyinput)
		{
			axis.y = 0;
			DX11Vec3Normalize(axis, axis);
			m_pos.x += axis.x * 0.2f;
			m_pos.y += axis.y * 0.2f;
			m_pos.z += axis.z * 0.2f;
			SetPos(m_pos);
		}

		// �}�E�X�̏���
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
			// ��x�������Ƃ������}�E�X�ʒu��O��̂��̂ɂ���
			if (input.GetMouseLButtonTrigger())
			{
				oldpos.x = input.GetMousePosX();
				oldpos.y = input.GetMousePosY();
			}
			//���݂̃}�E�X�ʒu
			currentpos.x = input.GetMousePosX();
			currentpos.y = input.GetMousePosY();

			// �O��ƌ��݂̃}�E�X�ʒu�̋��������߂�
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

void CPlayer::UpdateLocalpose()
{
	
	// �e�p�[�c�̉�]�p�x(�O�t���[������̕ψʗ�)
	XMFLOAT3			partsangle[static_cast<int>(CPlayer::PARTSMAX)];
	XMFLOAT3			partstrans[static_cast<int>(CPlayer::PARTSMAX)];

	// �ǂ̃p�[�c�𓮂�����
	static int idx = 0;
	bool	initflag = false;

	// �p�x�ƈړ��ʂ�������
	for (int i = 0; i < static_cast<int>(CPlayer::PARTSMAX); i++) {
		partsangle[i].x = 0.0f;
		partsangle[i].y = 0.0f;
		partsangle[i].z = 0.0f;
		partstrans[i].x = 0.0f;
		partstrans[i].y = 0.0f;
		partstrans[i].z = 0.0f;
	}
	auto camera = CCamera::GetInstance();
	CDirectInput& input = CDirectInput::GetInstance();


	bool keyinput = false;

	XMFLOAT3 axis(0, 0, 0);

	XMFLOAT4X4 CameraMtx = camera->GetCameraMatrix();

	//float speed = 0.3f;

	//
	if (input.CheckKeyBuffer(DIK_W)) {
		keyinput = true;
		axis.x -= CameraMtx._31;
		axis.y -= CameraMtx._32;
		axis.z += CameraMtx._33;
	}
	else if (input.CheckKeyBuffer(DIK_S)) {
		keyinput = true;
		axis.x += CameraMtx._31;
		axis.y += CameraMtx._32;
		axis.z -= CameraMtx._33;
	}
	else if (input.CheckKeyBuffer(DIK_D))
	{
		keyinput = true;
		axis.x += CameraMtx._11;
		axis.y += CameraMtx._12;
		axis.z -= CameraMtx._13;
	}
	else if (input.CheckKeyBuffer(DIK_A))
	{
		keyinput = true;
		axis.x -= CameraMtx._11;
		axis.y -= CameraMtx._12;
		axis.z += CameraMtx._13;
	}

	// �L�[���͂��������Ƃ������ړ�����
	if (keyinput)
	{
		axis.y = 0;
		DX11Vec3Normalize(axis, axis);
		partstrans[idx].x -= axis.x * 0.2f;
		partstrans[idx].y -= axis.y * 0.2f;
		partstrans[idx].z -= axis.z * 0.2f;
		SetPos(partstrans[idx]);
	}

	// �}�E�X�̏���
	XMFLOAT3 lookat = camera->GetLookat();
	XMFLOAT3 eye = camera->GetEye();

	XMFLOAT3 distance;

	auto pos = partstrans[idx];

	distance = lookat - pos;
	lookat = lookat - distance;
	eye = eye - distance;

	POINT currentpos{};
	if (input.GetMouseLButtonCheck())
	{
		// ��x�������Ƃ������}�E�X�ʒu��O��̂��̂ɂ���
		if (input.GetMouseLButtonTrigger())
		{
			oldpos.x = input.GetMousePosX();
			oldpos.y = input.GetMousePosY();
		}
		//���݂̃}�E�X�ʒu
		currentpos.x = input.GetMousePosX();
		currentpos.y = input.GetMousePosY();

		// �O��ƌ��݂̃}�E�X�ʒu�̋��������߂�
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


	}
	camera->SetEye(eye);
	camera->SetLookat(lookat);
	camera->CreateCameraMatrix();
	camera->CreateProjectionMatrix();

	// ����p�[�c��؂�ւ�
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_TAB)) {
		idx++;
		if (idx > static_cast<int>(CPlayer::PARTSMAX) - 3) {
			idx = 0;
		}
	}

	//// �p�[�c�̃��[�J���|�[�Y�����߂�ׂ̃L�[����
	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
	//	partstrans[idx].x -= 0.5f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
	//	partstrans[idx].x += 0.5f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W)) {
	//	partstrans[idx].z -= 0.5f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S)) {
	//	partstrans[idx].z += 0.5f;
	//}

	
	// �p�[�c�̊p�x���[�J���|�[�Y��\���s����v�Z
	XMFLOAT4X4 partsmtx;
	DX11MakeWorldMatrix(partsmtx, partsangle[idx], partstrans[idx]);
	DX11MtxMultiply(m_mtxlocalpose[idx], partsmtx, m_mtxlocalpose[idx]);

	CaliculateParentChildMtx();
}

void CPlayer::Order()
{
}

void CPlayer::Finalize()
{

}

void CPlayer::CaliculateParentChildMtx()
{

	// ��Ԃ̐e�̃L���^�s���ɍs����Z�b�g
//	m_mtxlocalpose[TANK_CATERPILLAR] = m_mtx;

	// �e�q�֌W���l�������s������
	for (int i = 0; i < static_cast<int>(HEROPARTS::PARTSMAX) - 2; i++) {
		m_mtxParentChild[i] = m_mtxlocalpose[i];
		for (int j = static_cast<int>(ObjectInitData[i].ParentObjectNo);
			j != static_cast<int>(HEROPARTS::NONE);
			j = static_cast<int>(ObjectInitData[j].ParentObjectNo)) {

			DX11MtxMultiply(m_mtxParentChild[i], m_mtxParentChild[i], m_mtxlocalpose[j]);
		}
	}
}
