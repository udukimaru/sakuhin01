#include "Grass.h"

DirectX::XMFLOAT4X4 m_mtx;


void Grass::Init()
{
	

	// ���f���̓ǂݍ���m
	bool sts = m_model.Init(
		"assets/texture/poke.obj",	// �t�@�C���� 
		"shader/vs.hlsl",			// ���_�V�F�[�_�[
		"shader/ps.hlsl",			// �s�N�Z���V�F�[�_�[
		"assets/texture/");			// �e�N�X�`���̊i�[�t�H��

	// �s�񏉊���
	DX11MtxIdentity(m_mtx);
}

void Grass::Update()
{
}

void Grass::Draw()
{
}

void Grass::DrawWithAxis()
{
}

void Grass::Finalize()
{
}
