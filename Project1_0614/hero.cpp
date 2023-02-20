#include	<random>
#include	"hero.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// ��Ԃ̐e�q�֌W�y�я����ʒu�E�����p�x���`�����f�[�^
Hero::HeroInitData	Hero::ObjectInitData[] = {
	//   �e							���f���ԍ�						�����ʒu				�����p�x	// ���ӁF���Ȃ炸�q�����e����ɂȂ�Ԃ���
	{ HEROPARTS::NONE,	HEROPARTS::HIP,	{ 0.0f,   0.0f,	  0.0f },	{ 0,0,0 }	},			// ��
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
	{ HEROPARTS::ARMR1,	HEROPARTS::BLADE, { -0.4f, -1.3f,   -2.0f },	{ 90,30,90 }   },		// ��
	{ HEROPARTS::END,		HEROPARTS::END,	{ 0.0f,   0.0f,   0.0f },	{ 0,0,0 }	}		// �I��
};

// ���f���t�@�C�������X�g
Hero::HeroModelData			Hero::XFileData[] = {
	{ HEROPARTS::HIP,  "assets/model/hero/c0_hip.x" },		// ��
	{ HEROPARTS::BODY, "assets/model/hero/c0_body.x" },		// ��
	{ HEROPARTS::HEAD, "assets/model/hero/c0_head.x" },		// ��
	{ HEROPARTS::ARMR0,"assets/model/hero/c0_armr0.x" },	// �E�r�O
	{ HEROPARTS::ARML0,"assets/model/hero/c0_arml0.x" },	// ���r�O
	{ HEROPARTS::LEGR0,"assets/model/hero/c0_legr0.x" },	// �E���O
	{ HEROPARTS::LEGL0,"assets/model/hero/c0_legl0.x" },	// �����O
	{ HEROPARTS::ARMR1,"assets/model/hero/c0_armr1.x" },	// �E�r�P
	{ HEROPARTS::ARML1,"assets/model/hero/c0_arml1.x" },	// ���r�P
	{ HEROPARTS::LEGR1,"assets/model/hero/c0_legr1.x" },	// �E���P
	{ HEROPARTS::LEGL1,"assets/model/hero/c0_legl1.x" },	// �����P
	{ HEROPARTS::BLADE,"assets/model/hero/c0_blade.x" },	// ��
	{ HEROPARTS::END,nullptr }
};

// ���f����ǂݍ��񂾂��ǂ���
bool Hero::m_modelloadflag = false;

bool Hero::Init() {

	bool sts = true;

	// �s�񏉊���
	DX11MtxIdentity(m_mtx);	// ���f����ǂݍ���

	// �ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if (Hero::m_modelloadflag == false) {
		// ���f���ǂݍ��݁iHERO�p�j
		for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
			sts = ModelMgr::GetInstance().LoadModel(
				Hero::XFileData[i].XfileName,	// �t�@�C���� 
				"shader/vs.hlsl",				// ���_�V�F�[�_�[
				"shader/ps.hlsl",				// �s�N�Z���V�F�[�_�[
				"assets/model/hero/");				// �e�N�X�`���̊i�[�t�H���_
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Hero::XFileData[i].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}
		}
		Hero::m_modelloadflag = true;
	}

	// ���f���|�C���^�[���Z�b�g
	for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
		SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	}

	// �v���C���s�񏉊���(�����ʒu)�i�����̂��Ƃ������l�����s����쐬�j
	for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
		DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	}

	// �e�q�֌W���l�������s����v�Z����
	CaliculateParentChildMtx();

	return sts;
}

void Hero::Draw() {

	// ���f���`��
	drawaxis(m_mtx, 200, m_pos);

	for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}
}

