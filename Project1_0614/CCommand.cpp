#include "CCommand.h"
#include "Easing.h"/*
#include "CCollider.h"
#include "CDirectInput.h"*/

//test

CCommand::COMMAND_ID CCommand::ChangeCommand(COMMAND_ID id)
{
	current_buttun = id;
	return current_buttun;
}
Quad2D test;
Quad2D sp[(int)CCommand::COMMAND_ID::MAX];
Quad2D sb[(int)CCommand::COMMAND_SKILL::MAX];
Quad2D monster[(int)CCommand::COMMAND_MONSTER::MAX];
Quad2D bag[(int)CCommand::COMMAND_BAG::MAX];
Quad2D select_mon[(int)CCommand::COMMAND_FINISH::MAX];


bool CCommand::InitButton()
{
	for (int i = 0; i < g_buttunlist.size(); i++) {
		sp[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_buttunlist[i].uv_off);
		sp[i].LoadTexture(g_buttunlist[i].texfolder);
	}
	for (int i = 0; i < g_skilllist.size(); i++) {
		sb[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_skilllist[i].uv_off);
		sb[i].LoadTexture(g_skilllist[i].texfolder);
	}
	for (int i = 0; i < g_monsterlist.size(); i++) {
		monster[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_monsterlist[i].uv_off);
		monster[i].LoadTexture(g_monsterlist[i].texfolder);
	}
	for (int i = 0; i < g_baglist.size(); i++) {
		bag[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_baglist[i].uv_off);
		bag[i].LoadTexture(g_baglist[i].texfolder);
	}
	for (int i = 0; i < g_finishlist.size(); i++) {
		select_mon[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), g_finishlist[i].uv_off);
		select_mon[i].LoadTexture(g_finishlist[i].texfolder);
	}
	return true;
}
//
//void CCommand::DrawCommandID(std::vector<ButtunDataList> battle)
//{
//
//}

