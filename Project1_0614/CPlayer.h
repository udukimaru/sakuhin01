#pragma once
#include "GameObject.h"
#include "CModel.h"
#include "dx11mathutil.h"
#include "CDirectInput.h"

class CPlayer :
    public GameObject
{
private:
    CModel m_model;

public:
    bool Init();
    void Draw();
    void Update();
    void Order();
    void Finalize();

private:
	static bool m_modelloadflag;							// モデルを読み込んだかどうか

	float						m_speed = 0.0f;				// スピード
	DirectX::XMFLOAT3			m_angle;					// 回転角

};

