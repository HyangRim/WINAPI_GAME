#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CScene_Start.h"


CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{

}

CSceneMgr::~CSceneMgr() {
	for (UINT sceneIDX = 0; sceneIDX < (UINT)SCENE_TYPE::END; sceneIDX++) {

		if (m_arrScene[sceneIDX] != nullptr) {
			delete m_arrScene[sceneIDX];
		}
	}
}

void CSceneMgr::init()
{
	//Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;

	//���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();

	//�θ� �����Ͷ� Start()�� ȣ���� ���� ����. 
}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
