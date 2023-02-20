#pragma once
#include "GameObject.h"
#include "CModel.h"
#include	"dx11mathutil.h"
#include	"CDirectInput.h"
class Grass 
{
private:
    CModel m_model;

public:
    void Init();

    void Update();

    void Draw();

    void DrawWithAxis();
    
    void Finalize();
};

