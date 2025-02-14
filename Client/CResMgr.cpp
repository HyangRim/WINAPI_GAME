#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"


CResMgr::CResMgr() {

}

CResMgr::~CResMgr() {

	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	//�̹� �ؽ��İ� map�� �ִ��� ������.
	CTexture* pTex = FindTexture(_strKey);

	//�̹� �ִٸ� �׳� �������ֱ�. 
	if (pTex != nullptr) return pTex;


	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	//Ű�� ����θ� ���ҽ��� ������ �˵��� ����. 
	//�����ΰ� � �̸�����, � ������� �˵��� ����. 
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);


	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	auto TextureIter = m_mapTex.find(_strKey);

	if (TextureIter == m_mapTex.end()) return nullptr;
	else return (CTexture*)TextureIter->second;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	//�̹� �ؽ��İ� map�� �ִ��� ������.
	CTexture* pTex = FindTexture(_strKey);

	//�̹� �ִٸ� �׳� �������ֱ�. 
	if (pTex != nullptr) return pTex;


	pTex = new CTexture;
	pTex->Create(_iWidth, _iHeight);

	//Ű�� ����θ� ���ҽ��� ������ �˵��� ����. 
	//�����ΰ� � �̸�����, � ������� �˵��� ����. 
	pTex->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}
