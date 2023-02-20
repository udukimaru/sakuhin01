#pragma once
#include "GameObject.h"
#include "CMonsterMgr.h"
#include "dx11mathutil.h"
//
//
//   敵キャラクターの動き。視界範囲や移動範囲など
// 　各Enemyにこの関数？を持たせるようにする
//
//

	struct Action {
		bool isActive;
		int id;
		float time;
		CMonsterMgr* pOwner;
	};

	//enum class Skill_ID {
	//	TACKLE,            // たいあたり
	//	WATERGUN,          // みずでっぽう
	//	FLAME,             // かえんほうしゃ
	//	LEAFCUTTER,        // はっぱカッター
	//	TELEKINESIS,       // ねんりき
	//	SHADOWBALL,        // シャドーボール
	//};

class CActor
{

public:

	enum class MONSTER_STATE {
		IDLE,
		SEARCH,
		WALK,
		RUN,
		SLEEP,
	};

	enum class SightRange { // 視界範囲の種類
		SMALL,
		LEARGE,
	};



	enum class Skill_TYPE { // モンスターのタイプ
		NORMAL,
		FIRE,
		WATER,
		GRASS,
		ESPER,
		GHOST,
	};

//==============================================================================
//! @fn     GetPlanefromProjectionmatrixWithNormalize
//! @brief  プロジェクション変換行列からフラスタムの６平面を取り出す(正規化行う)
//! @param　平面の方程式
//! @param　ビュー変換行列＊プロジェクション変換行列
//==============================================================================
	void GetPlanefromProjectionmatrixWithNormalize(PLANE* p, const XMFLOAT4X4& matrix) {
		// left
		p[0].a = matrix._14 + matrix._11;
		p[0].b = matrix._24 + matrix._21;
		p[0].c = matrix._34 + matrix._31;
		p[0].d = matrix._44 + matrix._41;

		// right
		p[1].a = matrix._14 - matrix._11;
		p[1].b = matrix._24 - matrix._21;
		p[1].c = matrix._34 - matrix._31;
		p[1].d = matrix._44 - matrix._41;

		// bottom
		p[2].a = matrix._14 + matrix._12;
		p[2].b = matrix._24 + matrix._22;
		p[2].c = matrix._34 + matrix._32;
		p[2].d = matrix._44 + matrix._42;
		// top
		p[3].a = matrix._14 - matrix._12;
		p[3].b = matrix._24 - matrix._22;
		p[3].c = matrix._34 - matrix._32;
		p[3].d = matrix._44 - matrix._42;

		// near
		p[4].a = matrix._13;
		p[4].b = matrix._23;
		p[4].c = matrix._33;
		p[4].d = matrix._43;

		// far
		p[5].a = matrix._14 - matrix._13;
		p[5].b = matrix._24 - matrix._23;
		p[5].c = matrix._34 - matrix._33;
		p[5].d = matrix._44 - matrix._43;

		float length;

		// 正規化
		for (int i = 0; i < 6; i++) {
			length = sqrtf(p[i].a * p[i].a + p[i].b * p[i].b + p[i].c * p[i].c);

			p[i].a = p[i].a / length;
			p[i].b = p[i].b / length;
			p[i].c = p[i].c / length;
			p[i].d = p[i].d / length;
		}
	}


//==============================================================================
//! @fn     IsInFrustum
//! @brief  フラスタム内かどうかをチェック
//! @param  位置座標（ワールド）　　	　	
//! @param  ビュー変換行列＊プロジェクション変換行列
//! @retval true フラスタム内　false フラスタム外
//==============================================================================

	bool IsInFrustum(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT4X4& matrix) {
		PLANE plane[6]{};
		GetPlanefromProjectionmatrixWithNormalize(plane, matrix);

		for (int i = 0; i < 6; i++) {
			float ans=plane[i].a*pos.x+plane[i].b*pos.y+ plane[i].c * pos.z + plane[i].d;
			if (ans < 0) {
				return false;
			}
		}
		return true;
	}

	bool CheckInSight(SightRange range); // 視界範囲にいるかどうか(視界範囲の種類)

	void AttackUpdate(Action* pThis, Skill_ID id);


	static CActor* GetInstance() {
		static CActor Instance;
		return &Instance;
	}

private:
	SightRange range_id;
	Skill_ID   skill_id;
};

