#include "MeshData.h"
#include "Assimpscene.h"
#include <assimp\scene.h>

MeshData::~MeshData()
{
	Unload();
}

void MeshData::Load(AssimpScene* assimpScene)
{
	aiNode* rootNode = assimpScene->GetScene()->mRootNode;
	ProcessNode(rootNode, assimpScene);
}

void MeshData::Unload()
{
	// ���b�V���̉��
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].Uninit();
	}
}

void MeshData::Draw(ID3D11DeviceContext* devcon)
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		// �萔�o�b�t�@�Z�b�g����
		m_meshes[i].Draw(devcon);
	}
}

void MeshData::ProcessNode(aiNode* node, AssimpScene* assimpScene)
{
	// �m�[�h���̃��b�V���̐������[�v����
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		int meshindex = node->mMeshes[i];			// �m�[�h��i�Ԗڃ��b�V���̃C���f�b�N�X���擾
		aiMesh* mesh = assimpScene->GetScene()->mMeshes[meshindex];	// �V�[�����烁�b�V���{�̂����o��

		m_meshes.push_back(this->ProcessMesh(mesh, assimpScene, meshindex));
	}

	// �q�m�[�h�ɂ��Ă����
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], assimpScene);
	}
}

MeshOneSkin MeshData::ProcessMesh(aiMesh* mesh, AssimpScene* assimpScene, int meshidx)
{
	std::vector<VertexOneSkin> vertices;			// ���_
	std::vector<unsigned int> indices;		// �ʂ̍\�����
	//std::vector<Texture> textures;			// �e�N�X�`��

	// ���_�����擾
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		VertexOneSkin vertex;

		vertex.m_Pos.x = mesh->mVertices[i].x;
		vertex.m_Pos.y = mesh->mVertices[i].y;
		vertex.m_Pos.z = mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
		if (mesh->HasNormals()) {
			vertex.m_Normal.x = mesh->mNormals[i].x;
			vertex.m_Normal.y = mesh->mNormals[i].y;
			vertex.m_Normal.z = mesh->mNormals[i].z;
		}
		else {
			vertex.m_Normal.x = 0.0f;
			vertex.m_Normal.y = 0.0f;
			vertex.m_Normal.z = 0.0f;
		}

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
		if (mesh->HasTextureCoords(0)) {
			vertex.m_Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.m_Tex.y = mesh->mTextureCoords[0][i].y;
		}

		vertex.m_BoneNum = 0;

		for (unsigned int b = 0; b < 4; b++)
		{
			vertex.m_BoneIndex[b] = -1;
			vertex.m_BoneWeight[b] = 0.0f;
		}

		vertices.push_back(vertex);
	}

	//�{�[���f�[�^������
	for (unsigned int b = 0; b < mesh->mNumBones; b++)
	{
		// ���b�V���Ɋ֘A�Â��Ă�{�[�������擾
		aiBone* bone = mesh->mBones[b];

		// �{�[���Ɋ֘A�Â��Ă��钸�_��I�Ѥ�E�F�C�g�l���Z�b�g����
		for (unsigned int widx = 0; widx < bone->mNumWeights; widx++)
		{
			aiVertexWeight weight = bone->mWeights[widx];

			unsigned int vidx = weight.mVertexId;			// ���̃E�G�C�g�Ɋ֘A�Â��Ă钸�_idx

			// ���b�V���̒��̉��Ԗڂ�
			vertices[vidx].m_BoneWeight[vertices[vidx].m_BoneNum] = weight.mWeight;

			// �Y������{�[�����̃C���f�b�N�X�l���Z�b�g
			vertices[vidx].m_BoneIndex[vertices[vidx].m_BoneNum] = assimpScene
				->GetBoneIndexByName(bone->mName.C_Str());

			vertices[vidx].m_BoneNum++;

			assert(vertices[vidx].m_BoneNum <= 4);
		}
	}

	//// �e�N�X�`�������擾����
	//if (mesh->mMaterialIndex >= 0)
	//{
	//	// ���̃��b�V���̃}�e���A���C���f�b�N�X�l���擾����
	//	int	mtrlidx = mesh->mMaterialIndex;

	//	// �V�[������}�e���A���f�[�^���擾����
	//	aiMaterial* material = scene->mMaterials[mtrlidx];

	//	// ���̃}�e���A���Ɋ֘A�Â����e�N�X�`�������o��
	//	std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);

	//	// ���̃��b�V���Ŏg�p���Ă���e�N�X�`����ۑ�
	//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//}

	// �ʂ̍\�������擾
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	return MeshOneSkin(vertices, indices);
}