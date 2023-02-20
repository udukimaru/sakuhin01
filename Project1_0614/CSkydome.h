#pragma once
#include "GameObject.h"
#include "CModel.h"
#include	"dx11mathutil.h"

class CSkydome :
    public GameObject
{
private:
    CModel m_model;

public:
    bool Init();

    void Draw();

   

    void Finalize();
};

