#include "Command_Base.h"
#include "CCommandSelect.h"
#include "CSkill.h"
#include "CMyMonster.h"
#include "CBag.h"
//
//CCommandSelect *cselect;
//CSkill* cskill;
//CMyMonster* cmonster;
//CBag* cbag;

bool Command_Base::Init()
{
	/*cselect = new CCommandSelect();
	cselect->Init();

	cskill = new CSkill;
	cskill->Init();

	cmonster = new CMyMonster;
	cmonster->Init();

	cbag = new CBag;
	cbag->Init();*/
	return true;
}

void Command_Base::Draw()
{
	/*cselect->Draw();
	cskill->Draw();
	cmonster->Draw();
	cbag->Draw();*/
}

void Command_Base::Update()
{
}

void Command_Base::Finalize()
{
	/*delete cselect;
	delete cskill;
	delete cmonster;
	delete cbag;*/
}


void Command_Base::UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4])
{
	quad[i].updateVertex(width, height, color, uv);
	quad[i].updateVbuffer();
	quad[i].SetPosition(x, y, 0);
	quad[i].SetScale(size.x, size.y, 0);
	quad[i].Draw();
}
