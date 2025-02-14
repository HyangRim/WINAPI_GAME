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
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	//m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\Tenshi.bmp");


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
	GetCollider()->SetScale(Vec2(25.f, 25.f));

	CTexture* m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");

	//�츮 �ؽ��İ� �Ϻ��ϰ� ������ �Ǿ� �־ ������ �����ϰ� �� �� �־���...
	//�ٵ� �׷��� ���� ��찡 ���� ����. 

	
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", m_pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	for (int idx = 0; idx < pAnim->GetMaxFrame(); idx++) {
		pAnim->GetFrame(idx).vOffset = Vec2(0.f, -20.f);
	}
	
	//pAnim->GetFrame(0).vOffset = Vec2(0.f, -20.f);
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

	if (KEY_TAP(KEY::Z)) {
		CreateMissile();
	}
	SetPos(vPos);

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	//������Ʈ(�浹ü, etc...) �� �ִ� ��� ����. 
	component_render(_dc);
	CTexture* pTex = CResMgr::GetInstance()->LoadTexture(L"Tenshi", L"texture\\Tenshi.bmp");
	
	Vec2 vPos = GetPos();
	vPos = CCamera::GetInstance()->GetRenderPos(vPos);
	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;
	TransparentBlt(_dc,
		int(vPos.x - ((float)(width / 2.f))),
		int(vPos.y - ((float)(height / 2.f))),
		width, height,
		pTex->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255));
	/*
	AlphaBlend(_dc
		, vPos.x - width / 2.f
		, vPos.y - height / 2.f
		, width, height,
		pTex->GetDC(),
		0, 0, width, height, bf
	);
	*/
	/*
	



	TransparentBlt(_dc,
		int(vPos.x - ((float)(width / 2.f))),
		int(vPos.y - ((float)(height / 2.f))),
		width, height,
		pTex->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255));
	*/
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));


	//�̰� �ٷ� �߰��ϴ� �� �ƴ϶�, �̺�Ʈ�� ����ϴ� ��. 
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

