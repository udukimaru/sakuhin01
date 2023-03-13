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
	// ƒRƒ}ƒ“ƒh
	for (int i = 0; i < g_buttunlist.size(); i++)
	{
		//BattleDraw(i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_off);

		if (g_buttunlist[i].active == true)
		{
			if (g_buttunlist[i].on_off == false)
			{
				if (i < 4) { // ID‚Å³‚µ‚¢‚©”»’è?
					UIDraw(sp, i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_off);
				}
			}
			else
			{
				if (i < 4) {
					UIDraw(sp, i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height,
						g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_on);
				}
				if (i == 0) {
					UIDraw(sp, 4, g_buttunlist[0].x, g_buttunlist[0].y, g_buttunlist[4].width, g_buttunlist[4].height,
						g_buttunlist[4].size, g_buttunlist[4].color, g_buttunlist[0].uv_on);
				}
				if (i == 1) {
					UIDraw(sp, 4, g_buttunlist[1].x, g_buttunlist[1].y, g_buttunlist[4].width, g_buttunlist[4].height,
						g_buttunlist[4].size, g_buttunlist[4].color, g_buttunlist[1].uv_on);
				}
				if (i == 2) {
					UIDraw(sp, 4, g_buttunlist[2].x, g_buttunlist[2].y, g_buttunlist[4].width, g_buttunlist[4].height,
						g_buttunlist[4].size, g_buttunlist[4].color, g_buttunlist[2].uv_on);
				}
				if (i == 3)
				{
					UIDraw(sp, 4, g_buttunlist[3].x, g_buttunlist[3].y, g_buttunlist[4].width, g_buttunlist[4].height,
						g_buttunlist[4].size, g_buttunlist[4].color, g_buttunlist[3].uv_on);
				}

			}
		}
	}
}

void CCommandSelect::Update()
{
	for (int i = 0; i < g_buttunlist.size(); i++)
	{
		if (g_buttunlist[i].active == true && i < 4) {
			if (i == 0)g_buttunlist[i].t = g_buttunlist[i].t + 0.05f;
			if (i == 1)g_buttunlist[i].t = g_buttunlist[i].t + 0.04f;
			if (i == 2)g_buttunlist[i].t = g_buttunlist[i].t + 0.03f;
			if (i == 3)g_buttunlist[i].t = g_buttunlist[i].t + 0.02f;
			if (i == 4)g_buttunlist[i].t = g_buttunlist[i].t + 0.02f;

			g_buttunlist[i].x = CEasing::GetInstance().lerp(1500, 1120, CEasing::GetInstance().easeOutElastic(g_buttunlist[i].t));


			if (g_buttunlist[i].x < 1120)
			{
				g_buttunlist[i].x = 1120;
				g_buttunlist[i].wait = true;
			}
			if (g_buttunlist[i].x < g_buttunlist[i].x + 5)
			{
				g_buttunlist[i].wait = true;
			}

		}
		else break;

	}
}

void CCommandSelect::Finalize()
{
}

