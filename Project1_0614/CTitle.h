#pragma once
#include	"SceneManager.h"
class CTitle :
    public IScene
{
public:
    void Init();
    void Input();
    void Draw();
    void Update();
    void Dispose();

   /* static CTitle& GetInstance() {
        static CTitle Instance;
        return Instance;
    }*/
};

