#include "TestMonster.h"

// モンスターの親子関係及び初期位置・初期角度を定義したデータ
TestMonster::MonsterInitData TestMonster::ObjectInitData[] = {
// 親 モデル番号 初期位置 初期角度 
// 注意：かならず子供より親が先にならぶこと
{ MONSTERPARTS::NONE, MONSTERPARTS::HIP, {0.0f, 0.0f, 0.0f}, {0,0,0}, },
{ MONSTERPARTS::HIP, MONSTERPARTS::BODY, {0.0f, 1.3f, -0.4f}, {0,0,0}, },
{ MONSTERPARTS::BODY, MONSTERPARTS::HEAD, {0.0f, 1.85f, -0.55f}, {0,0,0}, },
{ MONSTERPARTS::BODY, MONSTERPARTS::ARMR0, {-1.8f, 1.35f, -0.3f}, {0,0,0}, },
{ MONSTERPARTS::BODY, MONSTERPARTS::ARML0, {1.8f, 1.35f, -0.3f}, {0,0,0}, },
 { MONSTERPARTS::HIP, MONSTERPARTS::LEGR0, {-1.0f, -0.6f, 0.45f}, {0,0,0}, },
 { MONSTERPARTS::HIP, MONSTERPARTS::LEGL0, { 1.0f, -0.6f, 0.45f}, {0,0,0}, },

 { MONSTERPARTS::ARMR0, MONSTERPARTS::ARMR1, {-1.18f, -1.27f, 0.7f}, {0,0,0}, },
 { MONSTERPARTS::ARML0, MONSTERPARTS::ARML1, { 1.18f, -1.27f, 0.7f}, {0,0,0}, },

 { MONSTERPARTS::LEGR0, MONSTERPARTS::LEGR1, {-1.17f, -2.3f, -1.26f}, {0,0,0}, },
 { MONSTERPARTS::LEGL0, MONSTERPARTS::LEGL1, { 1.17f, -2.3f, -1.26f}, {0,0,0}, },

 { MONSTERPARTS::BODY, MONSTERPARTS::WINGR0, { 0.1f, 1.17f, 0.0f}, {0,0,0}, },
 { MONSTERPARTS::BODY, MONSTERPARTS::WINGL0, {-0.1f, 1.17f, 0.0f}, {0,0,0}, },
 { MONSTERPARTS::WINGR0, MONSTERPARTS::WINGR1, {-2.48f, 4.36f, 1.58f}, {0,0,0}, },
 { MONSTERPARTS::WINGL0, MONSTERPARTS::WINGL1, { 2.48f, 4.36f, 1.58f}, {0,0,0}, },
 { MONSTERPARTS::HIP, MONSTERPARTS::TAIL0 , { 0.0f, 0.0f, 0.0f }, {0,0,0}, },
 { MONSTERPARTS::END, MONSTERPARTS::END, { 0.0f, 0.0f, 0.0f }, { 0,0,0 } } // 終了
 };

 // モデルファイル名リスト
TestMonster::MonsterModelData TestMonster::XFileData[] = {
{MONSTERPARTS::HIP, "assets/model/Char/E2/e2_hip.x"},
{MONSTERPARTS::BODY, "assets/model/Char/E2/e2_body.x"},
{MONSTERPARTS::HEAD, "assets/model/Char/E2/e2_head.x"},
{MONSTERPARTS::ARMR0,"assets/model/Char/E2/e2_armr0.x"},
{MONSTERPARTS::ARML0,"assets/model/Char/E2/e2_arml0.x"},
{MONSTERPARTS::LEGR0,"assets/model/Char/E2/e2_legr0.x"},
{MONSTERPARTS::LEGL0,"assets/model/Char/E2/e2_legl0.x"},
{MONSTERPARTS::ARMR1,"assets/model/Char/E2/e2_armr1.x"},
{MONSTERPARTS::ARML1,"assets/model/Char/E2/e2_arml1.x"},
{MONSTERPARTS::LEGR1,"assets/model/Char/E2/e2_legr1.x"},
{MONSTERPARTS::LEGL1,"assets/model/Char/E2/e2_legl1.x"},
{MONSTERPARTS::WINGR0,"assets/model/Char/E2/e2_wingr0.x"},
{MONSTERPARTS::WINGL0,"assets/model/Char/E2/e2_wingl0.x"},
{MONSTERPARTS::WINGR1,"assets/model/Char/E2/e2_wingr1.x"},
{MONSTERPARTS::WINGL1,"assets/model/Char/E2/e2_wingl1.x"},
{MONSTERPARTS::TAIL0 ,"assets/model/Char/E2/e2_tail0.x"},
{MONSTERPARTS::END,nullptr }
};

bool TestMonster::Init()
{
    return false;
}

void TestMonster::Draw()
{
}

void TestMonster::Update()
{
}

void TestMonster::Finalize()
{
}

void TestMonster::UpdateLocalpose()
{
}

void TestMonster::CaliculateParentChildMtx()
{
}
