#pragma once
#include    "CMonsterMgr.h"
#include	"CModel.h"
#include	"dx11mathutil.h"
#include	"CDirectInput.h"
#include <random> 
#include	<directxmath.h>
#include	"Memory.h"


class M_Plain :
    public CMonsterMgr
{
private:
    CModel m_model[5];
    float speed = 10;
    bool   m_isinfrustum = true;		// フラスタム内かどうか
    enum class ACTION {
        ACT_LEFT = 0,
        ACT_RIGHT,
        // ACT_UP,
        // ACT_DOWN,
        ACT_ROLLP,
        ACT_ROLLM,
        ACT_STRAIGHT,

        MAX_ACTION
    };

    enum class AI_MOVE {
        AI_INIT,
       // ACT_UP,
       // ACT_DOWN,
       AI_IDLE,         //待機
       AI_WANDERING,    //徘徊
       AI_SEARCH,       //索敵
       AI_APPROACH,     //接近
       AI_ESCAPE,       //逃亡
       AI_DEAD,         //死亡
       MAX_ACTION
    };

    float m_speed = 0.01f;
    XMFLOAT3 m_angle;
    std::mt19937 m_mt;
    std::mt19937 m_mt2;
    ACTION m_action;
    AI_MOVE state;
    unsigned int m_actionKeepTime;
public:

    // オブジェクト名
    enum M_No1_PARTS {
        FACE,  //顔
        COVER, //顔のまわりのやつ
        R_ARM, //右腕？
        L_ARM, //左腕？
        CORE,  //宝石

        END,
        NONE,
        PARTSMAX
    };

    // 構造体タグ
    struct InitData {
        M_No1_PARTS ParentObjectNo;
        M_No1_PARTS ModeNo;
        DirectX::XMFLOAT3 FirstPosition;
        DirectX::XMFLOAT3 FirstAngle;
    };

    // モデル名リスト
    struct M_No1_ModelData {
        M_No1_PARTS modelNo;
        const char* filename;
    };

    // 初期配置データ
    static InitData	ObjectInitData[];

    // モデルファイル名リスト
    static M_No1_ModelData	 FileData[];

    // モデルセット
    void SetModel(CModel* p, int idx) {
        m_models[idx] = p;
    }


    float HP = 87;
    float maxHP = 87;
    bool Init();

    void Draw();

    void DrawWithAxis();

    void test();
    void AIaction();
    void Update();
    void Update_test();

    int AttackDamage();
    //void CheckInSight(XMFLOAT3 pos, XMFLOAT4 mtx);
    void MosionUpdate();
    void BattleUpdate();
    void Finalize();

    void UpdateLocalpose();									// ローカルポーズを更新する
    void CaliculateParentChildMtx();						// 親子関係を考慮した行列を作成
    void InitalPose() {
        for (int i = 0; i < static_cast<int>(M_No1_PARTS::PARTSMAX) - 2; i++) {
            DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
        }
    }

    DirectX::XMFLOAT4X4* GetLocalPoseMtx() {
        return m_mtxlocalpose;
    }

    void SetLocalPoseMtx(int idx, DirectX::XMFLOAT4X4 mtx) {
        m_mtxlocalpose[idx] = mtx;
    }

    bool isActive = false;
    bool IsActive() {
        return isActive;
    }
    float GetSpeed() {
        return speed;
    }
    float GetHP() {
        return HP;
    }
    float GetMAXHP() {
        return maxHP;
    }
    void SetInFrustumn(bool flag) {
        m_isinfrustum = flag;
    }

    bool IsInFrustumn() {
        return m_isinfrustum;
    }

    XMFLOAT3 GetPosLocal() {
        for (int i = 0; i < static_cast<int>(M_No1_PARTS::PARTSMAX); i++) {
            return partstrans[i];
        }
    }

    const XMFLOAT4X4& GetSightMatrix() {
        return mySight;
    }
    void SetNear(float nearclip) {
        m_near = nearclip;
    }

    void SetFar(float farclip) {
        m_far = farclip;
    }

    void SetFov(float fov) {
        m_Fov = fov;
    }

    void SetAspect(float width, float height) {
        m_Aspect = width / height;
    }

    void SetProjection(float nearclip, float farclip, float fov, float width, float height) {
        SetNear(nearclip);
        SetFar(farclip);
        SetFov(fov);
        SetAspect(width, height);
        CreateInSight();
    }
    void CreateInSight() {

        ALIGN16 XMMATRIX projection;

        projection = XMMatrixPerspectiveFovLH(m_Fov, m_Aspect, m_near, m_far);

        XMStoreFloat4x4(&mySight, projection);

    }
private:
    static bool m_modelloadflag;
    CModel* m_models[M_No1_PARTS::PARTSMAX];
    DirectX::XMFLOAT4X4			m_mtxlocalpose[M_No1_PARTS::PARTSMAX];	// 自分のことだけを考えた行列
    DirectX::XMFLOAT4X4			m_mtxParentChild[M_No1_PARTS::PARTSMAX];	// 親子関係を考慮した行列
     // 各パーツの回転角度(前フレームからの変位量)
    XMFLOAT3			partsangle[static_cast<int>(M_No1_PARTS::PARTSMAX)];
    XMFLOAT3			partstrans[static_cast<int>(M_No1_PARTS::PARTSMAX)];



    XMFLOAT4X4      mySight;
    float			m_near = 3;
    float			m_Aspect=10;
    float			m_Fov= XM_PI / 5.0f;
    float			m_far = 10;
};

