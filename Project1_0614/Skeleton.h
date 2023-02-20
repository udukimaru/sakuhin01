#pragma once
#include "Bone.h"
#include <d3d11.h>
struct aiNode;

// �X�P���g���i���̏W���́j
class Skeleton
{
public:
	bool Load(AssimpScene* assimpScene);

	void CalcBonesMatrix(
		const std::vector<DirectX::XMFLOAT4X4>& animationMatrix,
		int index,
		DirectX::XMFLOAT4X4 parentMatrix,
		std::vector<DirectX::XMFLOAT4X4>& outputMatrix);

public:
	// �Q�b�^�[�Z�b�^�[
	Bone* GetRootBone();
	Bone* GetBoneByIndex(int index);
	int GetBoneNum() const;

public:
	// �����ł���{�[���̍ő吔
	static constexpr unsigned int MAX_BONE_NUM = 400;

public:
	static void InitConstantBufferBoneMatrix(ID3D11Device* device);
	static void UninitConstantBufferBoneMatrix();
	static void UpdateConstantBufferBoneMatrix(const std::vector<DirectX::XMFLOAT4X4>& matrix);

private:

	// �{�[���𐶐�
	void CreateBones(AssimpScene* assimpScene, aiNode* node, int parentIndex);

	// �{�[���̐e�q�֌W���`��
	void CreateBoneTree();

	// �{�[���I�t�Z�b�g�s�񏉊���
	void InitBonesOffsetMatrix(AssimpScene* assimpScene);

private:
	std::vector<Bone> m_bones;	// �{�[���z��
	Bone* m_rootBone;			// ���[�g�ƂȂ�{�[��
	bool m_isLoad = false;		// �������������ǂ���

private:
	static ID3D11Buffer* m_constantbufferbonematrix;	// �{�[���s��i�[�p�萔�o�b�t�@
};

// �{�[���s��i�[�p�̃R���X�^���g�o�b�t�@
struct ConstantBufferBoneMtx
{
	DirectX::XMFLOAT4X4  mBoneMatrix[Skeleton::MAX_BONE_NUM];
};