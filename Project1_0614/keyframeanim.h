#pragma once
#include	<d3d11.h>
#include	<vector>
#include	<DirectXMath.h>
#include	<vector>

class	KeyFrameAnim {
private:
	unsigned int		m_frameno=0;		// フレーム番号
	std::vector<DirectX::XMFLOAT4> m_qt;	// クオータニオン（姿勢）
	std::vector<DirectX::XMFLOAT3> m_pos;	// 位置
	unsigned int		m_partsnum=0;		// パーツ総数
public:
	// 初期処理
	void Init(unsigned int partsnum) {
		m_qt.resize(partsnum);
		m_pos.resize(partsnum);
		m_partsnum = partsnum;
	}

	// 終了処理
	void Exit() {
		m_qt.clear();
		m_pos.clear();
	}

	// フレーム番号を取得
	unsigned int GetFrameNo() const{
		return m_frameno;
	}

	// 姿勢（クオータニオン）を取得
	DirectX::XMFLOAT4 GetQt(unsigned int partno) const{
		return m_qt[partno];
	}

	// 位置を取得
	DirectX::XMFLOAT3 GetPos(unsigned int partno) const{
		return m_pos[partno];
	}

	// パーツ数を取得
	unsigned int GetPartsNum() const {
		return m_partsnum;
	}

	// 姿勢（クオータニオン）をセット
	void SetQt(unsigned int partno, const DirectX::XMFLOAT4& qt) {
		m_qt[partno] = qt;
	}

	// 位置をセット
	void SetPos(unsigned int partno, const DirectX::XMFLOAT3& pos) {
		m_pos[partno] = pos;
	}

	// フレーム番号をセット
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
	// 終了処理
	void Exit();
	// パーツ総数をセットする
	void SetPartsNum(unsigned int partsnum);
	// 補間する
	void Interpolated(KeyFrameAnim* startkeyframe, KeyFrameAnim* endkeyframe, unsigned int frameno, KeyFrameAnim* nowkeyframe);
	// キーフレームをすべて削除する
	void Clear();
	void SetKeyFrame(unsigned int frameno, DirectX::XMFLOAT4X4* matrix);
	bool IsEnd(unsigned int frame);
	KeyFrameAnim* GetKeyFrame(unsigned int frameno);
	unsigned int GetKeyFrameNum();

	void Serilaize() {
		FILE* fp;
		fopen_s(&fp, "motion.txt", "w");
		fprintf_s(fp, "%d\n", m_partsnum);				// パーツ数

		fprintf_s(fp, "%zd\n", m_KeyFrameVector.size());	// キーフレーム数

		for (unsigned int i = 0; i < m_KeyFrameVector.size(); i++) {
			fprintf_s(fp, "%d\n", m_KeyFrameVector[i]->GetFrameNo());	// フレーム番号
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