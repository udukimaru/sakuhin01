#include "CBag.h"

bool CBag::Init()
{
	for (int i = 0; i < g_baglist.size(); i++) {
		bag[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_baglist[i].uv_off);
		bag[i].LoadTexture(g_baglist[i].texfolder);
	}
	return true;
}

void CBag::Update()
{
	for (int i = 0; i < g_baglist.size(); i++)
	{
		if (g_baglist[i].active == true)
		{
			g_baglist[i].size.x += 0.05f;
			g_baglist[i].size.y += 0.05f;
			g_baglist[i].color.w += 0.03f;
			if (g_baglist[i].size.x >= 1.0f) {
				g_baglist[i].size.x = 1.0f;
			}
			if (g_baglist[i].size.y >= 1.0f) {
				g_baglist[i].size.y = 1.0f;
			}
			if (g_baglist[i].color.w >= 0.8f)
			{
				g_baglist[i].color.w = 1.0f;
			}
		}
	}
}

void CBag::Draw()
{
	// ‚à‚¿‚à‚Ì
	for (int i = 0; i < g_baglist.size(); i++)
	{
		if (g_baglist[i].active == true)
		{
			if (g_baglist[i].on_off == false) {
				UIDraw(bag, i, g_baglist[i].x, g_baglist[i].y, g_baglist[i].width, g_baglist[i].height,
					g_baglist[i].size, g_baglist[i].color, g_baglist[i].uv_off);

			}
			else
			{
				UIDraw(bag, i, g_baglist[i].x, g_baglist[i].y, g_baglist[i].width, g_baglist[i].height,
					g_baglist[i].size, g_baglist[i].color, g_baglist[i].uv_on);
			}
		}
	}
}

void CBag::SetStartSize()
{
	for (int i = 0; i < g_baglist.size(); i++)
	{
		g_baglist[i].size = { 0,0 };
		g_baglist[i].color.w = 0.0f;
	}
}
