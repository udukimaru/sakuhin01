#include "CFinishSelect.h"
#include "Easing.h"

bool CFinishSelect::Init()
{
	for (int i = 0; i < g_finishlist.size(); i++) {
		select_mon[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_finishlist[i].uv_off);
		select_mon[i].LoadTexture(g_finishlist[i].texfolder);
	}
	return true;
}

void CFinishSelect::Draw()
{
	// Select
	for (int i = 0; i < g_finishlist.size(); i++)
	{
		if (g_finishlist[i].active == true)
		{
			if (g_finishlist[i].on_off == false)
			{
				if (i < 3) {

					UIDraw(select_mon, i, g_finishlist[i].x, g_finishlist[i].y, g_finishlist[i].width, g_finishlist[i].height,
						g_finishlist[i].size, g_finishlist[i].color, g_finishlist[i].uv_off);
				}
			}
			else
			{
				if (i < 3) {

					UIDraw(select_mon, i, g_finishlist[i].x, g_finishlist[i].y, g_finishlist[i].width, g_finishlist[i].height,
						g_finishlist[i].size, g_finishlist[i].color, g_finishlist[i].uv_on);
				}
			}
		}
	}
}

void CFinishSelect::Update()
{
	if (g_finishlist[0].active == true && g_finishlist[0].on_off == true)
	{
		g_finishlist[0].t += 0.01f;
		g_finishlist[0].y = g_finishlist[0].y - CEasing::GetInstance().SinVibe(1.1f, 5, g_finishlist[0].t);
	}

	if (g_finishlist[1].active == true && g_finishlist[1].on_off == true)
	{
		g_finishlist[1].t += 0.01f;
		g_finishlist[1].y = g_finishlist[1].y - CEasing::GetInstance().SinVibe(1.1f, 5, g_finishlist[1].t);
	}
}

void CFinishSelect::Finalize()
{
}
