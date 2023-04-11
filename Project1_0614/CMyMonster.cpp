#include "CMyMonster.h"


bool CMyMonster::Init()
{
	for (int i = 0; i < g_monsterlist.size(); i++) {
		monster[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_monsterlist[i].uv_off);
		monster[i].LoadTexture(g_monsterlist[i].texfolder);
	}
    return true;
}

void CMyMonster::Draw()
{
	for (int i = 0; i < g_monsterlist.size(); i++)
	{
		if (g_monsterlist[i].active == true)
		{
			if (i > 1&&i!=10) {
				UIDraw(monster, i, g_monsterlist[i].x, g_monsterlist[i].y, g_monsterlist[i].width, g_monsterlist[i].height,
					g_monsterlist[i].size, g_monsterlist[i].color, g_monsterlist[i].uv_off);
			}
			
			if (g_monsterlist[i].on_off == false) {
				if (i == 0) {
					UIDraw(monster, i, g_monsterlist[i].x, g_monsterlist[i].y, g_monsterlist[i].width, g_monsterlist[i].height,
						g_monsterlist[i].size, g_monsterlist[i].color, g_monsterlist[i].uv_off);
				}
			}
			else
			{
				if (i == 0) {
					UIDraw(monster, i, g_monsterlist[i].x - 5, g_monsterlist[i].y + 5, g_monsterlist[i].width, g_monsterlist[i].height,
						g_monsterlist[i].size, g_monsterlist[i].color, g_monsterlist[i].uv_on);
					UIDraw(monster, 1, g_monsterlist[1].x, g_monsterlist[1].y, g_monsterlist[1].width, g_monsterlist[1].height,
						g_monsterlist[1].size, g_monsterlist[1].color, g_monsterlist[1].uv_on);
				}
			}
		}
	}
}

void CMyMonster::Update()
{
	for (int i = 0; i < g_monsterlist.size(); i++)
	{
		if (g_monsterlist[i].active == true)
		{
			g_monsterlist[i].size.x += 0.05f;
			g_monsterlist[i].size.y += 0.05f;
			g_monsterlist[i].color.w += 0.03f;
			if (g_monsterlist[i].size.x >= 1.0f) {
				g_monsterlist[i].size.x = 1.0f;
			}
			if (g_monsterlist[i].size.y >= 1.0f) {
				g_monsterlist[i].size.y = 1.0f;
			}
			if (g_monsterlist[i].color.w >= 0.8f)
			{
				g_monsterlist[i].color.w = 1.0f;
			}
		}

	// カーソル位置取得
	XMFLOAT2 cursor_pos = {};
	cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
	cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();

	XMFLOAT2 pos = { g_monsterlist[i].x,g_monsterlist[i].y };

		if (CCollider::Col(pos, g_monsterlist[i].width, g_monsterlist[i].height, cursor_pos))
		{

			switch (i)
			{
			case 3:
				g_monsterlist[2].x = g_monsterlist[3].x;
				break;
			case 4:
				g_monsterlist[2].x = g_monsterlist[4].x;
				break;
			case 5:
				g_monsterlist[2].x = g_monsterlist[5].x;
				break;
			case 6:
				g_monsterlist[2].x = g_monsterlist[6].x;
				break;
			case 7:
				g_monsterlist[2].x = g_monsterlist[7].x;
				break;
			case 8:
				g_monsterlist[2].x = g_monsterlist[8].x;
			case 9:
			case 10:
				break;
			}
		}
	}
}

void CMyMonster::Finalize()
{
}

void CMyMonster::SetStartMonsterSize()
{
	for (int i = 0; i < g_monsterlist.size(); i++)
	{
		g_monsterlist[i].size = { 0,0 };
		g_monsterlist[i].color.w = 0.0f;
	}
}
