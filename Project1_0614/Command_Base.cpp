#include "Command_Base.h"

void Command_Base::UIDraw(Quad2D quad[], int i, float x, float y, float width, float height, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 uv[4])
{
	quad[i].updateVertex(width, height, color, uv);
	quad[i].updateVbuffer();
	quad[i].SetPosition(x, y, 0);
	quad[i].SetScale(size.x, size.y, 0);
	quad[i].Draw();
}
