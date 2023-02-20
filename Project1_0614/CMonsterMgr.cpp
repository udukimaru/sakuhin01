#include "CMonsterMgr.h"
#include "ModelMgr.h"
#include "dx11mathutil.h"

bool CMonsterMgr::Init()
{
    bool sts = true;

    // �s�񏉊���
    DX11MtxIdentity(m_mtx);
    //for (int i = 0; i < CMonsterMgr::MonsterList.size(); i++) {
    //// �s�񏉊���
    //DX11MtxIdentity(CMonsterMgr::MonsterList[i].mtx);

    //    sts = ModelMgr::GetInstance().LoadModel(
    //        CMonsterMgr::MonsterList[i].filename,
    //        "shader/vs.hlsl",			// ���_�V�F�[�_�[
    //        "shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
    //        CMonsterMgr::MonsterList[i].texname);	// �e�N�X�`���̊i�[�t�H���_      // �������ς���
    //    
    //}
    return sts;
}

bool CMonsterMgr::Init(bool group, XMFLOAT4X4 c_mtx)
{
    bool sts = true;
    enemy = group;

    //�@�G�Ȃ�Ό�����+Z�A�����i�莝���j�Ȃ�-Z
    if (enemy == false)// ����
    {
		XMFLOAT3 angle = { 0,180,0 };
		XMFLOAT4 axisX; //X��
		XMFLOAT4 axisY; //Y��
		XMFLOAT4 axisZ; //Z��

		//�@X�������o��
		axisX.x = c_mtx._11;
		axisX.y = c_mtx._12;
		axisX.z = c_mtx._13;
		axisX.w = 0.0f;

		//�@Y�������o��
		axisY.x = c_mtx._21;
		axisY.y = c_mtx._22;
		axisY.z = c_mtx._23;
		axisY.w = 0.0f;

		//�@Z�������o��
		axisZ.x = c_mtx._31;
		axisZ.y = c_mtx._32;
		axisZ.z = c_mtx._33;
		axisZ.w = 0.0f;
		XMFLOAT4 qt;    // �N�I�[�^�j�I��

		// �s�񂩂�N�I�[�^�j�I���쐬
		DX11GetQtfromMatrix(c_mtx, qt);

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
		DX11MtxFromQt(c_mtx, tempqt3);


		c_mtx._41 = m_pos.x;
		c_mtx._42 = m_pos.y;
		c_mtx._43 = m_pos.z;
    }
	DX11MtxIdentity(c_mtx);
    return sts;
}

void CMonsterMgr::Draw()
{
    //for (int i = 0; i < CMonsterMgr::MonsterList.size(); i++) {
        // ���f���`��
        m_models->Draw(m_mtx);
    //}
}

void CMonsterMgr::Draw(DirectX::XMFLOAT4X4 mtx)
{
    m_models->Draw(mtx);
}

//void CMonsterMgr::ActionUpdate(CMonsterMgr* pThis, Skill_ID id)
//{
//   
//}

void CMonsterMgr::BattleUpdate()
{
}

void CMonsterMgr::Update()
{
}

void CMonsterMgr::Finalize()
{
}
