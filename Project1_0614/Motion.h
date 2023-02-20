#pragma once
#include <string>
#include <vector>
#include <DirectXMath.h>
#include "BoneTransform.h"
#include "keyframe.h"
class Skeleton;
class Animation;

// �A�j���[�V�����̕�ԗp�̃f�[�^�\����
struct AnimationInterpolationInfo
{
	int keyIndex1;
	int keyIndex2;
	float InterpolationRate;
};

// ���[�V�����̊�b�N���X
class Motion
{
public:
	// �A�j���[�V�����s����v�Z
	void CalcAnimationMatrix(
		Animation* animation,
		std::vector<DirectX::XMFLOAT4X4>& outputMatrix);

	virtual float GetDuration(Animation* animation) abstract;

	virtual void CalcAnimationTransforms(
		std::vector<BoneTransform>& output,
		Animation* animation,
		float rate = 1.0f) abstract;

public:
	// �Q�b�^�[�Z�b�^�[
	std::string GetName() const;
	void SetName(std::string name);

	bool GetIsLoop() const;

private:
	std::string m_name;
	bool m_isLoop = true;	// ���[�v���邩�ǂ���
};

