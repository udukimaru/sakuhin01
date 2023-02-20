#pragma once
#include	<d3d11.h>
#include	<vector>
#include	<DirectXMath.h>
#include	<vector>

class	KeyFrameAnim {
private:
	unsigned int		m_frameno=0;		// �t���[���ԍ�
	std::vector<DirectX::XMFLOAT4> m_qt;	// �N�I�[�^�j�I���i�p���j
	std::vector<DirectX::XMFLOAT3> m_pos;	// �ʒu
	unsigned int		m_partsnum=0;		// �p�[�c����
public:
	// ��������
	void Init(unsigned int partsnum) {
		m_qt.resize(partsnum);
		m_pos.resize(partsnum);
		m_partsnum = partsnum;
	}

	// �I������
	void Exit() {
		m_qt.clear();
		m_pos.clear();
	}

	// �t���[���ԍ����擾
	unsigned int GetFrameNo() const{
		return m_frameno;
	}

	// �p���i�N�I�[�^�j�I���j���擾
	DirectX::XMFLOAT4 GetQt(unsigned int partno) const{
		return m_qt[partno];
	}

	// �ʒu���擾
	DirectX::XMFLOAT3 GetPos(unsigned int partno) const{
		return m_pos[partno];
	}

	// �p�[�c�����擾
	unsigned int GetPartsNum() const {
		return m_partsnum;
	}

	// �p���i�N�I�[�^�j�I���j���Z�b�g
	void SetQt(unsigned int partno, const DirectX::XMFLOAT4& qt) {
		m_qt[partno] = qt;
	}

	// �ʒu���Z�b�g
	void SetPos(unsigned int partno, const DirectX::XMFLOAT3& pos) {
		m_pos[partno] = pos;
	}

	// �t���[���ԍ����Z�b�g
	void SetFramNo(unsigned int no) {
		m_frameno = no;
	}
};


class KeyMotion {
private:
	std::vector<KeyFrameAnim*>	m_KeyFrameVector;
	unsigned int m_partsnum = 0;
public:
	void Init(unsigned int partsnum);
	// �I������
	void Exit();
	// �p�[�c�������Z�b�g����
	void SetPartsNum(unsigned int partsnum);
	// ��Ԃ���
	void Interpolated(KeyFrameAnim* startkeyframe, KeyFrameAnim* endkeyframe, unsigned int frameno, KeyFrameAnim* nowkeyframe);
	// �L�[�t���[�������ׂč폜����
	void Clear();
	void SetKeyFrame(unsigned int frameno, DirectX::XMFLOAT4X4* matrix);
	bool IsEnd(unsigned int frame);
	KeyFrameAnim* GetKeyFrame(unsigned int frameno);
	unsigned int GetKeyFrameNum();

	void Serilaize() {
		FILE* fp;
		fopen_s(&fp, "motion.txt", "w");
		fprintf_s(fp, "%d\n", m_partsnum);				// �p�[�c��

		fprintf_s(fp, "%zd\n", m_KeyFrameVector.size());	// �L�[�t���[����

		for (unsigned int i = 0; i < m_KeyFrameVector.size(); i++) {
			fprintf_s(fp, "%d\n", m_KeyFrameVector[i]->GetFrameNo());	// �t���[���ԍ�
			for (unsigned int j = 0; j < m_partsnum; j++) {
				DirectX::XMFLOAT4 qt = m_KeyFrameVector[i]->GetQt(j);
				fprintf_s(fp, "%f,%f,%f,%f\n",qt.x,qt.y,qt.z,qt.w);	//  qt
				DirectX::XMFLOAT3 pos = m_KeyFrameVector[i]->GetPos(j);
				fprintf_s(fp, "%f,%f,%f\n", pos.x, pos.y, pos.z);	//  pos
			}
		}
		fclose(fp);
	}

	void LoadMotion();
};