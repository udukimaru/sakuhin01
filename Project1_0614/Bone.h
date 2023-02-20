#pragma once
#include <vector>
#include <string>
#include <DirectXMath.h>

class AssimpScene;

// ��
class Bone
{
public:
	Bone();

public:
	void AddChild(Bone* bone);
	unsigned int GetChildCount() const;
	Bone* GetChild(int index);

public:
	// �Q�b�^�[�Z�b�^�[
	int GetBoneIndex() const;
	void SetBoneIndex(int index);

	int GetParentIndex() const;
	void SetParentIndex(int index);

	std::string GetName() const;
	void SetName(std::string name);

	DirectX::XMFLOAT4X4 GetOffsetMatrix() const;
	void SetOffsetMatrix(DirectX::XMFLOAT4X4 matrix);

public:
	// �{�[���̐e�����Ȃ��ꍇ�̃C���f�b�N�X
	static constexpr int NONE_PARENT = -1;

private:
	int m_parentIndex = NONE_PARENT;	// �e�̔ԍ�
	int m_boneIndex = -1;				// �����̔ԍ�
	std::string m_name;					// �{�[���̖��O
	std::vector<Bone*> m_children;		// �q���̃|�C���^

	DirectX::XMFLOAT4X4 m_offsetMatrix;	   // �I�t�Z�b�g�s��
};

