#include "CMonsterMgr.h"
#include "ModelMgr.h"
#include "dx11mathutil.h"

bool CMonsterMgr::Init()
{
    bool sts = true;

    // 行列初期化
    DX11MtxIdentity(m_mtx);
    //for (int i = 0; i < CMonsterMgr::MonsterList.size(); i++) {
    //// 行列初期化
    //DX11MtxIdentity(CMonsterMgr::MonsterList[i].mtx);

    //    sts = ModelMgr::GetInstance().LoadModel(
    //        CMonsterMgr::MonsterList[i].filename,
    //        "shader/vs.hlsl",			// 頂点シェーダー
    //        "shader/ps.hlsl",			// ピクセルシェーダー
    //        CMonsterMgr::MonsterList[i].texname);	// テクスチャの格納フォルダ      // ここも変える
    //    
    //}
    return sts;
}

bool CMonsterMgr::Init(bool group, XMFLOAT4X4 c_mtx)
{
    bool sts = true;
    enemy = group;

    //　敵ならば向きを+Z、味方（手持ち）なら-Z
    if (enemy == false)// 味方
    {
		XMFLOAT3 angle = { 0,180,0 };
		XMFLOAT4 axisX; //X軸
		XMFLOAT4 axisY; //Y軸
		XMFLOAT4 axisZ; //Z軸

		//　X軸を取り出す
		axisX.x = c_mtx._11;
		axisX.y = c_mtx._12;
		axisX.z = c_mtx._13;
		axisX.w = 0.0f;

		//　Y軸を取り出す
		axisY.x = c_mtx._21;
		axisY.y = c_mtx._22;
		axisY.z = c_mtx._23;
		axisY.w = 0.0f;

		//　Z軸を取り出す
		axisZ.x = c_mtx._31;
		axisZ.y = c_mtx._32;
		axisZ.z = c_mtx._33;
		axisZ.w = 0.0f;
		XMFLOAT4 qt;    // クオータニオン

		// 行列からクオータニオン作成
		DX11GetQtfromMatrix(c_mtx, qt);

		XMFLOAT4 qtx, qty, qtz; // クオータニオン

		// 指定軸回転のクオータニオンを生成
		DX11QtRotationAxis(qtx, axisX, angle.x);
		DX11QtRotationAxis(qty, axisY, angle.y);
		DX11QtRotationAxis(qtz, axisZ, angle.z);

		// クオータニオンを合成
		XMFLOAT4 tempqt1;
		DX11QtMul(tempqt1, qt, qtx);

		XMFLOAT4 tempqt2;
		DX11QtMul(tempqt2, qty, qtz);

		XMFLOAT4 tempqt3;
		DX11QtMul(tempqt3, tempqt1, tempqt2);

		// クオータニオンをノーマライズ
		DX11QtNormalize(tempqt3, tempqt3);

		// クオータニオンから行列作成
		DX11MtxFromQt(c_mtx, tempqt3);


		c_mtx._41 = m_pos.x;
		c_mtx._42 = m_pos.y;
		c_mtx._43 = m_pos.z;
    }
	DX11MtxIdentity(c_mtx);
    return sts;
}

void CMonsterMgr::Draw()
{
    //for (int i = 0; i < CMonsterMgr::MonsterList.size(); i++) {
        // モデル描画
        m_models->Draw(m_mtx);
    //}
}

void CMonsterMgr::Draw(DirectX::XMFLOAT4X4 mtx)
{
    m_models->Draw(mtx);
}

//void CMonsterMgr::ActionUpdate(CMonsterMgr* pThis, Skill_ID id)
//{
//   
//}

void CMonsterMgr::BattleUpdate()
{
}

void CMonsterMgr::Update()
{
}

void CMonsterMgr::Finalize()
{
}
