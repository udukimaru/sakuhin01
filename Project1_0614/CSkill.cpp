#include "CSkill.h"
#include "Easing.h"

bool CSkill::Init()
{
	for (int i = 0; i < g_skilllist.size(); i++) {
		skill[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_skilllist[i].uv_off);
		skill[i].LoadTexture(g_skilllist[i].texfolder);
	}
	return true;
}

void CSkill::Draw()
{
	// ‹Z
	for (int i = 0; i < g_skilllist.size(); i++)
	{
		if (g_skilllist[i].active == true)
		{
			if (g_skilllist[i].on_off == false) {
				if (i < 3) {
					UIDraw(skill, i, g_skilllist[i].x, g_skilllist[i].y, g_skilllist[i].width, g_skilllist[i].height,
						g_skilllist[i].size, g_skilllist[i].color, g_skilllist[i].uv_off);
				}
			}
			else
			{
				if (i < 3) {
					UIDraw(skill, i, g_skilllist[i].x, g_skilllist[i].y, g_skilllist[i].width, g_skilllist[i].height,
						g_skilllist[i].size, g_skilllist[i].color, g_skilllist[i].uv_on);
				}
				if (i == 0&& state == STATE::NOMAL)UIDraw(skill, 3, g_skilllist[3].fixedPos.x, g_skilllist[3].fixedPos.y, g_skilllist[3].width, g_skilllist[3].height,
					g_skilllist[3].size, g_skilllist[3].color, g_skilllist[i].uv_on);
				if (i == 1 && state == STATE::NOMAL)UIDraw(skill, 4, g_skilllist[4].fixedPos.x, g_skilllist[4].fixedPos.y, g_skilllist[4].width, g_skilllist[4].height,
					g_skilllist[4].size, g_skilllist[4].color, g_skilllist[i].uv_on);
				if (i == 2 && state == STATE::NOMAL)UIDraw(skill, 5, g_skilllist[5].fixedPos.x, g_skilllist[5].fixedPos.y, g_skilllist[5].width, g_skilllist[5].height,
					g_skilllist[5].size, g_skilllist[5].color, g_skilllist[5].uv_on);
				
			}
		}
	}

}

void CSkill::Update()
{
	switch (state)
	{
	case STATE::MOVE:
		// ‹Z
		for (int i = 0; i < g_skilllist.size(); i++)
		{
			if (i == 0)g_skilllist[i].t = g_skilllist[i].t + 0.05f;
			if (i == 1)g_skilllist[i].t = g_skilllist[i].t + 0.04f;
			if (i == 2)g_skilllist[i].t = g_skilllist[i].t + 0.03f;
			if (i == 3)g_skilllist[i].t = g_skilllist[i].t + 0.05f;
			if (i == 4)g_skilllist[i].t = g_skilllist[i].t + 0.04f;
			if (i == 5)g_skilllist[i].t = g_skilllist[i].t + 0.03f;

			g_skilllist[i].x = CEasing::GetInstance().lerp(1500, 1120, CEasing::GetInstance().easeOutElastic(g_skilllist[i].t));

			if (g_skilllist[i].x <= g_skilllist[i].fixedPos.x)
			{
				g_skilllist[i].x = g_skilllist[i].fixedPos.x;
				g_skilllist[i].t = 0;
				//state = STATE::NOMAL;
				isupdate = true;
			}
			if (isupdate == true)
			{
				state = STATE::NOMAL;
				isupdate = false;
			}
		}
		break;
	case STATE::NOMAL:
		for (int i = 0; i < g_skilllist.size(); i++)
		{
			if (g_skilllist[i].on_off == true)
			{
				g_skilllist[i].t = g_skilllist[i].t + 0.06f;
				g_skilllist[i].x = CEasing::GetInstance().lerp(1120, 1128, CEasing::GetInstance().easeOutElastic(g_skilllist[i].t));
				g_skilllist[i].y = CEasing::GetInstance().lerp(g_skilllist[i].fixedPos.y, g_skilllist[i].fixedPos.y - 8, g_skilllist[i].t);
				if (g_skilllist[i].x > 1128)g_skilllist[i].x = 1128;
				if (g_skilllist[i].fixedPos.y - 8 > g_skilllist[i].y)g_skilllist[i].y = g_skilllist[i].fixedPos.y - 8;
			}
			else
			{
				g_skilllist[i].x = g_skilllist[i].fixedPos.x;
				//g_skilllist[i].y = g_skilllist[i].fixedPos.y;
				g_skilllist[i].t = 0;
			}
		}
		break;
	}
}

void CSkill::Finalize()
{
}

void CSkill::SpecialOn(bool is)
{
	special = is;
}

bool CSkill::IsSpecial()
{
	return special;
}
