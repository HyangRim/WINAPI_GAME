#pragma once
#include "CObject.h"

class CTexture;
class CPlayer :
    public CObject
{

private:
    

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

    //�÷��̾� ������Ʈ�� ����Ǹ� 
    CLONE(CPlayer)

public:
    CPlayer();
    ~CPlayer();
};
