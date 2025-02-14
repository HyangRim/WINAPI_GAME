#include "pch.h"
#include "CCore.h"


#include "CObject.h"
#include "CTimeMgr.h"
#include "CkeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"



//CCore* CCore::g_pInst = nullptr;

CCore::CCore() 
	: m_hWnd(0), m_ptResolution{}, m_hDC(0)
	, m_arrBrush{}, m_arrPen{}
{
}


CCore::~CCore() {
	//m_hWnd에 엮여있던 m_hDC를 해제해준다. 
	ReleaseDC(m_hWnd, m_hDC);


	
	for (auto penIDX = 0; penIDX < (UINT)PEN_TYPE::END; penIDX++) {
		DeleteObject(m_arrPen[penIDX]);
	}
}


int CCore::init(HWND _hWnd, POINT _ptResolution) {
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 윈도우 크기 조정. 

	RECT rt = { 0,0,m_ptResolution.x, m_ptResolution.y };
	//테두리 포함해서, 크기 보정해주는 것. 
	//rt 포인터에다가 다시 값을 변환해서 넣어줌. 
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);


	//타이틀이나 그런 걸 제외한, 순수하게 물체가 그려질 수 있는 영역.
	//첫 번째로 들어가는 건, 어떤 윈도우인지. 
	//SetWindow는 타이틀창이나 테두리까지 포함한 크기임. 
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	//어디다가 그려요? m_hWnd에다가 그려요. 
	m_hDC = GetDC(m_hWnd);


	//이중 버퍼링 용도의 텍스쳐 한 장을 만든다. 
	m_pMemTex = CResMgr::GetInstance()->CreateTexture(L"BackBuffer", (UINT)(m_ptResolution.x), (UINT)(m_ptResolution.y));

	//자주 사용 할 펜 및 브러쉬 생성. 
	CreateBrushPen();

	//Manager initialize
	CPathMgr::GetInstance()->init();
	CTimeMgr::GetInstance()->init();
	CkeyMgr::GetInstance()->init();
	CCamera::GetInstance()->init();
	CSceneMgr::GetInstance()->init();


	return S_OK;
}


void CCore::progress() {

	// ============
	//	Manager Update
	// ============
	CTimeMgr::GetInstance()->update();
	CkeyMgr::GetInstance()->update();
	CCamera::GetInstance()->update();

	// ============
	//	Scene Update
	// ============

	CSceneMgr::GetInstance()->update();

	// 충돌 체크. 
	CCollisionMgr::GetInstance()->update();

	//UI 이벤트 체크
	CUIMgr::GetInstance()->update();


	// ============
	//	Rendering
	// ============
	

	//화면 초기화(흰 사각형으로 덧 씌움)
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	//어디다가 그려야하는지 알려주기. 
	CSceneMgr::GetInstance()->render(m_pMemTex->GetDC());
	CCamera::GetInstance()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
	
	CTimeMgr::GetInstance()->render();


	//렌더링까지 전부 다 끝난 후에 EventMgr에서 이벤트 지연 처리.
	// ============
	//	이벤트 지연 처리.
	// ============
	CEventMgr::GetInstance()->update();

}


void CCore::CreateBrushPen()
{
	// Hollow Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	//R,G,B Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

}