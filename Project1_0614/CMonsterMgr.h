#pragma once
#include "GameObject.h"
#include "CModel.h"
#include <vector>

enum class TYPE
{
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ESPER,
    GHOST,

};

enum class Skill_ID {
    NONE,              // スキルなし
    TACKLE,            // たいあたり
    WATERGUN,          // みずでっぽう
    FLAME,             // かえんほうしゃ
    LEAFCUTTER,        // はっぱカッター
    TELEKINESIS,       // ねんりき
    SHADOWBALL,        // シャドーボール

    SPECIAL,           // スペシャル
};

class CMonsterMgr :public GameObject
{
protected:
    int No_num;
    const char* name;
    TYPE type1;
    TYPE type2;
    Skill_ID waza1;
    Skill_ID waza2;
    Skill_ID waza3;
    Skill_ID waza4;

    float attack_power;
    float defense_power;
    float speed;
    float HP;
    float maxHP;

    bool enemy;

private:
    CModel* m_models;
public:
    enum class MONSTER_ID {  // モンスターID
        NONE,
        PLAIN,
        DOG,
        MAX
    };

    enum class MONSTER_TYPE { // モンスターのタイプ
        NORMAL,
        FIRE,
        WATER,
        Grass,
        ESPER,
        Ghost,
    };

    struct ModelData {
        MONSTER_ID id;
        const char* filename;
        const char* texname;
        const char* vsfilename;
        const char* psfilename;

        bool isActive;
    };

    std::vector<ModelData> MonsterList = {
        {MONSTER_ID::PLAIN,"assets/texture/poke_hantoumei.obj","assets/texture/","shader/vs.hlsl","shader/ps.hlsl",true},
        {MONSTER_ID::PLAIN,"assets/texture/poke_hutoumei.obj","assets/texture/","shader/vs.hlsl","shader/ps.hlsl",true},
        {MONSTER_ID::DOG,"assets/dog/dog2.obj","assets/dog/","shader/vs.hlsl","shader/ps.hlsl",true},
    };
    
    bool Init();
    bool Init(bool group, DirectX::XMFLOAT4X4 c_mtx);
    void Draw();
    void Draw(DirectX::XMFLOAT4X4 mtx);
   // void ActionUpdate(CMonsterMgr* pThis, Skill_ID id);
    void BattleUpdate();
    void Update();
    void Finalize();

    // モデルセット
    void SetModel(CModel* p) {
        m_models = p;
    }
    // HP
    float GetHP() {
        return HP;
    }
    //最大HP
    float GetMaxHP() {
        return maxHP;
    }
    
    TYPE GetType() {
        return type1;
    }
    static CMonsterMgr* GetInstance() {
        static CMonsterMgr Instance;
        return &Instance;
    }
};

