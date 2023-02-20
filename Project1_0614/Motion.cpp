#include "Motion.h"
#include "Animation.h"
#include "Skeleton.h"

void Motion::CalcAnimationMatrix(
	Animation* animation,
	std::vector<DirectX::XMFLOAT4X4>& outputMatrix)
{
	// �A�j���[�V�����s��p�z�񏉊���
	const int boneNum = animation->GetSkeleton()->GetBoneNum();
	outputMatrix.clear();
	outputMatrix.resize(boneNum);

	std::vector<BoneTransform> outputTransforms;
	CalcAnimationTransforms(outputTransforms, animation);

	// �e�{�[�����ƂɃA�j���[�V�����s������߂�
	for (int boneIndex = 0; boneIndex < boneNum; boneIndex++)
	{
		outputMatrix[boneIndex] = outputTransforms[boneIndex].GetMatrix();
	}
}

std::string Motion::GetName() const
{
	return this->m_name;
}

void Motion::SetName(std::string name)
{
	this->m_name = name;
}

bool Motion::GetIsLoop() const
{
	return this->m_isLoop;
}