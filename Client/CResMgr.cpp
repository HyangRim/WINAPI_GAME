#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"


CResMgr::CResMgr() {

}

CResMgr::~CResMgr() {
	for (auto mapIter : m_mapTex) {
		delete mapIter.second;
	}
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
	else return TextureIter->second;
}
