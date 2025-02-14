#pragma once


#include "global.h"
//���漱���ϴ� ������ ������ �ӵ��� ������ ���� �ʱ� ����. 
class CObject;


class CScene
{

private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];		//���� �ȿ� ��� ������Ʈ ���� �ְڴ�. �̷� Ư��(���)�� ������ŭ �����ֱ�.
	//�޸����ϸ� �׷� ������ŭ �����ֱ�.

	wstring			m_strName; //Scene �̸�

	UINT			m_iTileX;		//Ÿ�� ���� ����
	UINT			m_iTileY;		//Ÿ�� ���� ����. 

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	
	virtual void Enter() = 0;		//�ش� Scene�� ���� �� ȣ��.
	virtual void Exit() = 0;		//�ش� Scene�� Ż�� �� ȣ��.



public:
	//Ŭ������ ����� �����ϸ� �ζ��� ó���� ��. 
	//���� �Լ� ȣ�� ����� �����. 
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) 
	{
		return m_arrObj[(UINT)_eType];
	}

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	void DeleteGroup(GROUP_TYPE _eGroup);
	void DeleteAll();
	void CreateTile(UINT _IXCount, UINT _IYCount);
	void LoadTile(const wstring& _strRelativePath);

public:
	CScene();

	//�Ҹ����� �����Լ� �������. �� �Ŵ����� ��� Scene�� �θ� �����ͷ� ������.
	// CSceneMgr���� ���� �Ҹ��ų��, �Ҹ��ڴ� �θ��� CScene�� ȣ���.  
	virtual ~CScene();
};

