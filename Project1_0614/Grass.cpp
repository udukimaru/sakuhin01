#include "Grass.h"

DirectX::XMFLOAT4X4 m_mtx;


void Grass::Init()
{
	

	// モデルの読み込みm
	bool sts = m_model.Init(
		"assets/texture/poke.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/ps.hlsl",			// ピクセルシェーダー
		"assets/texture/");			// テクスチャの格納フォル

	// 行列初期化
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
