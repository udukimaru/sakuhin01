#pragma once
#include    "CMonsterMgr.h"
#include	"CModel.h"
#include	"dx11mathutil.h"
#include	"CDirectInput.h"

//
//
//   ‰¼
//
//
class M_Dog :
    public CMonsterMgr
{
private:
    CModel m_model;
    bool isActive = false;
    float speed = 15;
    bool enemy = false;
public:
    bool Init();
    bool Init(bool group, XMFLOAT4X4 c_mtx);
    void Draw();

    void DrawWithAxis();
    void BattleUpdate();
    void Update();
    int AttackDamage();
    int SpecialDamage();

    void Finalize();

    //int Attack();

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
    float HP = 90;
    float maxHP = 90;
};

