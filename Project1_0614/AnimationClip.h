#pragma once
#include "Motion.h"

class AssimpScene;
class aiNodeAnim;

//�@�A�j���[�V�����N���b�v
class AnimationClip : public Motion
{
	friend class BlendAnimation;

public:
	// �A�j���[�V�����ǂݍ���
	bool Load(AssimpScene* assimpScene, unsigned int animationIndex);

	virtual float GetDuration(Animation* animation) override;
	float GetDuration() const;

	// �A�j���[�V�����̎p�������߂�
	virtual void CalcAnimationTransforms(
		std::vector<BoneTransform>& output,
		Animation* animationo,
		float rate) override;

public:
	bool GetIsLoad() const;
	float GetKeyFrameDuration() const;
	KeyFrame GetKeyFrame(int boneIndex, int frameIndex) const;
	int GetKeyFrameNum(int boneIndex = 0) const;

	int GetBeginFrameOffset() const;
	void SetBeginFrameOffset(int offset);
	int GetEndFrameOffset() const;
	void SetEndFrameOffset(int offset);

private:
	void ResizeKeyFrames(const int boneNum); // �L�[�t���[���z��̃��������m��
	void InitPositionKeyFrame(aiNodeAnim* nodeAnim, const int boneIndex);
	void InitRotationKeyFrame(aiNodeAnim* nodeAnim, const int boneIndex);
	void InitLerpPositionKeyFrame(int boneIndex);
	void InitSlerpRotationKeyFrame(int boneIndex);

	// �A�j���[�V�����̕�ԗp�̏��擾
	void CalcAnimationInterpolationInfo(
		AnimationInterpolationInfo& output,
		float currentTime);

private:
	bool m_isLoad = false;		// �������������ǂ���
	float m_keyFrameDuration;	// �A�j���[�V�����̎���
	float m_TicksPerSecond;		// �A�j���[�V������1�t���[���̎���
	int m_beginFrameOffset = 0; // �n�܂�̃t���[���̃I�t�Z�b�g
	int m_endFrameOffset = 0;	// �I���̃t���[���̃I�t�Z�b�g
	std::vector<std::vector<KeyFrame>> m_boneKeyFrames;  // �L�[�t���[�����
};

