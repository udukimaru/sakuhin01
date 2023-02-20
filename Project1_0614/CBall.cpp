#include "CBall.h"
#include "CPlayer.h"

CPlayer b_player;

bool CBall::Init()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	// ���f���̓ǂݍ���m
	bool sts = m_model.Init(
		"assets/ball/ball.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/player/");	// �e�N�X�`���̊i�[�t�H���_

	XMFLOAT3 p_pos = {};
	p_pos=b_player.GetPos();
	m_pos.x = p_pos.x;
	m_pos.y = p_pos.y+5;
	m_pos.z = p_pos.z;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;
	return sts; 
}

void CBall::Draw()
{
	m_model.Draw(m_mtx);
}

void CBall::DrawWithAxis()
{
}

void CBall::Update()
{
	float	dt = static_cast<float>(60) / 1000000;// �������ԃ���	
	float g = 9.8f*100;
	vy -= (g * dt);
	m_pos.z += vz;
	m_pos.y += vy;
	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;
}

void CBall::Finalize()
{
}
