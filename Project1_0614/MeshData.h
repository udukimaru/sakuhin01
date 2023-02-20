#pragma once
#include "MeshOneSkin.h"

class AssimpScene;
struct aiNode;
struct aiMesh;

// ���b�V���̃f�[�^�N���X
class MeshData
{
public:
	~MeshData();

public:
	void Load(AssimpScene* assimpScene); // �ǂݍ���
	void Unload();

	void Draw(ID3D11DeviceContext* devcon);

private:
	// �m�[�h���
	void ProcessNode(aiNode* node, AssimpScene* assimpScene);

	// ���b�V�����
	MeshOneSkin ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, int meshidx);

private:
	std::vector<MeshOneSkin> m_meshes; // ���b�V���z��
};

