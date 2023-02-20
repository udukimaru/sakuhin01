#include "MeshOneSkin.h"
#include "Shader.h"
#include "CDirectxGraphics.h"
MeshOneSkin::MeshOneSkin(std::vector<VertexOneSkin> vertices, std::vector<unsigned int> indices)
{
	this->m_vertices = vertices;
	this->m_indices = indices;

	InitBuffers();
}

void MeshOneSkin::Uninit()
{
	if (this->m_VertexBuffer == nullptr)
	{
		this->m_VertexBuffer->Release();
		this->m_VertexBuffer = nullptr;
	}

	if (this->m_IndexBuffer == nullptr)
	{
		this->m_IndexBuffer->Release();
		this->m_IndexBuffer = nullptr;
	}
}

void MeshOneSkin::Draw(ID3D11DeviceContext* devcon)
{
	unsigned int stride = sizeof(VertexOneSkin);
	unsigned int offset = 0;
	// ���_�o�b�t�@���Z�b�g
	devcon->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcon->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// �g�|���W�[���Z�b�g
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �C���f�b�N�X�o�b�t�@�𗘗p���ĕ`��
	devcon->DrawIndexed(static_cast<unsigned int>(m_indices.size()), 0, 0);
}

bool MeshOneSkin::InitBuffers()
{
	ID3D11Device* dev;
	dev = CDirectXGraphics::GetInstance()->GetDXDevice();

	// ���_�o�b�t�@����
	bool sts = CreateVertexBufferWrite(dev,
		static_cast<unsigned int>(sizeof(VertexOneSkin)),			// �X�g���C�h
		static_cast<unsigned int>(this->m_vertices.size()),		// ���_��
		this->m_vertices.data(),									// ���_�f�[�^
		&this->m_VertexBuffer);
	if (!sts) {
		return false;
	}

	// �C���f�b�N�X�o�b�t�@����
	sts = CreateIndexBuffer(dev,
		static_cast<unsigned int>(this->m_indices.size()),
		this->m_indices.data(),
		&this->m_IndexBuffer);
	if (!sts) {
		return false;
	}
	return true;
}