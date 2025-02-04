#pragma once

class CObject;
//������Ʈ�� ������ �˻��ϴ� ������ ����. 

//�浹ü�� �׳� ������Ʈ�� �����ǿ� �ִٸ�, �浹ü�� �Ӹ��������� ���, ���뿡 �浹ü ���� ���� ���...
//�������� ���� �浹ü �δ� �׷� �� ���ؼ�.



//1. �浹�� �׷캰. (�׷��� Scene������ �׷캰�� ������...)
//ex) Player <-> Monster�̷���. 
class CCollider
{
private:
	static UINT g_iNextID;		//

	CObject*	m_pOwner;		//collider�� �����ϰ� �ִ� ������Ʈ. 

	Vec2		m_vOffsetPos;	//������Ʈ�κ��� ������� ��ġ. 
	Vec2		m_vFinalPos;	//�� ������ finalupdate���� ����. 
	Vec2		m_vScale;		//�浹ü�� ũ��. 

	UINT		m_iID;			//�浹ü ������ ID��. 
	UINT		m_iCol;

public:

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:

	void finalupdate();
	void render(HDC _dc);


public:
	//�浹 ���� �Լ�. 
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);


	//���� ������ ����. 
	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);

	
	~CCollider();

	friend class CObject;
};

