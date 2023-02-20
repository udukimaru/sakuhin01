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

	// ���ʂ�`�悷��
	ComPtr<ID3D11Buffer> m_pVertexBuffer;         //���_�o�b�t�@
	ComPtr<ID3D11Buffer> m_pIndexBuffer;          //�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D11VertexShader> m_pVertexShader;   //���_�V�F�[�_�[
	ComPtr<ID3D11PixelShader> m_pPixelShader;     //�s�N�Z���V�F�[�_�[
	ComPtr<ID3D11InputLayout> m_pVertexLayout;    //���_���C�A�E�g

	// �}�b�v�ݒu
	int m_map[MAPSIZEZ][MAPSIZEX] = {
		// -4- -3 -2 -1 0 1 2 3 4
		0,
	};

	// ���ʃ`�b�v
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
	// �R�s�[�E����͋֎~���邪�A���[�u�͋�����
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;

	//�f�t�H���g
	Stage(Stage&&) = default;
	Stage() = default;
	Stage& operator=(Stage&&) = default;

	bool Create();     //����
	void Destroy();    //�j��
	bool Init();       //��������
	void Update();     //�X�V
	//int GetMapChipNo(int x, int y, int z);
	//int GetMapChipNo(int x, int y);
	void Draw();       //�`��
	void Finalize();   //�I������
};