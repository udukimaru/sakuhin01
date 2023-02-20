#pragma once
#include	"gameobject.h"
#include	"CModel.h"
#include	"dx11mathutil.h"

class Hero :public GameObject {
public:
	// �I�u�W�F�N�g��
	enum HEROPARTS {
		HIP,		// ��
		BODY,		// ��
		HEAD,		// ��
		ARMR0,		// �E�r�O
		ARML0,		// ���r�O
		LEGR0,		// �E���O
		LEGL0,		// �����O
		ARMR1, 		// �E�r�P
		ARML1, 		// ���r�P
		LEGR1,		// �E���P
		LEGL1,		// �����P
		BLADE,		// ��
		NONE,		// �Ȃ�
		END,		// �f�[�^�Ȃ�
		PARTSMAX
	};

	// �\���̌^�^�O
	struct	HeroInitData {
		Hero::HEROPARTS	ParentObjectNo;				// �e�I�u�W�F�N�g�m��
		Hero::HEROPARTS	ModelNo;					// ���f���ԍ�
		DirectX::XMFLOAT3	FirstPosition;				// �ŏ��̈ʒu
		DirectX::XMFLOAT3	FirstAngle;					// �ŏ��̊p�x
	};

	// �^���N�̃��f�������X�g
	struct	HeroModelData {
		Hero::HEROPARTS	ModelNo;					// ���f���ԍ�
		const char*		XfileName;					// �w�t�@�C����
	};

	// �����z�u�f�[�^
	static HeroInitData	ObjectInitData[];

	// ���f���t�@�C�������X�g
	static HeroModelData			XFileData[];

	// ���f���Z�b�g
	void SetModel(CModel* p,int idx) {
		m_models[idx] = p;
	}

	bool Init();
	void Draw();
	void Update();
	void Finalize();

	void UpdateLocalpose();									// ���[�J���|�[�Y���X�V����
	void CaliculateParentChildMtx();						// �e�q�֌W���l�������s����쐬

	DirectX::XMFLOAT4X4 * GetLocalPoseMtx() {
		return m_mtxlocalpose;
	}

	void SetLocalPoseMtx(int idx, DirectX::XMFLOAT4X4 mtx) {
		m_mtxlocalpose[idx] = mtx;
	}

	void InitalPose() {
		for (int i = 0; i < static_cast<int>(HEROPARTS::PARTSMAX) - 2; i++) {
			DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
		}
	}

private:
	static bool m_modelloadflag;							// ���f����ǂݍ��񂾂��ǂ���
	CModel*		m_models[HEROPARTS::PARTSMAX];
	DirectX::XMFLOAT4X4			m_mtxlocalpose[HEROPARTS::PARTSMAX];	// �����̂��Ƃ������l�����s��
	DirectX::XMFLOAT4X4			m_mtxParentChild[HEROPARTS::PARTSMAX];	// �e�q�֌W���l�������s��

	float						m_speed = 0.0f;				// �X�s�[�h
	DirectX::XMFLOAT3			m_angle;					// ��]�p
};