#include "pch.h"
#include "func.h"



#include "CObject.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent createEvn = {};
	createEvn.eEven = EVENT_TYPE::CREATE_OBJECT;
	createEvn.lParam = (DWORD_PTR)_pObj;
	createEvn.wParam = (DWORD_PTR)_eGroup;


	CEventMgr::GetInstance()->AddEvent(createEvn);
}
