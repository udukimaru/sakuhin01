#pragma once
#include "GameObject.h"
#include "CModel.h"
#include	"dx11mathutil.h"
#include "CDirectInput.h"
class CBall :
    public GameObject
{
private:
    CModel m_model;
    float vz = 1.0f;
    float vy = 0.5f;
    float m = 200.0f;
    float r = 50.0f;


public:
    bool Init();

    void Draw();

    void DrawWithAxis();

    void Update();

    void Finalize();
};

