#include "CSkydome.h"


bool CSkydome::Init()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	// モデルの読み込みm
	bool sts = m_model.Init(
		"assets/skydome/skydome.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/pstexcol.hlsl",			// ピクセルシェーダー
		"assets/skydome/");	// テクスチャの格納フォルダ

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
