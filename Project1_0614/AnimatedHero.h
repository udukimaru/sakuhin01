#pragma once
#include	<directxmath.h>
#include	"CDirectInput.h"
#include	"M_Plain.h"
#include	"keyframeanim.h"

class AnimatedHero : public M_Plain {

private:
	KeyMotion				m_motion;				// モーション
	int					m_frameno = 0;			// フレーム番号
	int					m_motionframeno = 0;	// モーション再生フレーム番号	
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
		m_motionframeno = 0;		// モーション再生フレーム番号０
		m_frameno = 0;				// フレーム番号０
	}

	// キーフレームを編集し追加する
	void MotionEditUpdate() {

		// ローカルポーズを更新
		UpdateLocalpose();

		// 親子関係を考慮した行列を計算する
		CaliculateParentChildMtx();

		// キーフレームを保存
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_K)) {

			m_motion.SetKeyFrame(m_frameno, GetLocalPoseMtx());
			m_frameno += 10;
		}

		// キーフレームを保存
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_S)) {
			m_motion.Serilaize();
		}

		// モーションロード
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_L)) {
			m_motion.LoadMotion();
		}

		// 初期状態にする
		if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
			ClearMotion();
		}
	}

	// キーフレームアニメーション再生
	void MotionPlayUpdate() {

		KeyFrameAnim* currentframe;

		// モーションにキーフレームがないなら何もしない
		if (m_motion.GetKeyFrameNum() <= 0) {
			return;
		}

		// モーション終了か？
		if (m_motion.IsEnd(m_motionframeno)) {
			m_motionframeno = 0;
		}

		// 現在フレーム情報を取得
		currentframe = m_motion.GetKeyFrame(m_motionframeno);

		for (unsigned int i = 0; i < (M_No1_PARTS::PARTSMAX - 2); i++) {

			DirectX::XMFLOAT4X4 mtx;

			// クオータニオンから行列を作る
			DX11MtxFromQt(mtx, currentframe->GetQt(i));

			// 位置を取得
			DirectX::XMFLOAT3 pos = currentframe->GetPos(i);
			mtx._41 = pos.x;
			mtx._42 = pos.y;
			mtx._43 = pos.z;

			// ローカルポーズを表す行列をセットする
			SetLocalPoseMtx(i, mtx);
		}

		// 親子関係を考慮した行列を計算する
		CaliculateParentChildMtx();

		m_motionframeno++;
	}
};