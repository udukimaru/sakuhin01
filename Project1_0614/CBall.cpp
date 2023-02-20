#include "CBall.h"
#include "CPlayer.h"

CPlayer b_player;

bool CBall::Init()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	// モデルの読み込みm
	bool sts = m_model.Init(
		"assets/ball/ball.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/ps.hlsl",			// ピクセルシェーダー
		"assets/player/");	// テクスチャの格納フォルダ

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
	float	dt = static_cast<float>(60) / 1000000;// 微少時間Δｔ	
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
