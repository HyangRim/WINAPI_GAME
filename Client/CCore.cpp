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



//CCore* CCore::g_pInst = nullptr;

CCore::CCore() 
	: m_hWnd(0), m_ptResolution{}, m_hDC(0)
	, m_hBit(0), m_memDC(0)
	, m_arrBrush{}, m_arrPen{}
{
}


CCore::~CCore() {
	//m_hWnd�� �����ִ� m_hDC�� �������ش�. 
	ReleaseDC(m_hWnd, m_hDC);


	//Create�� ���� ���� DeleteDC�� �ؾ��Ѵ�. 
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
	
	for (auto penIDX = 0; penIDX < (UINT)PEN_TYPE::END; penIDX++) {
		DeleteObject(m_arrPen[penIDX]);
	}
}


int CCore::init(HWND _hWnd, POINT _ptResolution) {
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ������ ũ�� ����. 

	RECT rt = { 0,0,m_ptResolution.x, m_ptResolution.y };
	//�׵θ� �����ؼ�, ũ�� �������ִ� ��. 
	//rt �����Ϳ��ٰ� �ٽ� ���� ��ȯ�ؼ� �־���. 
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);


	//Ÿ��Ʋ�̳� �׷� �� ������, �����ϰ� ��ü�� �׷��� �� �ִ� ����.
	//ù ��°�� ���� ��, � ����������. 
	//SetWindow�� Ÿ��Ʋâ�̳� �׵θ����� ������ ũ����. 
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	//���ٰ� �׷���? m_hWnd���ٰ� �׷���. 
	m_hDC = GetDC(m_hWnd);


	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����. 
	//�׸��� �׸� �� �ִ� �� �����쿡 �޷��ִ�, �ػ󵵸�ŭ�� �ȼ�(��� ��Ʈ���̶�� �θ�)

	//�ᱹ �Ȱ��� �ػ󵵷� ��Ʈ���� ������ �Ǵ� �� �ƴѰ�? �ؼ� �Ȱ��� �ػ��� ��Ʈ���� ����. 
	//Compatible�� ȣȯ��. (ȣȯ���� ������ �ִ� ��Ʈ��)
	//��Ʈ�� ���̵� ���� �޾���. 
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	//���� ���� �������� DC�� �ʿ���. (� ���������� ���� Device Context�� �ʿ���)
	m_memDC = CreateCompatibleDC(m_hDC);

	//�̹��� �׸��� �׸� Ÿ��, �������� ��ü���ִ� ��. ������ ���� ��Ʈ���� ��������. 
	//�ǵ��� ���ϵǴ� �� ���� ��Ʈ������ ������? �⺻������ ���ִ� 1�ȼ�¥�� Default ��Ʈ��. 
	HBITMAP holdBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(holdBit);


	//���� ��� �� �� �� �귯�� ����. 
	CreateBrushPen();

	//Manager initialize
	CPathMgr::GetInstance()->init();
	CTimeMgr::GetInstance()->init();
	CkeyMgr::GetInstance()->init();
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

	// �浹 üũ. 
	CCollisionMgr::GetInstance()->update();

	//UI �̺�Ʈ üũ
	CUIMgr::GetInstance()->update();


	// ============
	//	Rendering
	// ============
	

	//ȭ�� �ʱ�ȭ(�� �簢������ �� ����)
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	//���ٰ� �׷����ϴ��� �˷��ֱ�. 
	CSceneMgr::GetInstance()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
	
	CTimeMgr::GetInstance()->render();


	//���������� ���� �� ���� �Ŀ� EventMgr���� �̺�Ʈ ���� ó��.
	// ============
	//	�̺�Ʈ ���� ó��.
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