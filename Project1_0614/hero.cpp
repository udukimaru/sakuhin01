#include	<random>
#include	"hero.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// 戦車の親子関係及び初期位置・初期角度を定義したデータ
Hero::HeroInitData	Hero::ObjectInitData[] = {
	//   親							モデル番号						初期位置				初期角度	// 注意：かならず子供より親が先にならぶこと
	{ HEROPARTS::NONE,	HEROPARTS::HIP,	{ 0.0f,   0.0f,	  0.0f },	{ 0,0,0 }	},			// 腰
	{ HEROPARTS::HIP,		HEROPARTS::BODY,	{ 0.0f,   0.8f,   -0.1f },	{ 0,0,0 }	},			// 体
	{ HEROPARTS::BODY,	HEROPARTS::HEAD,	{ 0.0f,   1.3f,   -0.1f },	{ 0,0,0 }	},			// 頭					
	{ HEROPARTS::BODY,	HEROPARTS::ARMR0,	{ -0.4f,  0.9f,    0.1f },	{ 0,0,0 }	},			// 右腕０
	{ HEROPARTS::BODY,	HEROPARTS::ARML0,	{ 0.4f,   0.9f,    0.1f },	{ 0,0,0 }	},			// 左腕０
	{ HEROPARTS::HIP,		HEROPARTS::LEGR0,	{ -0.4f, -0.3f,  -0.05f },	{ 0,0,0 }	},			// 右足０
	{ HEROPARTS::HIP,		HEROPARTS::LEGL0,	{ 0.4f,  -0.3f,  -0.05f },	{ 0,0,0 }	},			// 左足０
	{ HEROPARTS::ARMR0,	HEROPARTS::ARMR1,	{ -0.8f, -1.2f,   0.1f },	{ 0,0,0 }	},			// 右腕１
	{ HEROPARTS::ARML0,	HEROPARTS::ARML1,	{ 0.8f,  -1.2f,   0.1f },	{ 0,0,0 }	},			// 左腕１
	{ HEROPARTS::LEGR0,	HEROPARTS::LEGR1,	{ -0.3f, -1.9f,   0.05f },	{ 0,0,0 }	},			// 右足１
	{ HEROPARTS::LEGL0,	HEROPARTS::LEGL1,	{ 0.3f,  -1.9f,   0.05f },	{ 0,0,0 }	},			// 左足１
	{ HEROPARTS::ARMR1,	HEROPARTS::BLADE, { -0.4f, -1.3f,   -2.0f },	{ 90,30,90 }   },		// 刀
	{ HEROPARTS::END,		HEROPARTS::END,	{ 0.0f,   0.0f,   0.0f },	{ 0,0,0 }	}		// 終了
};

// モデルファイル名リスト
Hero::HeroModelData			Hero::XFileData[] = {
	{ HEROPARTS::HIP,  "assets/model/hero/c0_hip.x" },		// 腰
	{ HEROPARTS::BODY, "assets/model/hero/c0_body.x" },		// 体
	{ HEROPARTS::HEAD, "assets/model/hero/c0_head.x" },		// 頭
	{ HEROPARTS::ARMR0,"assets/model/hero/c0_armr0.x" },	// 右腕０
	{ HEROPARTS::ARML0,"assets/model/hero/c0_arml0.x" },	// 左腕０
	{ HEROPARTS::LEGR0,"assets/model/hero/c0_legr0.x" },	// 右足０
	{ HEROPARTS::LEGL0,"assets/model/hero/c0_legl0.x" },	// 左足０
	{ HEROPARTS::ARMR1,"assets/model/hero/c0_armr1.x" },	// 右腕１
	{ HEROPARTS::ARML1,"assets/model/hero/c0_arml1.x" },	// 左腕１
	{ HEROPARTS::LEGR1,"assets/model/hero/c0_legr1.x" },	// 右足１
	{ HEROPARTS::LEGL1,"assets/model/hero/c0_legl1.x" },	// 左足１
	{ HEROPARTS::BLADE,"assets/model/hero/c0_blade.x" },	// 剣
	{ HEROPARTS::END,nullptr }
};

// モデルを読み込んだかどうか
bool Hero::m_modelloadflag = false;

bool Hero::Init() {

	bool sts = true;

	// 行列初期化
	DX11MtxIdentity(m_mtx);	// モデルを読み込む

	// 読み込みが完了していなければ読み込む
	if (Hero::m_modelloadflag == false) {
		// モデル読み込み（HERO用）
		for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
			sts = ModelMgr::GetInstance().LoadModel(
				Hero::XFileData[i].XfileName,	// ファイル名 
				"shader/vs.hlsl",				// 頂点シェーダー
				"shader/ps.hlsl",				// ピクセルシェーダー
				"assets/model/hero/");				// テクスチャの格納フォルダ
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Hero::XFileData[i].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}
		}
		Hero::m_modelloadflag = true;
	}

	// モデルポインターをセット
	for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
		SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	}

	// プレイヤ行列初期化(初期位置)（自分のことだけを考えた行列を作成）
	for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
		DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	}

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();

	return sts;
}