void Hero::UpdateLocalpose() {

	// �e�p�[�c�̉�]�p�x(�O�t���[������̕ψʗ�)
	XMFLOAT3			partsangle[static_cast<int>(HEROPARTS::PARTSMAX)];
	XMFLOAT3			partstrans[static_cast<int>(HEROPARTS::PARTSMAX)];

	// �ǂ̃p�[�c�𓮂�����
	static int idx = 0;
	bool	initflag = false;

	// �p�x�ƈړ��ʂ�������
	for (int i = 0; i < static_cast<int>(HEROPARTS::PARTSMAX); i++) {
		partsangle[i].x = 0.0f;
		partsangle[i].y = 0.0f;
		partsangle[i].z = 0.0f;
		partstrans[i].x = 0.0f;
		partstrans[i].y = 0.0f;
		partstrans[i].z = 0.0f;
	}

	// ����p�[�c��؂�ւ�
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_TAB)) {
		idx++;
		if (idx > static_cast<int>(HEROPARTS::PARTSMAX) - 3) {
			idx = 0;
		}
	}

	// �p�[�c�̃��[�J���|�[�Y�����߂�ׂ̃L�[����
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
		partsangle[idx].x += 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
		partsangle[idx].x -= 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
		partsangle[idx].y += 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
		partsangle[idx].y -= 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F1)) {
		partsangle[idx].z += 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F2)) {
		partsangle[idx].z -= 1.0f;
	}

	// ������Ԃɂ���
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
		initflag = true;
		idx = 0;
	}

	// �����|�[�Y�ɖ߂�
	if (initflag) {
		InitalPose();
	}

	// �p�[�c�̊p�x���[�J���|�[�Y��\���s����v�Z
	XMFLOAT4X4 partsmtx;
	DX11MakeWorldMatrix(partsmtx, partsangle[idx], partstrans[idx]);
	DX11MtxMultiply(m_mtxlocalpose[idx], partsmtx, m_mtxlocalpose[idx]);
}

// �X�V
void Hero::Update() {

	XMFLOAT4 axisX;
	XMFLOAT4 axisY;
	XMFLOAT4 axisZ;

	static bool keyinput = true;

	//�@�{�̂̈ړ�����
	//  X�������o��
	axisX.x = m_mtx._11;
	axisX.y = m_mtx._12;
	axisX.z = m_mtx._13;
	axisX.w = 0.0f;

	// Y�������o��
	axisY.x = m_mtx._21;
	axisY.y = m_mtx._22;
	axisY.z = m_mtx._23;
	axisY.w = 0.0f;

	// Z�������o��
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// �ړ��ʋy�ъp�x���O�ɂ���
	m_speed = 0.0f;
	m_angle.x = m_angle.y = m_angle.z = 0.0f;

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
		m_angle.y -= 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		m_angle.y += 1.0f;
		keyinput = true;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W)) {
		m_speed = 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S)) {
		m_speed = -1.0f;
		keyinput = true;
	}

	// �L�[���͂��������ꍇ
	if (keyinput) {
		XMFLOAT4 qt;	// �N�I�[�^�j�I��

		// �s�񂩂�N�I�[�^�j�I���𐶐�
		DX11GetQtfromMatrix(m_mtx, qt);

		XMFLOAT4 qtx, qty, qtz;		// �N�I�[�^�j�I��

		// �w�莲��]�̃N�I�[�^�j�I���𐶐�
		DX11QtRotationAxis(qtx, axisX, m_angle.x);
		DX11QtRotationAxis(qty, axisY, m_angle.y);
		DX11QtRotationAxis(qtz, axisZ, m_angle.z);

		// �N�I�[�^�j�I��������
		XMFLOAT4 tempqt1;
		DX11QtMul(tempqt1, qt, qtx);

		XMFLOAT4 tempqt2;
		DX11QtMul(tempqt2, qty, qtz);

		XMFLOAT4 tempqt3;
		DX11QtMul(tempqt3, tempqt1, tempqt2);

		// �N�I�[�^�j�I�����m�[�}���C�Y
		DX11QtNormalize(tempqt3, tempqt3);

		// �N�I�[�^�j�I������s����쐬
		DX11MtxFromQt(m_mtx, tempqt3);
	}

	// Z�������o��
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// �ʒu���X�V
	m_pos.x += axisZ.x*m_speed;
	m_pos.y += axisZ.y*m_speed;
	m_pos.z += axisZ.z*m_speed;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;					
	m_mtx._43 = m_pos.z;

	// ���[�J���|�[�Y���X�V����
	UpdateLocalpose();

	// �e�q�֌W���l�������s����v�Z����
	CaliculateParentChildMtx();

	keyinput = false;
}

void Hero::Finalize() {

}

void Hero::CaliculateParentChildMtx() {

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