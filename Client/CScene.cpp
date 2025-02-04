#include "pch.h"
#include "CScene.h"
#include "CObject.h"





CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {
			//m_arrObj[그룹][물체] 삭제. 
			delete m_arrObj[typeIDX][objIDX];
		}
		
		//씬이 사라지면, 그 씬의 벡터들도 다 사라짐. 
		//STL의 RAII가 알아서 삭제하기 때문. 
	}
}

void CScene::update()
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {
			m_arrObj[typeIDX][objIDX]->update();
		}
	}
}
//움직이고 했던 걸, 마지막으로 업데이트 함. 
//충돌체가 플레이어 따라가게 함, 충돌 처리. 
void CScene::finalupdate()
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {
			m_arrObj[typeIDX][objIDX]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT typeIDX = 0; typeIDX < (UINT)GROUP_TYPE::END; typeIDX++) {
		for (size_t objIDX = 0; objIDX < m_arrObj[typeIDX].size(); objIDX++) {
			m_arrObj[typeIDX][objIDX]->render(_dc);
		}
	}
}
