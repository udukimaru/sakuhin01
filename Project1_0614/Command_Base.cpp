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

// 1:UI���X�g�@2:���X�g�ԍ��@3:x���W�@4:�����W�@5:���傫���@6:�c�傫���@7:�T�C�Y�@8:�F�@9:UV���W
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
