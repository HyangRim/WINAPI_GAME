#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
    virtual void update();
    //�θ�κ��� ��ӹ��� �����Լ�����, �Ϲ� �Լ����� ������ ���� �ȵǼ� virtual��. 
    //virtual�� ����� �����Լ��̱� ��... �׷��� ���������. 
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();
};

