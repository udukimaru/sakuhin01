#include "CActor.h"
#include <random> 

bool CActor::CheckInSight(SightRange range)
{
	switch (range_id)
	{
	case SightRange::SMALL:
		break;
	case SightRange::LEARGE:
		break;
	}
    return false;
}

void CActor::AttackUpdate(Action* pThis, Skill_ID id)
{
	skill_id = id;

	switch (skill_id)
	{
	case Skill_ID::TACKLE:
		Skill_TYPE::NORMAL;  // ノーマルタイプ

		//技の効果とエフェクト（画像）や命中率、威力
		{
			// ランダムで攻撃力決定
			// シード値決定用乱数
			std::random_device rand_dev;
			std::mt19937 m_mt(rand_dev());
			std::uniform_int_distribution<> rand100(10, 15);
			printf("%d\n", rand100(m_mt));

			float ownerHP = pThis->pOwner->GetHP();
			float ownerMaxHP = pThis->pOwner->GetMaxHP();

			ownerHP -= rand100(m_mt);



			//size2.x = ownerHP / ownerMaxHP * 1.0f;
			//posX2 = (1.0f - size2.x) / 4 * 1.0f;

			printf("%f\n", ownerHP);

			//batletet = true;
			//starttext = false;
			//write->DrawString("イッヌのたいあたり！", XMFLOAT2(200, 580), D2D1_DRAW_TEXT_OPTIONS_NONE);
		}
		break;
	case Skill_ID::FLAME:
		Skill_TYPE::FIRE;  // ほのおタイプ


		break;
	case Skill_ID::WATERGUN:
		Skill_TYPE::WATER; // みずタイプ


		break;
	case Skill_ID::LEAFCUTTER:
		Skill_TYPE::GRASS; // くさタイプ


		break;
	case Skill_ID::TELEKINESIS:
		Skill_TYPE::ESPER; // エスパータイプ


		break;
	case Skill_ID::SHADOWBALL:
		Skill_TYPE::GHOST; // ゴーストタイプ


		break;
	}
}
 
