#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CkeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\Tenshi.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
	GetCollider()->SetScale(Vec2(25.f, 25.f));
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos();
	if (KEY_HOLD(KEY::W)) {
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S)) {
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A)) {
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D)) {
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE)) {
		CreateMissile();
	}
	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	int iWidth = m_pTex->Width();
	int iHeight = m_pTex->Height();

	Vec2 vPos = GetPos();

	/*
	BitBlt(_dc,
		int(vPos.x - ((float)(iWidth / 2.f))),
		int(vPos.y - ((float)(iHeight / 2.f))),
		iWidth,
		iHeight,
		m_pTex->GetDC(), 
		0, 0, SRCCOPY);
	*/
	//�Ϻ� �ȼ����� �Űܼ� �������� ���� �ʳ�?(��� ��ȫ�� ���� ����)
	//Bitblt���� �ٸ� �ű�� �Լ��� ����
	TransparentBlt(_dc, 
		int(vPos.x - ((float)(iWidth / 2.f))),
		int(vPos.y - ((float)(iHeight / 2.f))),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight, 
		RGB(255, 0, 255));

	//������Ʈ(�浹ü, etc...) �� �ִ� ��� ����. 
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));


	//�̰� �ٷ� �߰��ϴ� �� �ƴ϶�, �̺�Ʈ�� ����ϴ� ��. 
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

