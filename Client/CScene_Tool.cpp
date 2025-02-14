#include "pch.h"
#include "CScene_Tool.h"
#include "CkeyMgr.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"

#include "resource.h"
#include "CSceneMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"
#include "CPathMgr.h"


void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
{

}

CScene_Tool::~CScene_Tool()
{

}


void CScene_Tool::Enter()
{
	CreateTile(5, 5);
	Vec2 vResolution = CCore::GetInstance()->GetResolution();


	//UI�� ���� ������ �����Ϸ��� Ŭ���� �� �־�߸� ��. 
	//�������� UI�� �̺�Ʈ ���踦 ���شٸ� <- Ư�� ��Ȳ�� ȣ���ϴ� �Լ��� ��Ȯ


	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));

	//��ư UI�� ����ص� �Լ��� ����� �� �ְ� �س���. 
	//�Լ��� ���´� �ݵ�� ��ȯ�� void�̰�, ���ڰ� 2���� �Լ��� ���� �� ����.
	//�׷��� ���� �ְ� ���� �Լ��� �����Լ��� �ƴ� ����Լ���...

	//��� �Լ��� ������ �ݵ�� ��ü�� �ʿ���. 
	//ȣ�� ��ų ��ü�� �ݵ�� �ʿ���. 
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);


	//pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);


	
	/*
	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-500.f, 0.f));

	//�̷��� ���ָ� ����̾� ��������, �ٸ� ������.
	((CBtnUI*)pClonePanel->GetChildsUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	AddObject(pClonePanel, GROUP_TYPE::UI);

	m_pUI = pClonePanel;*/
	//Camera Look ����.
	CCamera::GetInstance()->SetLookAt(vResolution / 2.f);
}


//�� �ȿ� �����ϴ� ��� ���� ������Ʈ. 
//1. ���𰡸� �Է� ���� �� �ִ� ������Ʈ�� ����� �Ǵ� �� �ƴұ�.
//���� �����ϰų�, �׷� �� �ִµ� �����쿡�� ������� ����� �����ϴ� ���� ����. 
void CScene_Tool::Exit()
{
	//���� ������ ��Ŀ�̵Ǿ��� ���� UIMgr�� ����ϰ� �ִµ�...
	//�׷��� �� �ٲܶ��� �׷� �� �� ���� �ؾ���. 

	//���⼭ Ÿ�� ���� ������ �� �־����. 
	DeleteAll();
}


void CScene_Tool::update()
{
	//�θ��� ��� ȣ��. 
	CScene::update();


	SetTileIdx();

	if (KEY_TAP(KEY::CTRL)) {
		LoadTileData();
		//LoadTile(L"tile\\Test.tile");
	}
}



void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN)) {
		Vec2 vMousePos = MOUSE_POS;

		vMousePos = CCamera::GetInstance()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow) return;


		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}


void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInstance()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	
	wstring strTileFolder = CPathMgr::GetInstance()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	//Modal ���. 
	if (GetSaveFileName(&ofn)) {
		//�������� ������ true, ��Ҵ� false.
		CPathMgr::GetInstance()->GetRelativePath(szName);
		SaveTile(szName);
	}
}


void CScene_Tool::SaveTile(const wstring& _strFilePath)
{

	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	assert(pFile);

	//������ ����. 

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��. 
	for (size_t tileIdx = 0; tileIdx < vecTile.size(); tileIdx++) {
		((CTile*)vecTile[tileIdx])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInstance()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInstance()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Modal ���. 
	if (GetOpenFileName(&ofn)) {
		//�������� ������ true, ��Ҵ� false.
		wstring strRelativePath = CPathMgr::GetInstance()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}




void ChangeScene(DWORD_PTR, DWORD_PTR) {
	ChangeScene(SCENE_TYPE::START);
}



//=============================
// Tile Count Window Proc
//=============================

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.

//__stdcall�� �Լ� ȣ�� �Ծ�. 
INT_PTR __stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)// ok�� Xâ ������
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();

			//�̰� �����ϸ� ���������� ĳ������ �Ϸ� 
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));    //Dialog ������. 
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));    
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



//�����س��� �۾��ϴ� �� �ٽ� �ε� ����. 


//BMP������ alpha���� ���µ�...
// �츮�� �� ���� alpha���� �־��ֱ�. ���� ���� ��ġ��?

