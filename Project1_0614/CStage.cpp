#include "CStage.h"
#include "CModel.h"
#include "dx11mathutil.h"

CModel g_stage{};

DirectX::XMFLOAT4X4 g_mtxstage[20][20];

void CStage::Init()
{
	bool sts = g_stage.Init(
		"assets/stage/PlayerBox.x",
		"shader/vs.hlsl",
		"shader/ps.hlsl",
		"assets/stage/");

	XMFLOAT3 st_pos(-60, -30, 60);
	XMFLOAT3 st_up_pos(0, 0, 0);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {

			DX11MtxIdentity(g_mtxstage[i][j]);

			g_mtxstage[i][j]._41 = st_pos.x + (i * 15);
			g_mtxstage[i][j]._42 = st_pos.y;
			g_mtxstage[i][j]._43 = st_pos.z - (j * 15);

		}
	}
}

void CStage::Draw()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			g_stage.Draw(g_mtxstage[i][j]);
		}
	}
}

void CStage::Finalize()
{
	g_stage.Uninit();
}
