#include "CBattleUI.h"
#include "Easing.h"

void CBattleUI::EnemyHPVib_Update()
{
	sin_t += 0.1f;
	enemyHPpos.y = enemyHPpos.y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", enemyHPpos.y);
	uilist[3].color.x = 1.0f;
	uilist[3].color.y = 0.0f;
}
void CBattleUI::myHPVib_Update()
{
	sin_t += 0.1f;
	myHPpos.y = myHPpos.y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", myHPpos.y);
	uilist[1].color.x = 1.0f;
	uilist[1].color.y = 0.0f;
}
void CBattleUI::HPVib_Update(std::vector<BattleUIDataList> &list, int i)
{
	sin_t += 0.1f;
	list[i].y = list[i].y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", list[i].y);
	list[i].color.x = 1.0f;
	list[i].color.y = 0.0f;
}

void CBattleUI::HBasePVib_Update(std::vector<BattleUIDataList>& list, int i)
{
	sin_t += 0.1f;
	list[i].y = list[i].y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", list[i].y);
}


bool CBattleUI::Init()
{
	for (int i=0;i< uilist.size();i++)
	{
		battleui_data[i].Init(1, 1, XMFLOAT4(1, 1, 1, 1), uilist[i].uv_off);
		battleui_data[i].LoadTexture(uilist[i].texfolder);
	}
	return true;
}

void CBattleUI::Draw()
{
	
	for (int i = 0; i < uilist.size(); i++)
	{
		if (uilist[i].active == true) {
			if (i == 0)
			{
				UIDraw(battleui_data, 0, uilist[i].x, uilist[i].y, uilist[i].width, uilist[i].height, uilist[i].size, XMFLOAT4(1, 1, 1, 1), uilist[i].uv_off);
			}
			if (i == 1||i==2)
			{
				UIDraw(battleui_data, i, uilist[i].x, uilist[1].y, uilist[i].width, uilist[i].height, uilist[i].size, uilist[i].color, uilist[i].uv_off);
			}
			if (i == 3 || i == 4)
			{
				UIDraw(battleui_data, i, uilist[i].x, uilist[3].y, uilist[i].width, uilist[i].height, uilist[i].size, uilist[i].color, uilist[i].uv_off);
			}
		}
	}
}

void CBattleUI::Update()
{
	if (uilist[0].active == true) {
		uilist[0].t += 0.01f;
		uilist[0].y = uilist[0].y+CEasing::GetInstance().SinVibe(0.5f, 4, uilist[0].t);
	}

	if (uilist[1].size.x <= 0) {
		uilist[1].size.x = 0;
	}
}

void CBattleUI::HPCal(float damage, float maxhp, float hp, std::vector<BattleUIDataList>& list, int i,bool drawhp)
{
	damage--;
	if (damage > 0&&drawhp==true) {
		hp -= 1.0f;
		list[i].size.x = 1.0f * (hp / maxhp);
		list[i].x = list[i].x - (1.0f + 0.1f);
	}
	else
	{
		drawhp = false;
	}
}
