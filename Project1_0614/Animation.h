#pragma once
#include <vector>
#include <DirectXMath.h>
class Motion;
class Skeleton;

// �A�j���[�V�������Đ�����N���X
class Animation
{
public:
	// ���[�V�����z��ɒǉ�
	void AddAnimationClips(Motion* motion);

	// �A�j���[�V�����X�V
	void UpdateAnimation(float dt);

	// �萔�o�b�t�@�X�V
	void UpdateConstantBufferBoneMatrix();

	// �A�j���[�V���������߂���Đ�
	void Play();
	void Play(int motionIndex);

public:
	// �Q�b�^�[�Z�b�^�[
	Skeleton* GetSkeleton();
	void SetSkeleton(Skeleton* skeleton);

	float GetMotionTime() const;
	void SetMotionTime(float time);

	int GetMotionIndex() const;
	void SetMotionIndex(int index);

	float GetMotionSpeed() const;
	void SetMotionSpeed(float speed);

	int GetMotionNum() const;

	float GetBlendParameter() const;
	void SetBlendParameter(float param);

private:
	std::vector<Motion*> m_animationClips;          // ���[�V�����̔z��
	std::vector<DirectX::XMFLOAT4X4> m_bonesMatrix; // �萔�o�b�t�@�ɓK�p����{�[�����
	Skeleton* m_skeleton;

private:
	float m_motionSpeed = 1.0f; // �Đ��X�s�[�h
	float m_motionTime = 0.0f;  // ���ݍĐ����̎���
	int m_motionIndex = 0;     // ���ݍĐ����̃��[�V�����ԍ�
	float m_blendParameter = 0.0f; // �u�����h�c���[�p�̃p�����[�^
};

