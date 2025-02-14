#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "func.h"
#include "CTile.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"




CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {
			//m_arrObj[�׷�][��ü] ����. 
			delete m_arrObj[typeIDX][objIDX];
		}
		
		//���� �������, �� ���� ���͵鵵 �� �����. 
		//STL�� RAII�� �˾Ƽ� �����ϱ� ����. 
	}
}

void CScene::update()
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {
			if (!m_arrObj[typeIDX][objIDX]->IsDead()) {
				m_arrObj[typeIDX][objIDX]->update();
			}
		}
	}
}
//�����̰� �ߴ� ��, ���������� ������Ʈ ��. 
//�浹ü�� �÷��̾� ���󰡰� ��, �浹 ó��. 
void CScene::finalupdate()
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {

			//Final Update�� ������. ���������� Component���� ������ �ܰ� ������Ʈ(�浹ó����, ���������)
			m_arrObj[typeIDX][objIDX]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		auto ObjVecIter = m_arrObj[typeIDX].begin();

		for (; ObjVecIter != m_arrObj[typeIDX].end();) {
			if (!(*ObjVecIter)->IsDead()) {
				(*ObjVecIter)->render(_dc);
				ObjVecIter++;
			}
			else {
				//Dead������ ��쿣 ���������� �����ϱ�. 
				ObjVecIter = m_arrObj[typeIDX].erase(ObjVecIter);
			}

		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eGroup)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eGroup]);
}

void CScene::DeleteAll()
{

	for (UINT GroupIdx = 0; GroupIdx < (UINT)GROUP_TYPE::END; GroupIdx++) {
		DeleteGroup((GROUP_TYPE)GroupIdx);
	}
}

void CScene::CreateTile(UINT _IXCount, UINT _IYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _IXCount;
	m_iTileY = _IYCount;

	//Ÿ�� ����
	CTexture* pTileTex = CResMgr::GetInstance()->LoadTexture(L"Tile", L"texture\\tera2.bmp");
	
	for (UINT tileIDX = 0; tileIDX < _IYCount; tileIDX++) {
		for (UINT tileJDX = 0; tileJDX < _IXCount; tileJDX++) {
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(tileJDX * TILE_SIZE), (float)(tileIDX * TILE_SIZE)));
			pTile->SetTexture(pTileTex);


			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += _strRelativePath;
	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	//������ �ε�.

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	//��� Ÿ�ϵ��� ���������� ������ �����͸� �ε��ϰ� ��. 
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t tileIdx = 0; tileIdx < vecTile.size(); tileIdx++) {
		((CTile*)vecTile[tileIdx])->Load(pFile);
	}

	fclose(pFile);
}
