#include "CBattleUI.h"
#include "Easing.h"

//std::vector<std::shared_ptr<Quad2D>> spritedata;
Quad2D battleui_data[(int)CBattleUI::UI_ID::MAX];

void CBattleUI::EnemyHPVib_Update()
{
	sin_t += 0.1f;
	enemyHPpos.y = enemyHPpos.y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", enemyHPpos.y);
	uilist[3].color.x = 1.0f;
	uilist[3].color.y = 0.0f;
	/*uilist[3].t += 0.1f;
	enemyHPpos.y = enemyHPpos.y + CEasing::GetInstance().SinVibe(10, 8, uilist[3].t);*/

}
void CBattleUI::myHPVib_Update()
{
	sin_t += 0.1f;
	myHPpos.y = myHPpos.y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", myHPpos.y);
	uilist[1].color.x = 1.0f;
	uilist[1].color.y = 0.0f;
}
void CBattleUI::HPVib_Update(std::vector<UI_List> &list, int i)
{
	sin_t += 0.1f;
	list[i].y = list[i].y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", list[i].y);
	list[i].color.x = 1.0f;
	list[i].color.y = 0.0f;
}

void CBattleUI::HBasePVib_Update(std::vector<UI_List>& list, int i)
{
	sin_t += 0.1f;
	list[i].y = list[i].y + CEasing::GetInstance().SinVibe(10, 8, sin_t);
	printf("%f\n", list[i].y);
}

//void CBattleUI::Init()
//{
//	/*for (int i = 0; i < uilist.size(); i++)
//	{
//		Quad2D::Init(uilist[i].width, uilist[i].height, uilist[i].color, text_uv);
//	}
//
//	for (int i = 0; i < uilist.size(); i++)
//	{
//		Quad2D::LoadTexture(uilist[i].texfolder);
//	}*/
//
//	/*for (auto& u : uilist)
//	{
//		std::shared_ptr<Quad2D> p(std::make_shared<Quad2D>());
//		p->LoadTexture(u.texfolder);
//
//		p->Init(u.width, u.height, u.color, text_uv);
//		p->SetScale(u.size.x, u.size.y, 0);
//		p->SetPosition(u.x, u.y, 0);
//		p->updateVertex(u.width, u.height, u.color, text_uv);
//		p->updateVbuffer();
//
//		list.push_back(p);
//	}*/
//}
//
void CBattleUI::Init()
{
	for (int i=0;i< uilist.size();i++)
	{
		battleui_data[i].Init(1, 1, XMFLOAT4(1, 1, 1, 1), uilist[i].uv);
		battleui_data[i].LoadTexture(uilist[i].texfolder);
	}
}

void CBattleUI::Draw()
{
	
	for (int i = 0; i < uilist.size(); i++)
	{
		if (uilist[i].active == true) {
			if (i == 0)
			{
				battleui_data[i].updateVertex(uilist[i].width, uilist[i].height, XMFLOAT4(1, 1, 1, 1), uilist[i].uv);
				battleui_data[i].updateVbuffer();
				battleui_data[i].SetScale(uilist[i].size.x, uilist[i].size.y, 0);
				battleui_data[i].SetPosition(uilist[i].x, uilist[i].y, 0);
				battleui_data[i].Draw();
			}
			if (i == 1||i==2)
			{
				battleui_data[i].updateVertex(uilist[i].width, uilist[i].height, uilist[i].color, uilist[i].uv);
				battleui_data[i].updateVbuffer();
				battleui_data[i].SetScale(uilist[i].size.x, uilist[i].size.y, 0);
				battleui_data[i].SetPosition(uilist[i].x, uilist[1].y, 0);
				battleui_data[i].Draw();
			}
			if (i == 3 || i == 4)
			{
				battleui_data[i].updateVertex(uilist[i].width, uilist[i].height, uilist[i].color, uilist[i].uv);
				battleui_data[i].updateVbuffer();
				battleui_data[i].SetScale(uilist[i].size.x, uilist[i].size.y, 0);
				battleui_data[i].SetPosition(uilist[i].x, uilist[3].y, 0);
				battleui_data[i].Draw();
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

void CBattleUI::HPCal(float damage, float maxhp, float hp, std::vector<UI_List>& list, int i,bool drawhp)
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

void CBattleUI::UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4])
{
	quad[i].updateVertex(width, height, color, uv);
	quad[i].updateVbuffer();
	quad[i].SetPosition(x, y, 0);
	quad[i].SetScale(size.x, size.y, 0);
	quad[i].Draw();
}

//void CBattleUI::CreateUI(UI_ID type,float x,float y, float z, float xsize, float ysize, DirectX::XMFLOAT4 color)
//{
//	Quad2D board = *CBattleUI::GetInstance().GetUIPtr(type);
//
//	board.SetScale(xsize, ysize, 0);
//	board.SetPosition(x, y, z);
//
//	g_UserInterfaces.push_back(board);
//}
