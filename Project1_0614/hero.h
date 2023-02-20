#pragma once
#include	"gameobject.h"
#include	"CModel.h"
#include	"dx11mathutil.h"

class Hero :public GameObject {
public:
	// オブジェクト名
	enum HEROPARTS {
		HIP,		// 腰
		BODY,		// 体
		HEAD,		// 頭
		ARMR0,		// 右腕０
		ARML0,		// 左腕０
		LEGR0,		// 右足０
		LEGL0,		// 左足０
		ARMR1, 		// 右腕１
		ARML1, 		// 左腕１
		LEGR1,		// 右足１
		LEGL1,		// 左足１
		BLADE,		// 刀
		NONE,		// なし
		END,		// データなし
		PARTSMAX
	};

	// 構造体型タグ
	struct	HeroInitData {
		Hero::HEROPARTS	ParentObjectNo;				// 親オブジェクトＮｏ
		Hero::HEROPARTS	ModelNo;					// モデル番号
		DirectX::XMFLOAT3	FirstPosition;				// 最初の位置
		DirectX::XMFLOAT3	FirstAngle;					// 最初の角度
	};

	// タンクのモデル名リスト
	struct	HeroModelData {
		Hero::HEROPARTS	ModelNo;					// モデル番号
		const char*		XfileName;					// Ｘファイル名
	};

	// 初期配置データ
	static HeroInitData	ObjectInitData[];

	// モデルファイル名リスト
	static HeroModelData			XFileData[];

	// モデルセット
	void SetModel(CModel* p,int idx) {
		m_models[idx] = p;
	}

	bool Init();
	void Draw();
	void Update();
	void Finalize();

	void UpdateLocalpose();									// ローカルポーズを更新する
	void CaliculateParentChildMtx();						// 親子関係を考慮した行列を作成

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
	static bool m_modelloadflag;							// モデルを読み込んだかどうか
	CModel*		m_models[HEROPARTS::PARTSMAX];
	DirectX::XMFLOAT4X4			m_mtxlocalpose[HEROPARTS::PARTSMAX];	// 自分のことだけを考えた行列
	DirectX::XMFLOAT4X4			m_mtxParentChild[HEROPARTS::PARTSMAX];	// 親子関係を考慮した行列

	float						m_speed = 0.0f;				// スピード
	DirectX::XMFLOAT3			m_angle;					// 回転角
};