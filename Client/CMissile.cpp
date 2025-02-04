#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	:m_vDir(Vec2(1.f,0.f))
	,m_fTheta(PI / 4.f)
{
	//m_vDir.Normalize();
	CreateCollider();
}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * fDT * m_vDir.x;
	vPos.y += 600.f * fDT * m_vDir.y;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	//부모 클래스 만들기. 
	//CObject::render(_dc);
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}