void Hero::Draw() {

	// モデル描画
	drawaxis(m_mtx, 200, m_pos);

	for (int i = 0; i < static_cast<int>(Hero::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}
}

void Hero::UpdateLocalpose() {

	// 各パーツの回転角度(前フレームからの変位量)
	XMFLOAT3			partsangle[static_cast<int>(HEROPARTS::PARTSMAX)];
	XMFLOAT3			partstrans[static_cast<int>(HEROPARTS::PARTSMAX)];

	// どのパーツを動かすか
	static int idx = 0;
	bool	initflag = false;

	// 角度と移動量を初期化
	for (int i = 0; i < static_cast<int>(HEROPARTS::PARTSMAX); i++) {
		partsangle[i].x = 0.0f;
		partsangle[i].y = 0.0f;
		partsangle[i].z = 0.0f;
		partstrans[i].x = 0.0f;
		partstrans[i].y = 0.0f;
		partstrans[i].z = 0.0f;
	}

	// 動作パーツを切り替え
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_TAB)) {
		idx++;
		if (idx > static_cast<int>(HEROPARTS::PARTSMAX) - 3) {
			idx = 0;
		}
	}

	// パーツのローカルポーズを決める為のキー操作
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
		partsangle[idx].x += 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
		partsangle[idx].x -= 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
		partsangle[idx].y += 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
		partsangle[idx].y -= 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F1)) {
		partsangle[idx].z += 1.0f;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F2)) {
		partsangle[idx].z -= 1.0f;
	}

	// 初期状態にする
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
		initflag = true;
		idx = 0;
	}

	// 初期ポーズに戻す
	if (initflag) {
		InitalPose();
	}

	// パーツの角度ローカルポーズを表す行列を計算
	XMFLOAT4X4 partsmtx;
	DX11MakeWorldMatrix(partsmtx, partsangle[idx], partstrans[idx]);
	DX11MtxMultiply(m_mtxlocalpose[idx], partsmtx, m_mtxlocalpose[idx]);
}

// 更新
void Hero::Update() {

	XMFLOAT4 axisX;
	XMFLOAT4 axisY;
	XMFLOAT4 axisZ;

	static bool keyinput = true;

	//　本体の移動処理
	//  X軸を取り出す
	axisX.x = m_mtx._11;
	axisX.y = m_mtx._12;
	axisX.z = m_mtx._13;
	axisX.w = 0.0f;

	// Y軸を取り出す
	axisY.x = m_mtx._21;
	axisY.y = m_mtx._22;
	axisY.z = m_mtx._23;
	axisY.w = 0.0f;

	// Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// 移動量及び角度を０にする
	m_speed = 0.0f;
	m_angle.x = m_angle.y = m_angle.z = 0.0f;

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
		m_angle.y -= 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		m_angle.y += 1.0f;
		keyinput = true;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W)) {
		m_speed = 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S)) {
		m_speed = -1.0f;
		keyinput = true;
	}

	// キー入力があった場合
	if (keyinput) {
		XMFLOAT4 qt;	// クオータニオン

		// 行列からクオータニオンを生成
		DX11GetQtfromMatrix(m_mtx, qt);

		XMFLOAT4 qtx, qty, qtz;		// クオータニオン

		// 指定軸回転のクオータニオンを生成
		DX11QtRotationAxis(qtx, axisX, m_angle.x);
		DX11QtRotationAxis(qty, axisY, m_angle.y);
		DX11QtRotationAxis(qtz, axisZ, m_angle.z);

		// クオータニオンを合成
		XMFLOAT4 tempqt1;
		DX11QtMul(tempqt1, qt, qtx);

		XMFLOAT4 tempqt2;
		DX11QtMul(tempqt2, qty, qtz);

		XMFLOAT4 tempqt3;
		DX11QtMul(tempqt3, tempqt1, tempqt2);

		// クオータニオンをノーマライズ
		DX11QtNormalize(tempqt3, tempqt3);

		// クオータニオンから行列を作成
		DX11MtxFromQt(m_mtx, tempqt3);
	}

	// Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// 位置を更新
	m_pos.x += axisZ.x*m_speed;
	m_pos.y += axisZ.y*m_speed;
	m_pos.z += axisZ.z*m_speed;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;					
	m_mtx._43 = m_pos.z;

	// ローカルポーズを更新する
	UpdateLocalpose();

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();

	keyinput = false;
}

void Hero::Finalize() {

}

void Hero::CaliculateParentChildMtx() {

	// 一番の親のキャタピラに行列をセット
//	m_mtxlocalpose[TANK_CATERPILLAR] = m_mtx;

	// 親子関係を考慮した行列を作る
	for (int i = 0; i < static_cast<int>(HEROPARTS::PARTSMAX) - 2; i++) {
		m_mtxParentChild[i] = m_mtxlocalpose[i];
		for (int j = static_cast<int>(ObjectInitData[i].ParentObjectNo);
			j != static_cast<int>(HEROPARTS::NONE);
			j = static_cast<int>(ObjectInitData[j].ParentObjectNo)) {

			DX11MtxMultiply(m_mtxParentChild[i], m_mtxParentChild[i], m_mtxlocalpose[j]);
		}
	}
}