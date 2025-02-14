#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"



CMonster::CMonster()
	: m_fSpeed(100.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fMaxMoveDistance(50.f)
	, m_iDir(1)
	, m_iHP(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(45.f,	45.f));
}

CMonster::~CMonster()
{

}

void CMonster::update()
{

	return;
	Vec2 vCurPos = GetPos();

	//���� �������� �ð��� m_fSpeed��ŭ �̵�. 
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	//��ȸ �Ÿ� �������� �Ѿ���� Ȯ��. 
	//�ε�ε� �Ÿ����� ����... �ѹ��� ũ��(105) �Ѿ�µ�, 
	//���� �����ӿ� ���ݹۿ�(-1) �� �ǵ��� ������. 

	float fDistance = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxMoveDistance;
	if (0.f < fDistance) {
		m_iDir *= -1;
		vCurPos.x += fDT * m_fSpeed * m_iDir;
	}

	SetPos(vCurPos);
}


void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	
	if (pOtherObj->GetName() == L"Missile_Player") {
		m_iHP -= 1;

		if(m_iHP <= 0)
			DeleteObject(this);
	}
	
}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}

