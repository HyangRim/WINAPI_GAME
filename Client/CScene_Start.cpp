#include "pch.h"
#include "CScene_start.h"
#include "CObject.h"
#include "CCore.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CPathMgr.h"

CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::Enter()
{


	//Object �߰�.
	//���� ������ ��ü�� �÷��̾�, �ּҸ� ���� �� �θ� Ŭ����. 
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	//���� ��ġ. 
	int iMonCount = 3;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);
	for (int idx = 0; idx < iMonCount; idx++) {
		//Monster Object �߰�.
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)idx * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMaxMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}


	//�浹 ����. 
	//Player �׷�� Monster�׷찣�� �浹 üũ 
	//update���� ����, finalupdate���� ���� ������ �Ϸ�

	//���� ���ο� �浹�� �߻��Ҽ��� ����. 
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
}

void CScene_Start::Exit()
{

}