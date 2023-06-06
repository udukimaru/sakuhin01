#include "CCommandSelect.h"
#include "Easing.h"

bool CCommandSelect::Init()
{
	for (int i = 0; i < g_buttunlist.size(); i++) {
		sp[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_buttunlist[i].uv_off);
		sp[i].LoadTexture(g_buttunlist[i].texfolder);
	}

    return true;
}

void CCommandSelect::Draw()
{
	// コマンド
	for (int i = 0; i < g_buttunlist.size(); i++)
	{
		if (g_buttunlist[i].active == true)// UIが表示されているとき
		{
			if (g_buttunlist[i].on_off == false)//　カーソルがボタンにのってない状態
			{
				if (i < 4) { 
					UIDraw(sp, i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_off);
				}
			}
			else//　カーソルがボタンにのっている状態
			{
				// ボタンオンの状態
				if (i < 4)UIDraw(sp, i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);
				// 以下各ボタンの影表示
				/*if (i == 0)UIDraw(sp, 4, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height,g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);
				if (i == 1)UIDraw(sp, 4, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height,g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);
				if (i == 2)UIDraw(sp, 4, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height,g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);
				if (i == 3)UIDraw(sp, 4, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height,g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);*/
				if(i>=4 && state == STATE::NOMAL)UIDraw(sp, i, g_buttunlist[i].fixedPos.x, g_buttunlist[i].fixedPos.y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);
			}
		}
	}
}

void CCommandSelect::Update()
{
	switch (state)
	{
	case STATE::MOVE:
	for (int i = 0; i < g_buttunlist.size(); i++)
	{
		if (g_buttunlist[i].active == true && i < 4) {
			if (i == 0)g_buttunlist[i].t = g_buttunlist[i].t + 0.05f;
			if (i == 1)g_buttunlist[i].t = g_buttunlist[i].t + 0.04f;
			if (i == 2)g_buttunlist[i].t = g_buttunlist[i].t + 0.03f;
			if (i == 3)g_buttunlist[i].t = g_buttunlist[i].t + 0.02f;
			//if (i == 4)g_buttunlist[i].t = g_buttunlist[i].t + 0.02f;

			g_buttunlist[i].x = CEasing::GetInstance().lerp(1500, 1120, CEasing::GetInstance().easeOutElastic(g_buttunlist[i].t));


			if (g_buttunlist[i].x <= g_buttunlist[i].fixedPos.x)
			{
				g_buttunlist[i].x = g_buttunlist[i].fixedPos.x;
				g_buttunlist[i].t = 0;
				isupdate = true;
			}
			if (isupdate == true)
			{
				state = STATE::NOMAL;
				isupdate = false;
			}

		}
	}
		break;

	case STATE::NOMAL:
		for (int i = 0; i < g_buttunlist.size(); i++)
		{
			//if (i < 4) {
				if (g_buttunlist[i].on_off == true)
				{
					g_buttunlist[i].t = g_buttunlist[i].t + 0.06f;
					g_buttunlist[i].x = CEasing::GetInstance().lerp(1120, 1128, CEasing::GetInstance().easeOutElastic(g_buttunlist[i].t));
					g_buttunlist[i].y = CEasing::GetInstance().lerp(g_buttunlist[i].fixedPos.y, g_buttunlist[i].fixedPos.y - 8, g_buttunlist[i].t);
					if (g_buttunlist[i].x > 1128)g_buttunlist[i].x = 1128;
					if (g_buttunlist[i].fixedPos.y - 8 > g_buttunlist[i].y)g_buttunlist[i].y = g_buttunlist[i].fixedPos.y - 8;
				}
				else
				{
					g_buttunlist[i].x = g_buttunlist[i].fixedPos.x;
					g_buttunlist[i].y = g_buttunlist[i].fixedPos.y;
					g_buttunlist[i].t = 0;
				}
			//}
		}
		break;
	}
}

void CCommandSelect::Finalize()
{
}

