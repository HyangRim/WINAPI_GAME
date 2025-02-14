#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CkeyMgr.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	//���⼭ ���� �����ڸ� ������, �θ𿡼� �⺻�����ڷ� ���� ������.
	//���� ���� �����ڸ� ��������� �־���߸� ��. 
	for (auto& child : _origin.m_vecChildUI) {
		AddChild(child->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}


void CUI::update()
{
	//child ui update
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();
	m_vFinalPos = GetPos();
	//UI�� ���� ��ǥ�� ���Ѵ�.
	if (GetParent()) {
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	//UI ���콺 üũ
	MouseOnCheck();

	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected) {
		vPos = CCamera::GetInstance()->GetRenderPos(vPos);
	}
	if (m_bLbtnDown) {
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		Rectangle(_dc, (int)(vPos.x), (int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}
	else {
		Rectangle(_dc, (int)(vPos.x), (int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}
	//child ui render
	render_child(_dc);
}

void CUI::update_child()
{
	for (auto& child : m_vecChildUI) {
		child->update();
	}
}

void CUI::finalupdate_child()
{
	for (auto& child : m_vecChildUI) {
		child->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (auto& child : m_vecChildUI) {
		child->render(_dc);
	}
}


void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}


void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected) {
		vMousePos = CCamera::GetInstance()->GetRealPos(vMousePos);
	}
	

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <=m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y) 
	{
		m_bMouseOn = true;
	}
	else {
		m_bMouseOn = false;
	}
}

//������ ���� �� UI�� ������ ��Ŀ���� �ٲ��� ��. -> ĵ���� UI���� ������ ������ �ؾ߸� ��. 