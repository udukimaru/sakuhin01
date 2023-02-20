#include	<vector>
#include	"dx11mathutil.h"
#include	"keyframeanim.h"

// ��������
void KeyMotion::Init(unsigned int partsnum) {
	SetPartsNum(partsnum);
}

// �I������
void KeyMotion::Exit() {
	Clear();
}

// �p�[�c�������Z�b�g����
void KeyMotion::SetPartsNum(unsigned int partsnum) {
	m_partsnum = partsnum;
}

// ��Ԃ���
void KeyMotion::Interpolated(KeyFrameAnim* startkeyframe, KeyFrameAnim* endkeyframe,unsigned int frameno, KeyFrameAnim* nowkeyframe) {
	float rate;					// ����

	float framesu = static_cast<float>((endkeyframe->GetFrameNo() - startkeyframe->GetFrameNo() + 1));
	float nowframe = static_cast<float>(frameno - startkeyframe->GetFrameNo());

	// �������v�Z
	rate = nowframe/framesu;

	// �L�[�t���[���쐬
	for (unsigned int i = 0; i < nowkeyframe->GetPartsNum(); i++) {
		DirectX::XMFLOAT4 q;		// �N�I�[�^�j�I��
		DirectX::XMFLOAT3 pos;		// �ʒu

		// �X���[�v���
//		D3DXQuaternionSlerp(&q, 
//			&startkeyframe->GetQt(i), 
//			&endkeyframe->GetQt(i), rate);	

		DX11QtSlerp(startkeyframe->GetQt(i), endkeyframe->GetQt(i), rate, q);

		// �N�I�[�^�j�I�����Z�b�g
		nowkeyframe->SetQt(i, q);
		
		// �ʒu�̐��`���
		DirectX::XMFLOAT3 startpos;
		DirectX::XMFLOAT3 endpos;
		startpos = startkeyframe->GetPos(i);
		endpos = endkeyframe->GetPos(i);

		pos.x = startpos.x + (endpos.x - startpos.x) * rate;
		pos.y = startpos.y + (endpos.y - startpos.y) * rate;
		pos.z = startpos.z + (endpos.z - startpos.z) * rate;

		// �ʒu���Z�b�g
		nowkeyframe->SetPos(i, pos);
	}
	// �t���[���ԍ��Z�b�g
	nowkeyframe->SetFramNo(frameno);
}

// �L�[�t���[�������ׂč폜����
void KeyMotion::Clear() {
	std::vector<KeyFrameAnim*>::iterator	it;

	for (it = m_KeyFrameVector.begin(); it != m_KeyFrameVector.end();) {
		delete *it;
		it = m_KeyFrameVector.erase(it);
		continue;
	}
}

// �L�[�t���[�����Z�b�g����
void KeyMotion::SetKeyFrame(unsigned int frameno, DirectX::XMFLOAT4X4* matrix) {
	KeyFrameAnim*	kf;
	DirectX::XMFLOAT4 q;
	DirectX::XMFLOAT3 pos;

	kf = new KeyFrameAnim();
	kf->Init(m_partsnum);

	kf->SetFramNo(frameno);				// �t���[���ԍ��Z�b�g

	for (unsigned int i = 0; i < m_partsnum; i++) {
		DX11GetQtfromMatrix(matrix[i], q);		// �s�񂩂�N�I�[�^�j�I�������

		kf->SetQt(i, q);

		pos.x = matrix[i]._41;
		pos.y = matrix[i]._42;
		pos.z = matrix[i]._43;
		kf->SetPos(i, pos);
	}

	m_KeyFrameVector.push_back(kf);				// �L�[�t���[���ۑ�
}

// ���[�V�����I����?
bool KeyMotion::IsEnd(unsigned int frame) {

	if (frame > m_KeyFrameVector[m_KeyFrameVector.size() - 1]->GetFrameNo()) {
		return true;
	}
	return false;
}

// �t���[���ԍ��ɊY������L�[�t���[�����擾����
KeyFrameAnim* KeyMotion::GetKeyFrame(unsigned int frameno) {

	static KeyFrameAnim kframe;

	KeyFrameAnim* kf=nullptr;
	std::vector<KeyFrameAnim*>::iterator	it;
	KeyFrameAnim* oldkeyframe=nullptr;

	// �Y������L�[�t���[���ɑΉ������L�[�t���[������������
	for (it = m_KeyFrameVector.begin(); it != m_KeyFrameVector.end(); it++) {
		if ((*it)->GetFrameNo() >= frameno) {
			if ((*it)->GetFrameNo() == frameno){
				kf = *it;
			}
			else {
				kframe.Init(m_partsnum);
				// ��Ԃ��ăL�[�t���[�����v�Z
				Interpolated(oldkeyframe, (*it),frameno,&kframe);
				kf = &kframe;
			}
			break;
		}
		// �ЂƂO�̃L�[�t���[�������Z�[�u
		oldkeyframe = *it;
	}

	return kf;
}

// �L�[�t���[���������擾����
unsigned int KeyMotion::GetKeyFrameNum() {
	return static_cast<unsigned int>(m_KeyFrameVector.size());
}

void KeyMotion::LoadMotion() {

	Clear();

	FILE* fp;

	// ���[�V�����t�@�C�������݂��Ȃ������ꍇ
	errno_t sts = fopen_s(&fp, "motion.txt", "r");
	if (sts != 0) {
		return;
	}

	fscanf_s(fp, "%d", &m_partsnum);				// �p�[�c��

	unsigned int KeyFrameNum;
	fscanf_s(fp, "%d", &KeyFrameNum);	// �L�[�t���[����

	unsigned int frameno;

	for (unsigned int i = 0; i < KeyFrameNum; i++) {
		// �L�[�t���[���쐬
		KeyFrameAnim* kf = new KeyFrameAnim();
		kf->Init(m_partsnum);

		// �t���[���ԍ��Z�b�g
		fscanf_s(fp, "%d", &frameno);
		kf->SetFramNo(frameno);

		DirectX::XMFLOAT4 qt;
		DirectX::XMFLOAT3 pos;
		for (unsigned int j = 0; j < m_partsnum; j++) {
			fscanf_s(fp, "%f,%f,%f,%f", &qt.x, &qt.y, &qt.z, &qt.w);
			kf->SetQt(j, qt);
			fscanf_s(fp, "%f,%f,%f", &pos.x, &pos.y, &pos.z);
			kf->SetPos(j, pos);
		}
		m_KeyFrameVector.push_back(kf);
	}
	fclose(fp);
}
