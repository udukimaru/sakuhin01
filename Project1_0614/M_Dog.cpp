#include "M_Dog.h"
#include "CPlayer.h"
#include "drawaxis.h"
#include "CMonsterMgr.h"
#include <random> 

CPlayer p;

bool M_Dog::Init()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	// モデルの読み込みm
	bool sts = m_model.Init(
		"assets/dog/dog2.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/ps.hlsl",			// ピクセルシェーダー
		"assets/dog/");	// テクスチャの格納フォルダ

	m_pos.x = 5;
	m_pos.y = 0;
	m_pos.z = -5;

	

	XMFLOAT3 angle = { 0,180,0 };
	XMFLOAT4 axisX; //X軸
	XMFLOAT4 axisY; //Y軸
	XMFLOAT4 axisZ; //Z軸

	//　X軸を取り出す
	axisX.x = m_mtx._11;
	axisX.y = m_mtx._12;
	axisX.z = m_mtx._13;
	axisX.w = 0.0f;

	//　Y軸を取り出す
	axisY.x = m_mtx._21;
	axisY.y = m_mtx._22;
	axisY.z = m_mtx._23;
	axisY.w = 0.0f;

	//　Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;
	XMFLOAT4 qt;    // クオータニオン

	// 行列からクオータニオン作成
	DX11GetQtfromMatrix(m_mtx, qt);

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
	DX11MtxFromQt(m_mtx, tempqt3);

	
	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	isActive = true;

	return sts;
}

bool M_Dog::Init(bool group, XMFLOAT4X4 c_mtx)
{
	m_mtx = c_mtx;
	CMonsterMgr::Init(group, c_mtx);
	return false;
}


void M_Dog::Update()
{
	//XMFLOAT3 angle;
	XMFLOAT3 angle = { 0,0,0 };
	bool keyinput = false;

	angle.x = angle.y = angle.z = 0.0f;


}

int M_Dog::AttackDamage()
{
	int damage;
	std::random_device rand_dev;
	std::mt19937 m_mt(rand_dev());
	std::uniform_int_distribution<> rand100(10, 15);
	damage = rand100(m_mt);
	printf("攻撃力%d\n", damage);

	return damage;
}

int M_Dog::SpecialDamage()
{
	int damage;
	std::random_device rand_dev;
	std::mt19937 m_mt(rand_dev());
	std::uniform_int_distribution<> rand100(40, 50);
	damage = rand100(m_mt);
	printf("攻撃力%d\n", damage);

	return damage;
}

void M_Dog::Draw()
{
	// モデル描画
	m_model.Draw(m_mtx);
}

void M_Dog::DrawWithAxis()
{
}
void M_Dog::BattleUpdate()
{
	m_pos.z += 0.5f;
	//if (m_pos.z >= 5) m_pos.z = 5.0f;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;


	//// ランダムで攻撃力決定
	//		// シード値決定用乱数
	//std::random_device rand_dev;
	//std::mt19937 m_mt(rand_dev());
	//std::uniform_int_distribution<> rand100(10, 15);
	//printf("%d\n", rand100(m_mt));


	//obj->HP -= rand100(m_mt);
	//size2.x = g_monster.HP / g_monster.GetMAXHP() * 1.0f;
	//posX2 = (1.0f - size2.x) / 4 * 1.0f;

	//printf("%f\n", g_monster.HP);
}
void M_Dog::Finalize()
{

}

//int CMonster2::Attack()
//{
//
//	return 0;
//}
