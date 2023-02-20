#include	<vector>
#include	"dx11mathutil.h"
#include	"keyframeanim.h"

// 初期処理
void KeyMotion::Init(unsigned int partsnum) {
	SetPartsNum(partsnum);
}

// 終了処理
void KeyMotion::Exit() {
	Clear();
}

// パーツ総数をセットする
void KeyMotion::SetPartsNum(unsigned int partsnum) {
	m_partsnum = partsnum;
}

// 補間する
void KeyMotion::Interpolated(KeyFrameAnim* startkeyframe, KeyFrameAnim* endkeyframe,unsigned int frameno, KeyFrameAnim* nowkeyframe) {
	float rate;					// 割合

	float framesu = static_cast<float>((endkeyframe->GetFrameNo() - startkeyframe->GetFrameNo() + 1));
	float nowframe = static_cast<float>(frameno - startkeyframe->GetFrameNo());

	// 割合を計算
	rate = nowframe/framesu;

	// キーフレーム作成
	for (unsigned int i = 0; i < nowkeyframe->GetPartsNum(); i++) {
		DirectX::XMFLOAT4 q;		// クオータニオン
		DirectX::XMFLOAT3 pos;		// 位置

		// スラープ補間
//		D3DXQuaternionSlerp(&q, 
//			&startkeyframe->GetQt(i), 
//			&endkeyframe->GetQt(i), rate);	

		DX11QtSlerp(startkeyframe->GetQt(i), endkeyframe->GetQt(i), rate, q);

		// クオータニオンをセット
		nowkeyframe->SetQt(i, q);
		
		// 位置の線形補間
		DirectX::XMFLOAT3 startpos;
		DirectX::XMFLOAT3 endpos;
		startpos = startkeyframe->GetPos(i);
		endpos = endkeyframe->GetPos(i);

		pos.x = startpos.x + (endpos.x - startpos.x) * rate;
		pos.y = startpos.y + (endpos.y - startpos.y) * rate;
		pos.z = startpos.z + (endpos.z - startpos.z) * rate;

		// 位置をセット
		nowkeyframe->SetPos(i, pos);
	}
	// フレーム番号セット
	nowkeyframe->SetFramNo(frameno);
}

// キーフレームをすべて削除する
void KeyMotion::Clear() {
	std::vector<KeyFrameAnim*>::iterator	it;

	for (it = m_KeyFrameVector.begin(); it != m_KeyFrameVector.end();) {
		delete *it;
		it = m_KeyFrameVector.erase(it);
		continue;
	}
}

// キーフレームをセットする
void KeyMotion::SetKeyFrame(unsigned int frameno, DirectX::XMFLOAT4X4* matrix) {
	KeyFrameAnim*	kf;
	DirectX::XMFLOAT4 q;
	DirectX::XMFLOAT3 pos;

	kf = new KeyFrameAnim();
	kf->Init(m_partsnum);

	kf->SetFramNo(frameno);				// フレーム番号セット

	for (unsigned int i = 0; i < m_partsnum; i++) {
		DX11GetQtfromMatrix(matrix[i], q);		// 行列からクオータニオンを作る

		kf->SetQt(i, q);

		pos.x = matrix[i]._41;
		pos.y = matrix[i]._42;
		pos.z = matrix[i]._43;
		kf->SetPos(i, pos);
	}

	m_KeyFrameVector.push_back(kf);				// キーフレーム保存
}

// モーション終了か?
bool KeyMotion::IsEnd(unsigned int frame) {

	if (frame > m_KeyFrameVector[m_KeyFrameVector.size() - 1]->GetFrameNo()) {
		return true;
	}
	return false;
}

// フレーム番号に該当するキーフレームを取得する
KeyFrameAnim* KeyMotion::GetKeyFrame(unsigned int frameno) {

	static KeyFrameAnim kframe;

	KeyFrameAnim* kf=nullptr;
	std::vector<KeyFrameAnim*>::iterator	it;
	KeyFrameAnim* oldkeyframe=nullptr;

	// 該当するキーフレームに対応したキーフレーム情報を見つける
	for (it = m_KeyFrameVector.begin(); it != m_KeyFrameVector.end(); it++) {
		if ((*it)->GetFrameNo() >= frameno) {
			if ((*it)->GetFrameNo() == frameno){
				kf = *it;
			}
			else {
				kframe.Init(m_partsnum);
				// 補間してキーフレームを計算
				Interpolated(oldkeyframe, (*it),frameno,&kframe);
				kf = &kframe;
			}
			break;
		}
		// ひとつ前のキーフレーム情報をセーブ
		oldkeyframe = *it;
	}

	return kf;
}

// キーフレーム総数を取得する
unsigned int KeyMotion::GetKeyFrameNum() {
	return static_cast<unsigned int>(m_KeyFrameVector.size());
}

void KeyMotion::LoadMotion() {

	Clear();

	FILE* fp;

	// モーションファイルが存在しなかった場合
	errno_t sts = fopen_s(&fp, "motion.txt", "r");
	if (sts != 0) {
		return;
	}

	fscanf_s(fp, "%d", &m_partsnum);				// パーツ数

	unsigned int KeyFrameNum;
	fscanf_s(fp, "%d", &KeyFrameNum);	// キーフレーム数

	unsigned int frameno;

	for (unsigned int i = 0; i < KeyFrameNum; i++) {
		// キーフレーム作成
		KeyFrameAnim* kf = new KeyFrameAnim();
		kf->Init(m_partsnum);

		// フレーム番号セット
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
