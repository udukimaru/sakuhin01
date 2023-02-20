#include "CSkydome.h"


bool CSkydome::Init()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	// ���f���̓ǂݍ���m
	bool sts = m_model.Init(
		"assets/skydome/skydome.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/pstexcol.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/skydome/");	// �e�N�X�`���̊i�[�t�H���_

	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.z = 0;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	return sts;
}

void CSkydome::Draw()
{
	m_model.Draw(m_mtx);
}

void CSkydome::Finalize()
{
	m_model.Uninit();
}
