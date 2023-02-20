#pragma once
#include	<directxmath.h>
#include	"CDirectInput.h"
#include	"M_Plain.h"
#include	"keyframeanim.h"

class AnimatedHero : public M_Plain {

private:
	KeyMotion				m_motion;				// ���[�V����
	int					m_frameno = 0;			// �t���[���ԍ�
	int					m_motionframeno = 0;	// ���[�V�����Đ��t���[���ԍ�	
public:
	virtual ~AnimatedHero() {

	}

	void Finalize() {
		m_motion.Exit();
	}

	int GetKeyframeNum() {
		return m_motion.GetKeyFrameNum();
	}

	void InitMotion() {
		m_motion.Init(M_No1_PARTS::PARTSMAX - 2);
	}

	void ClearMotion() {

		m_motion.Clear();
		m_motionframeno = 0;		// ���[�V�����Đ��t���[���ԍ��O
		m_frameno = 0;				// �t���[���ԍ��O
	}

	// �L�[�t���[����ҏW���ǉ�����
	void MotionEditUpdate() {

		// ���[�J���|�[�Y���X�V
		UpdateLocalpose();

		// �e�q�֌W���l�������s����v�Z����
		CaliculateParentChildMtx();

		// �L�[�t���[����ۑ�
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {

			m_motion.SetKeyFrame(m_frameno, GetLocalPoseMtx());
			m_frameno += 10;
		}

		// �L�[�t���[����ۑ�
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_S)) {
			m_motion.Serilaize();
		}

		// ���[�V�������[�h
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {
			m_motion.LoadMotion();
		}

		// ������Ԃɂ���
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
			ClearMotion();
		}
	}

	// �L�[�t���[���A�j���[�V�����Đ�
	void MotionPlayUpdate() {

		KeyFrameAnim* currentframe;

		// ���[�V�����ɃL�[�t���[�����Ȃ��Ȃ牽�����Ȃ�
		if (m_motion.GetKeyFrameNum() <= 0) {
			return;
		}

		// ���[�V�����I�����H
		if (m_motion.IsEnd(m_motionframeno)) {
			m_motionframeno = 0;
		}

		// ���݃t���[�������擾
		currentframe = m_motion.GetKeyFrame(m_motionframeno);

		for (unsigned int i = 0; i < (M_No1_PARTS::PARTSMAX - 2); i++) {

			DirectX::XMFLOAT4X4 mtx;

			// �N�I�[�^�j�I������s������
			DX11MtxFromQt(mtx, currentframe->GetQt(i));

			// �ʒu���擾
			DirectX::XMFLOAT3 pos = currentframe->GetPos(i);
			mtx._41 = pos.x;
			mtx._42 = pos.y;
			mtx._43 = pos.z;

			// ���[�J���|�[�Y��\���s����Z�b�g����
			SetLocalPoseMtx(i, mtx);
		}

		// �e�q�֌W���l�������s����v�Z����
		CaliculateParentChildMtx();

		m_motionframeno++;
	}
};