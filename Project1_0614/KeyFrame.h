#pragma once
#include <DirectXMath.h>
#include <vector>

// �L�[�t���[��
struct KeyFrame
{
	DirectX::XMFLOAT4 rotation; // ��]
	DirectX::XMFLOAT3 position; // ���W
	bool shouldSlerpRotation;	// ��]���Ԃ���ׂ����ǂ���
	bool shouldLerpPosition;	// ���W���Ԃ���ׂ����ǂ���
};