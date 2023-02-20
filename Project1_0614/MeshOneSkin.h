#pragma once
#include	<d3d11.h>
#include	<directxmath.h>
#include	<vector>

struct VertexOneSkin
{
	DirectX::XMFLOAT3 m_Pos;	// �ʒu
	DirectX::XMFLOAT3 m_Normal;	// �@��
	DirectX::XMFLOAT2 m_Tex;	// UV���W
	int32_t	m_BoneIndex[4];	//�{�[���C���f�b�N�X
	float	m_BoneWeight[4];// �E�F�C�g�l
	int32_t	m_BoneNum;		// �{�[����
};

class MeshOneSkin
{
public:
	MeshOneSkin(std::vector<VertexOneSkin> vertices, std::vector<unsigned int> indices);

public:
	void Uninit(); // �㏈��
	void Draw(ID3D11DeviceContext* devcon);

private:
	bool InitBuffers(); // �o�b�t�@������

private:
	std::vector<VertexOneSkin> m_vertices;			// ���_�f�[�^
	std::vector<unsigned int> m_indices;

private:
	ID3D11Buffer* m_VertexBuffer;			// ���_�o�b�t�@
	ID3D11Buffer* m_IndexBuffer;
};