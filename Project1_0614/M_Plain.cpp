#include "M_Plain.h"
#include "drawaxis.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// モデルを読み込んだかどうか
bool M_Plain::m_modelloadflag = false;

bool M_Plain::Init()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

    m_actionKeepTime = 100;

	// モデルの読み込み
	bool sts = m_model[0].Init(
		"assets/plain/cover.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/ps.hlsl",			// ピクセルシェーダー
		"assets/plain/");	// テクスチャの格納フォルダ

	// モデルの読み込み
	 sts = m_model[1].Init(
		"assets/plain/face.obj",	// ファイル名 
		"shader/vs.hlsl",			// 頂点シェーダー
		"shader/ps.hlsl",			// ピクセルシェーダー
		"assets/plain/");	// テクスチャの格納フォルダ

     // モデルの読み込み
     sts = m_model[2].Init(
         "assets/plain/core.obj",	// ファイル名 
         "shader/vs.hlsl",			// 頂点シェーダー
         "shader/ps.hlsl",			// ピクセルシェーダー
         "assets/plain/");	// テクスチャの格納フォルダ

     // モデルの読み込み
     sts = m_model[3].Init(
         "assets/plain/left_arm.obj",	// ファイル名 
         "shader/vs.hlsl",			// 頂点シェーダー
         "shader/ps.hlsl",			// ピクセルシェーダー
         "assets/plain/");	// テクスチャの格納フォルダ

      // モデルの読み込み
     sts = m_model[4].Init(
         "assets/plain/right_arm.obj",	// ファイル名 
         "shader/vs.hlsl",			// 頂点シェーダー
         "shader/ps.hlsl",			// ピクセルシェーダー
         "assets/plain/");	// テクスチャの格納フォルダ

	// 初期位置
	m_pos.x = 5;
	m_pos.y = 0;
	m_pos.z = 10;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	isActive = true;
    // シード値決定用乱数
    std::random_device rand_dev;
    // シード値セット
    m_mt.seed(rand_dev());
    m_mt2.seed(rand_dev());

	return sts;
}

void M_Plain::Update()
{    
	// 動きの処理を...
	XMFLOAT3 pos = {};
    XMFLOAT4 axisX;
    XMFLOAT4 axisY;
    XMFLOAT4 axisZ;

    Move();

    // X軸を取り出す
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

    XMFLOAT4 qt;

    // 行列からクオータニオン作成
    DX11GetQtfromMatrix(m_mtx, qt);

    XMFLOAT4 qtx, qty, qtz;

    // 指定軸回転のクオータニオン作成
    DX11QtRotationAxis(qtx, axisX, m_angle.x);
    DX11QtRotationAxis(qty, axisY, m_angle.y);
    DX11QtRotationAxis(qtz, axisZ, m_angle.z);
    // クオータニオン合成
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

    // Z軸を取り出す
    axisZ.x = m_mtx._31;
    axisZ.y = m_mtx._32;
    axisZ.z = m_mtx._33;
    axisZ.w = 0.0f;

    m_pos.x -= axisZ.x * m_speed;
    m_pos.y -= axisZ.y * m_speed;
    m_pos.z -= axisZ.z * m_speed;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;
}

void M_Plain::BattleUpdate()
{
   
    m_pos.z -= 0.3f;

    m_mtx._41 = m_pos.x;
    m_mtx._42 = m_pos.y;
    m_mtx._43 = m_pos.z;
}

void M_Plain::Move()
{
    // 乱数生成
    std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(M_Plain::ACTION::MAX_ACTION) - 1);
    std::uniform_int_distribution<int32_t> rand10(10, 50);

    // 回転角をいったんリセット
    m_angle.x = m_angle.y = m_angle.z = 0.0f;

    // アクションにより回転角をセット
    switch (m_action)
    {
    case M_Plain::ACTION::ACT_STRAIGHT:
        m_angle.x = m_angle.y = m_angle.z = 0.0f;
        break;
    case M_Plain::ACTION::ACT_LEFT:
        m_angle.y = 1.1f;

        break;
    case M_Plain::ACTION::ACT_RIGHT:
        m_angle.y = -1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLP:
        m_angle.y = -1.1f;
        // partsangle[idx].y -= 1.0f;
        break;
    case M_Plain::ACTION::ACT_ROLLM:
        m_angle.y = 1.1f;
        //partsangle[idx].y += 1.0f;
        break;
    }
    // m_action = M_Plain::ACTION::ACT_LEFT;
      //カウンター減算
    if (--m_actionKeepTime <= 0) {
        // 乱数により次のアクションと持続時間を設定
        m_action = static_cast<ACTION>(rand4(m_mt));
        m_actionKeepTime = rand10(m_mt2);
    }
}

void M_Plain::Draw()
{
	// モデル描画
	m_model[1].Draw(m_mtx);
	m_model[0].Draw(m_mtx);
    m_model[2].Draw(m_mtx);
    m_model[3].Draw(m_mtx);
    m_model[4].Draw(m_mtx);
}

void M_Plain::Finalize()
{
    m_model->Uninit();
}

int M_Plain::AttackDamage()
{
    //int damage;
    std::random_device rand_dev;
    std::mt19937 m_mt(rand_dev());
    std::uniform_int_distribution<> rand100(10, 15);
    attack_power = rand100(m_mt);
    printf("敵攻撃力%d\n", attack_power);

    return attack_power;
}