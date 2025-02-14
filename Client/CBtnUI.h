#pragma once
#include "CUI.h"

//���⼭ ������ �˷����� ������ �Լ� ������(��Ȯ�� Ŭ������ ����)�� 
//�𸣱⿡ �̻��� ������ ������ �� �־� ������ ����. 

//����Լ� ������ ������ ������ ��Ȯ�� Ŭ���� ������ �˾ƾ� ��. 
#include "CScene.h"
#include "CObject.h"
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);



//�� ���� �����ϰ� �ִ� Ư�� ��� �Լ��� �޾ƿ;߸� ��. 


//��ư UI�� ���������� �ٶ�µ�, �̷� ������ ����� ���� �� �³�?
//� ������Ʈ�� ����� ���� ������? ���������� �� ��� ������?

//�̷��� �ϸ� SCENE�̳�, ������Ʈ���� �Ļ��� ���� �� �� ����. 
typedef void(CScene:: *SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CBtnUI :
    public CUI
{

private:
    //�Լ� �����͸� �ҷ��ͼ� ��ư�� ������ �� �װ� ��.
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

    //�� ��� �Լ��� ��� ���� ��ü��, ȣ�� �� �Լ�. 
    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*         m_pSceneInst;

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CBtnUI)

public:
    CBtnUI();
    ~CBtnUI();
};

