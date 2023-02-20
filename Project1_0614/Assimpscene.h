#pragma once
#include <string>
#include <unordered_map>

struct aiScene;
struct aiNode;

class AssimpScene
{
public:
	// ��������
	bool Init(std::string filename);
	// �I������
	void Exit();

	// �V�[���擾
	const aiScene* GetScene() const;

	// �A�j���[�V�����������Ă��邩
	bool HasAnimation();

	// �A�j���[�V�����̐�
	unsigned int GetAnimationsNum() const;

	// ���O����{�[���̃C���f�b�N�X���擾����
	int GetBoneIndexByName(std::string name) const;

	// �{�[���̐����擾
	unsigned int GetBoneNum() const;

private:
	// �{�[���̖��O�ƃC���f�b�N�X���֘A�t����}�b�v�쐬
	void CreateBoneIndexMap(aiNode* node);

private:
	const aiScene* m_Scene = nullptr;	// assimp scene

	// �{�[���̖��O�ƃC���f�b�N�X���֘A�t����
	std::unordered_map<std::string, int> m_boneIndexMap;
};