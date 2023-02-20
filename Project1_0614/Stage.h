#pragma once
#include  <wrl/client.h>
#include "vertexproto.h"
#include "dx11mathutil.h"
#include "DX11Settransform.h"
#include "DX11util.h"

using Microsoft::WRL::ComPtr;

class Stage {

	static constexpr float MAPCHIPWIDTH = 450.0f;
	static constexpr uint16_t MAPSIZEX = 1;
	static constexpr uint16_t MAPSIZEZ = 1;

	ComPtr<ID3D11ShaderResourceView> m_srv;
	ComPtr<ID3D11Resource> m_tex;

	// 平面を描画する
	ComPtr<ID3D11Buffer> m_pVertexBuffer;         //頂点バッファ
	ComPtr<ID3D11Buffer> m_pIndexBuffer;          //インデックスバッファ
	ComPtr<ID3D11VertexShader> m_pVertexShader;   //頂点シェーダー
	ComPtr<ID3D11PixelShader> m_pPixelShader;     //ピクセルシェーダー
	ComPtr<ID3D11InputLayout> m_pVertexLayout;    //頂点レイアウト

	// マップ設置
	int m_map[MAPSIZEZ][MAPSIZEX] = {
		// -4- -3 -2 -1 0 1 2 3 4
		0,
	};

	// 平面チップ
	Vertex m_v[4] = {
		{DirectX::XMFLOAT3(-MAPCHIPWIDTH / 2.0f,0,MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(1.0f,0.0f)},
		{DirectX::XMFLOAT3(MAPCHIPWIDTH / 2.0f,0,MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(1.0f,1.0f)},
		{DirectX::XMFLOAT3(-MAPCHIPWIDTH / 2.0f,0,-MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(0.0f,0.0f)},
		{DirectX::XMFLOAT3(MAPCHIPWIDTH / 2.0f,0,-MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(0.0f,1.0f)},
	};

	const char* m_texfilename =
	{
		"assets/stage/ground.jpg",
	};

	void ChipDraw(int z, int x);
public:
	// コピー・代入は禁止するが、ムーブは許可する
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;

	//デフォルト
	Stage(Stage&&) = default;
	Stage() = default;
	Stage& operator=(Stage&&) = default;

	bool Create();     //生成
	void Destroy();    //破棄
	bool Init();       //初期処理
	void Update();     //更新
	//int GetMapChipNo(int x, int y, int z);
	//int GetMapChipNo(int x, int y);
	void Draw();       //描画
	void Finalize();   //終了処理
};