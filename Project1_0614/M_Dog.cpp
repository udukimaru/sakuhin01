#include "M_Dog.h"
#include "CPlayer.h"
#include "drawaxis.h"
#include "CMonsterMgr.h"
#include <random> 

CPlayer p;

bool M_Dog::Init()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	// ���f���̓ǂݍ���m
	bool sts = m_model.Init(
		"assets/dog/dog2.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/dog/");	// �e�N�X�`���̊i�[�t�H���_

	m_pos.x = 5;
	m_pos.y = 0;
	m_pos.z = -5;

	

	XMFLOAT3 angle = { 0,180,0 };
	XMFLOAT4 axisX; //X��
	XMFLOAT4 axisY; //Y��
	XMFLOAT4 axisZ; //Z��

	//�@X�������o��
	axisX.x = m_mtx._11;
	axisX.y = m_mtx._12;
	axisX.z = m_mtx._13;
	axisX.w = 0.0f;

	//�@Y�������o��
	axisY.x = m_mtx._21;
	axisY.y = m_mtx._22;
	axisY.z = m_mtx._23;
	axisY.w = 0.0f;

	//�@Z�������o��
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;
	XMFLOAT4 qt;    // �N�I�[�^�j�I��

	// �s�񂩂�N�I�[�^�j�I���쐬
	DX11GetQtfromMatrix(m_mtx, qt);

	XMFLOAT4 qtx, qty, qtz; // �N�I�[�^�j�I��

	// �w�莲��]�̃N�I�[�^�j�I���𐶐�
	DX11QtRotationAxis(qtx, axisX, angle.x);
	DX11QtRotationAxis(qty, axisY, angle.y);
	DX11QtRotationAxis(qtz, axisZ, angle.z);

	// �N�I�[�^�j�I��������
	XMFLOAT4 tempqt1;
	DX11QtMul(tempqt1, qt, qtx);

	XMFLOAT4 tempqt2;
	DX11QtMul(tempqt2, qty, qtz);

	XMFLOAT4 tempqt3;
	DX11QtMul(tempqt3, tempqt1, tempqt2);

	// �N�I�[�^�j�I�����m�[�}���C�Y
	DX11QtNormalize(tempqt3, tempqt3);

	// �N�I�[�^�j�I������s��쐬
	DX11MtxFromQt(m_mtx, tempqt3);

	
	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	isActive = true;

	return sts;
}

bool M_Dog::Init(bool group, XMFLOAT4X4 c_mtx)
{
	m_mtx = c_mtx;
	CMonsterMgr::Init(group, c_mtx);
	return false;
}


void M_Dog::Update()
{
	//XMFLOAT3 angle;
	XMFLOAT3 angle = { 0,0,0 };
	bool keyinput = false;

	angle.x = angle.y = angle.z = 0.0f;


}

int M_Dog::AttackDamage()
{
	int damage;
	std::random_device rand_dev;
	std::mt19937 m_mt(rand_dev());
	std::uniform_int_distribution<> rand100(10, 15);
	damage = rand100(m_mt);
	printf("�U����%d\n", damage);

	return damage;
}

int M_Dog::SpecialDamage()
{
	int damage;
	std::random_device rand_dev;
	std::mt19937 m_mt(rand_dev());
	std::uniform_int_distribution<> rand100(40, 50);
	damage = rand100(m_mt);
	printf("�U����%d\n", damage);

	return damage;
}

void M_Dog::Draw()
{
	// ���f���`��
	m_model.Draw(m_mtx);
}

void M_Dog::DrawWithAxis()
{
}
void M_Dog::BattleUpdate()
{
	m_pos.z += 0.5f;
	//if (m_pos.z >= 5) m_pos.z = 5.0f;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;


	//// �����_���ōU���͌���
	//		// �V�[�h�l����p����
	//std::random_device rand_dev;
	//std::mt19937 m_mt(rand_dev());
	//std::uniform_int_distribution<> rand100(10, 15);
	//printf("%d\n", rand100(m_mt));


	//obj->HP -= rand100(m_mt);
	//size2.x = g_monster.HP / g_monster.GetMAXHP() * 1.0f;
	//posX2 = (1.0f - size2.x) / 4 * 1.0f;

	//printf("%f\n", g_monster.HP);
}
void M_Dog::Finalize()
{

}

//int CMonster2::Attack()
//{
//
//	return 0;
//}
