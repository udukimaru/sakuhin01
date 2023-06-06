#include "Command_Base.h"

bool Command_Base::Init()
{
	return true;
}

void Command_Base::Draw()
{
}

void Command_Base::Update()
{
}

void Command_Base::Finalize()
{
}

// 1:UIリスト　2:リスト番号　3:x座標　4:ｙ座標　5:横大きさ　6:縦大きさ　7:サイズ　8:色　9:UV座標
void Command_Base::UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4])
{
	quad[i].updateVertex(width, height, color, uv);
	quad[i].updateVbuffer();
	quad[i].SetPosition(x, y, 0);
	quad[i].SetScale(size.x, size.y, 0);
	quad[i].Draw();
}

void Command_Base::SlidePos(float x, float y)
{

}
