#include "M_Plain.h"
#include "drawaxis.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// ���f����ǂݍ��񂾂��ǂ���
bool M_Plain::m_modelloadflag = false;

bool M_Plain::Init()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

    m_actionKeepTime = 100;

	// ���f���̓ǂݍ���
	bool sts = m_model[0].Init(
		"assets/plain/cover.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

	// ���f���̓ǂݍ���
	 sts = m_model[1].Init(
		"assets/plain/face.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

     // ���f���̓ǂݍ���
     sts = m_model[2].Init(
         "assets/plain/core.obj",	// �t�@�C���� 
         "shader/vs.hlsl",			// ���_�V�F�[�_�[
         "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
         "assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

     // ���f���̓ǂݍ���
     sts = m_model[3].Init(
         "assets/plain/left_arm.obj",	// �t�@�C���� 
         "shader/vs.hlsl",			// ���_�V�F�[�_�[
         "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
         "assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

      // ���f���̓ǂݍ���
     sts = m_model[4].Init(
         "assets/plain/right_arm.obj",	// �t�@�C���� 
         "shader/vs.hlsl",			// ���_�V�F�[�_�[
         "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
         "assets/plain/");	// �e�N�X�`���̊i�[�t�H���_

	// �����ʒu
	m_pos.x = 5;
	m_pos.y = 0;
	m_pos.z = 10;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	isActive = true;
    // �V�[�h�l����p����
    std::random_device rand_dev;
    // �V�[�h�l�Z�b�g
    m_mt.seed(rand_dev());
    m_mt2.seed(rand_dev());

	return sts;
}

void M_Plain::Update()
{    
	// �����̏�����...
	XMFLOAT3 pos = {};
    XMFLOAT4 axisX;
    XMFLOAT4 axisY;
    XMFLOAT4 axisZ;

    Move();

    // X�������o��
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

    XMFLOAT4 qt;

    // �s�񂩂�N�I�[�^�j�I���쐬
    DX11GetQtfromMatrix(m_mtx, qt);

    XMFLOAT4 qtx, qty, qtz;

    // �w�莲��]�̃N�I�[�^�j�I���쐬
    DX11QtRotationAxis(qtx, axisX, m_angle.x);
    DX11QtRotationAxis(qty, axisY, m_angle.y);
    DX11QtRotationAxis(qtz, axisZ, m_angle.z);
    // �N�I�[�^�j�I������
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

    // Z�������o��
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    m_pos.x -= axisZ.x * m_speed;
    m_pos.y -= axisZ.y * m_speed;
    m_pos.z -= axisZ.z * m_speed;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;
}

void M_Plain::BattleUpdate()
{
   
    m_pos.z -= 0.3f;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;
}

void M_Plain::Move()
{
    // ��������
    std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(M_Plain::ACTION::MAX_ACTION) - 1);
    std::uniform_int_distribution<int32_t> rand10(10, 50);

    // ��]�p���������񃊃Z�b�g
    m_angle.x = m_angle.y = m_angle.z = 0.0f;

    // �A�N�V�����ɂ���]�p���Z�b�g
    switch (m_action)
    {
    case M_Plain::ACTION::ACT_STRAIGHT:
        m_angle.x = m_angle.y = m_angle.z = 0.0f;
        break;
    case M_Plain::ACTION::ACT_LEFT:
        m_angle.y = 1.1f;

        break;
    case M_Plain::ACTION::ACT_RIGHT:
        m_angle.y = -1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLP:
        m_angle.y = -1.1f;
        // partsangle[idx].y -= 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLM:
        m_angle.y = 1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    }
    // m_action = M_Plain::ACTION::ACT_LEFT;
      //�J�E���^�[���Z
    if (--m_actionKeepTime <= 0) {
        // �����ɂ�莟�̃A�N�V�����Ǝ������Ԃ�ݒ�
        m_action = static_cast<ACTION>(rand4(m_mt));
        m_actionKeepTime = rand10(m_mt2);
    }
}

void M_Plain::Draw()
{
	// ���f���`��
	m_model[1].Draw(m_mtx);
	m_model[0].Draw(m_mtx);
    m_model[2].Draw(m_mtx);
    m_model[3].Draw(m_mtx);
    m_model[4].Draw(m_mtx);
}

void M_Plain::Finalize()
{
    m_model->Uninit();
}

int M_Plain::AttackDamage()
{
    //int damage;
    std::random_device rand_dev;
    std::mt19937 m_mt(rand_dev());
    std::uniform_int_distribution<> rand100(10, 15);
    attack_power = rand100(m_mt);
    printf("�G�U����%d\n", attack_power);

    return attack_power;
}