void CCommand::DrawButton()
{

	// コマンド
	for (int i = 0; i < g_buttunlist.size(); i++)
	{
		//BattleDraw(i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_off);

		if (g_buttunlist[i].active == true)
		{
			if (g_buttunlist[i].on_off == false)
			{
				if (i < 4) { // IDで正しいか判定?
					UIDraw(sp,i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height, g_buttunlist[i].size, g_buttunlist[i].color, g_buttunlist[i].uv_off);
				}
			}
			else
			{
				if (i < 4) {
					UIDraw(sp,i, g_buttunlist[i].x, g_buttunlist[i].y, g_buttunlist[i].width, g_buttunlist[i].height,
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
	// 技
	for (int i = 0; i < g_skilllist.size(); i++)
	{
		if (g_skilllist[i].active == true) 
		{
			if (g_skilllist[i].on_off == false) {
				if (i < 3) {
					UIDraw(sb, i, g_skilllist[i].x, g_skilllist[i].y, g_skilllist[i].width, g_skilllist[i].height,
						g_skilllist[i].size, g_skilllist[i].color, g_skilllist[i].uv_off);
				}
			}
			else
			{
				if (i < 3) {
					UIDraw(sb, i, g_skilllist[i].x - 5, g_skilllist[i].y + 5, g_skilllist[i].width, g_skilllist[i].height,
						g_skilllist[i].size, g_skilllist[i].color, g_skilllist[i].uv_on);
				}
				if (i == 0) {
					UIDraw(sb, 3, g_skilllist[3].x - 5, g_skilllist[0].y + 5, g_skilllist[3].width, g_skilllist[3].height,
						g_skilllist[3].size, g_skilllist[3].color, g_skilllist[0].uv_on);
				}
				if (i == 1) {
					UIDraw(sb, 4, g_skilllist[4].x - 5, g_skilllist[1].y + 5, g_skilllist[4].width, g_skilllist[4].height,
						g_skilllist[4].size, g_skilllist[4].color, g_skilllist[1].uv_on);
				}
				if (i == 2) {
					UIDraw(sb, 5, g_skilllist[2].x-10, g_skilllist[2].y+10, g_skilllist[5].width, g_skilllist[5].height,
						g_skilllist[5].size, g_skilllist[5].color, g_skilllist[5].uv_on);
				}
			}
		}
	}

	// モンスター
	for (int i = 0; i < g_monsterlist.size(); i++)
	{
		if (g_monsterlist[i].active == true)
		{
			if (g_monsterlist[i].on_off == false) {
				if(i!=1){
					UIDraw(monster, i, g_monsterlist[i].x, g_monsterlist[i].y, g_monsterlist[i].width, g_monsterlist[i].height,
						g_monsterlist[i].size, g_monsterlist[i].color, g_monsterlist[i].uv_off);
				}
			}
			else
			{
				if (i == 0) {
					UIDraw(monster, i, g_monsterlist[i].x - 5, g_monsterlist[i].y + 5, g_monsterlist[i].width, g_monsterlist[i].height,
						g_monsterlist[i].size, g_monsterlist[i].color, g_monsterlist[i].uv_on);
					UIDraw(monster, 1, g_monsterlist[1].x , g_monsterlist[1].y , g_monsterlist[1].width, g_monsterlist[1].height,
						g_monsterlist[1].size, g_monsterlist[1].color, g_monsterlist[1].uv_on);
				}
				}
		}
	}
	// もちもの
	for (int i = 0; i < g_baglist.size(); i++)
	{
		if (g_baglist[i].active == true)
		{
			if (g_baglist[i].on_off == false) {
				UIDraw(bag, i, g_baglist[i].x, g_baglist[i].y, g_baglist[i].width, g_baglist[i].height,
					g_baglist[i].size,g_baglist[i].color, g_baglist[i].uv_off);

			}
			else
			{
				UIDraw(bag, i, g_baglist[i].x, g_baglist[i].y, g_baglist[i].width, g_baglist[i].height,
					g_baglist[i].size, g_baglist[i].color, g_baglist[i].uv_on);
			}
		}
	}

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

//void CCommand::DrawShadow(float y)
//{
//	if (g_buttunlist[4].active == true)
//	{
//		if (g_buttunlist[4].on_off == false)
//		{
//			sp[4].updateVertex(g_buttunlist[4].width, g_buttunlist[4].height, g_buttunlist[4].color, g_buttunlist[4].uv_off);
//			sp[4].updateVbuffer();
//			sp[4].SetPosition(g_buttunlist[4].x, y, 0);
//			sp[4].Draw();
//		}
//		else
//		{
//			sp[4].updateVertex(g_buttunlist[4].width, g_buttunlist[4].height, g_buttunlist[4].color, g_buttunlist[4].uv_on);
//			sp[4].updateVbuffer();
//			sp[4].SetPosition(g_buttunlist[4].x, y, 0);
//			sp[4].Draw();
//		}
//	}
//}

void CCommand::Update()
{

	// イージング
	for (int i = 0; i < g_buttunlist.size(); i++)
	{
		if (g_buttunlist[i].active == true&&i<4) {
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
				if (g_buttunlist[i].x < g_buttunlist[i].x+5)
				{
					g_buttunlist[i].wait = true;
				}
			
		}
		else break;

	}
	// 技
	for (int i = 0; i < g_skilllist.size(); i++)
	{

		if (g_skilllist[i].active == true) {
			if (i == 0)g_skilllist[i].t = g_skilllist[i].t + 0.05f;
			if (i == 1)g_skilllist[i].t = g_skilllist[i].t + 0.04f;
			if (i == 2)g_skilllist[i].t = g_skilllist[i].t + 0.03f;
			if (i == 3)g_skilllist[i].t = g_skilllist[i].t + 0.05f;
			if (i == 4)g_skilllist[i].t = g_skilllist[i].t + 0.04f;
			//posx = lerp(1300, ui1.g_buttunlist[i].x, easeOutElastic(backOut(t)));
			g_skilllist[i].x = CEasing::GetInstance().lerp(1500, 1120, CEasing::GetInstance().easeOutElastic(g_skilllist[i].t));

			if (g_skilllist[i].x < 1120)
			{
				g_skilllist[i].x = 1120;
				g_skilllist[i].wait = true;
			}
			if (g_skilllist[i].x < g_skilllist[i].x+5)
			{
				g_skilllist[i].wait = true;
			}
		}
		else break;
	}

	for (int i = 0; i < g_monsterlist.size(); i++)
	{
		if (g_monsterlist[i].active == true)
		{
			//f (i > 1) {
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
			//}
		}
		else break;
	}
}

void CCommand::SelectUpdate()
{
	if (g_finishlist[0].active == true&& g_finishlist[0].on_off==true)
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
//
//bool CCommand::CheckOnOff(std::vector<ButtunDataList> &list)
//{
//	//std::vector<ButtunDataList> commandlist = list;
//	// カーソル位置取得
//	XMFLOAT2 cursor_pos = {};
//	cursor_pos.x = CDirectInput::GetInstance().GetMousePosX();
//	cursor_pos.y = CDirectInput::GetInstance().GetMousePosY();
//
//
//	for (int i = 0; i < list.size(); i++)
//	{
//	  XMFLOAT2 pos = { list[i].x,list[i].y};
//	  if (CCollider::Col(pos, list[i].width, list[i].height, cursor_pos) && list[i].active == true && list[i].wait == true && BattleaPos[i] <= list[i].x + 10)
//	  {
//		  //OnOff(list);
//		  list[i].on_off = true;
//
//		  if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
//		  {
//			  return true;
//		  }
//	  }
//	  else 
//	  {
//		  list[i].on_off = false;
//	  }
//	 // return false;
//	}
//}

bool CCommand::OnOff(std::vector<ButtunDataList> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].on_off == true)return true;

		else return false;
	}
	
}

// メモ　モンスターのやつ表示されない

//void CCommand::SetStartPos()
//{
//	// コマンド
//	for (int i = 0; i < g_buttunlist.size(); i++)
//	{
//		g_buttunlist[i].t = 0.0f;
//		g_buttunlist[i].x = 0.0f;
//		//sp[i].SetPosition(BattleaPos[i], g_buttunlist[i].y, 0);
//	}
//		//BattleaPos[(int)COMMAND_ID::MAX - 1] = { 0.0f };
//}
//
//void CCommand::SetStartSkillPos()
//{
//	// コマンド
//	for (int i = 0; i < g_skilllist.size(); i++)
//	{
//		g_skilllist[i].t = 0.0f;
//	}
//	//SkillPos[(int)COMMAND_SKILL::MAX - 1] = { 0.0f };
//}
//
void CCommand::SetStartMonsterSize()
{
	for (int i = 0; i < g_monsterlist.size(); i++)
	{
		g_monsterlist[i].size = { 0,0 };
		g_monsterlist[i].color.w = 0.0f;
	}
}

XMFLOAT2 CCommand::SetUV()
{

	XMFLOAT2 UV[4] = {
	{0.0f,0.0f},
	{1.0f,0.0f},
	{0.0f,1.0f},
	{1.0f,1.0f}
	};
	//uv = UV[4];
	return UV[4];
}

void CCommand::SetSadowPos(float y)
{


	sp[4].SetPosition(g_buttunlist[4].x, y, 0);
}


XMFLOAT2 CCommand::SetPositionUI(float x, float y)
{
	XMFLOAT2 pos = { x,y };

	return pos;
}

void CCommand::UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4])
{
	/*for (int i = 0; i < g_buttunlist.size(); i++)
	{
		if (g_buttunlist[i].active == true)
		{
			if (g_buttunlist[i].on_off == false)
			{*/
				quad[i].updateVertex(width, height, color, uv);
				quad[i].updateVbuffer();
				quad[i].SetPosition(x, y, 0);
				quad[i].SetScale(size.x, size.y, 0);
				quad[i].Draw();
			/*}
		}
	}*/
}
