#include "CTitleUI.h"
#include "Easing.h"

//std::vector<CTitleUI::TitleUI> title_uilist;

// 四角形クラス
static Quad2D	g_quad[(int)CTitleUI::TitleUI_ID::MAX];

//std::vector<Quad2D*> g_UI = {};
//static CTitleUI::TitleUI title_ui[(int)CTitleUI::TitleUI_ID::MAX];

void CTitleUI::Update_Blink()
{
    uilist[2].t += 0.01f;
    float alphaParam = uilist[2].t - (int)uilist[2].t;

    if (alphaParam < 0.5) {
        uilist[2].color.w = alphaParam * 2.0f;
    }
    else {
        uilist[2].color.w = 1.0f - (alphaParam - 0.5f) * 2.0f;
    }

}

bool CTitleUI::InitTitle_UI()
{
    for (int i = 0; i < uilist.size(); i++) {
        g_quad[i].Init(30, 30, XMFLOAT4(1, 1, 1, 1), CTitleUI::uv);
        g_quad[i].LoadTexture(uilist[i].texfolder); 
    }
    return true;
}

void CTitleUI::UpdateTitle_UI()
{
    uilist[3].t += 0.005f;
    uilist[3].y += CEasing::GetInstance().SinVibe(10, 2, uilist[3].t);
    uilist[3].x += 3.0f;
  
    Update_Blink();
}

void CTitleUI::DrawTitle_UI()
{
    for (int i = 0; i < uilist.size(); i++)
    {
        g_quad[i].updateVertex(uilist[i].width, uilist[i].height, uilist[i].color, CTitleUI::uv);
        g_quad[i].updateVbuffer();
        g_quad[i].SetPosition(uilist[i].x, uilist[i].y, 0);
        g_quad[i].Draw();
    }
}
