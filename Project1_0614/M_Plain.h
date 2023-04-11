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
    bool   m_isinfrustum = true;		// �t���X�^�������ǂ���
    enum class ACTION {
        ACT_LEFT = 0,
        ACT_RIGHT,

        ACT_ROLLP,
        ACT_ROLLM,
        ACT_STRAIGHT,

        MAX_ACTION
    };

    enum class AI_MOVE {
        AI_INIT,

       AI_IDLE,         //�ҋ@
       AI_WANDERING,    //�p�j
       AI_SEARCH,       //���G
       AI_APPROACH,     //�ڋ�
       AI_ESCAPE,       //���S
       AI_DEAD,         //���S
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
 
    bool isActive = false;
    float HP = 87;
    float maxHP = 87;
    bool Init();        // ������
    void Update();      // �X�V����
    void Draw();        // �`��
    void Finalize();    // �I������

    void Move();

    int AttackDamage();

    void BattleUpdate();// �U����

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
   
private:
    static bool m_modelloadflag;
  
    XMFLOAT4X4      mySight;
    float			m_near = 3;
    float			m_Aspect=10;
    float			m_Fov= XM_PI / 5.0f;
    float			m_far = 10;
};

