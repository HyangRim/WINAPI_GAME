#include "pch.h"
#include "CPanelUI.h"
#include "CkeyMgr.h"



CPanelUI::CPanelUI()
	: CUI(false)
{

}

CPanelUI::~CPanelUI() {

}

void CPanelUI::update()
{
}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown()) {
		Vec2 vDiff = MOUSE_POS - m_vDragStart;


		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	//�г� UI�� �巡���ؼ� �̵� �����ϰ� �ؾ���. 
	//���� ������ ����� �ؼ� �װ� ��ǥ�� ����ϰ�, ������ ��ǥ�� ����Ͽ� �Ȱ��� �Ÿ���ŭ �̵���Ű�� �Ǵ� ��. 
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}