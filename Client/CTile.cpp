#include "pch.h"
#include "CTile.h"

#include "CTexture.h"


CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
	
}
//Tool Scene�� ���ؼ� Ÿ���� ��ġ�� �ڽ��� �ڵ尡 �ƴ� ������� ��ġ�� �� �־�� �ϴµ�.
//Ÿ���� ���������� �ǵ����, �� Ÿ���� ������ �ٲ� �� �־����. 

//�׸��� ���� & �ε尡 �����ؾ���. 
void CTile::update()
{

}

void CTile::render(HDC _dc)
{

	if (m_pTileTex == nullptr || -1 == m_iImgIdx) {
		return;
	}

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT IMaxCol = iWidth / TILE_SIZE;
	UINT IMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = (UINT)(m_iImgIdx / IMaxCol);
	UINT iCurCol = (UINT)(m_iImgIdx % IMaxCol);

	Vec2 vRenderPos = CCamera::GetInstance()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	if (IMaxRow <= iCurRow) {
		assert(nullptr);
	}
	
	BitBlt(_dc,
		(int)(vRenderPos.x),
		(int)(vRenderPos.y),
		(int)(vScale.x),
		(int)(vScale.y),
		m_pTileTex->GetDC(),
		iCurRow * TILE_SIZE,
		iCurCol * TILE_SIZE,
		SRCCOPY);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
