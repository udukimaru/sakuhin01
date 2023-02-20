#pragma once
#include <d3d11.h>

class Material_OneSkin
{
public:
	~Material_OneSkin();

public:
	bool LoadShader(const char* vsfile, const char* psfile);
	void Unload();

	// �V�F�[�_���Z�b�g����
	void SetShader();

private:
	ID3D11VertexShader* m_pVertexShader = nullptr;		// ���_�V�F�[�_�[���ꕨ
	ID3D11PixelShader* m_pPixelShader = nullptr;		// �s�N�Z���V�F�[�_�[���ꕨ
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// ���_�t�H�[�}�b�g��`
};

