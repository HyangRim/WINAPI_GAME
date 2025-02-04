#pragma once

//������Ʈ��� ��, ���� �θ���� �༮. ������Ʈ���� ������ ���� 
//� �� UI, � �� ĳ����... 

//������Ʈ�� �ϰ������� ������ �༮�� �ʿ���. -> Scene

//�� ������Ʈ�� �θ� Ŭ����. -> ��ӹ��� ������Ʈ�� Scene�� ������Ʈ ������
//�θ��ʿ� �����Ǿ��ִ� update�Ӹ� �ƴ϶�, �� ������Ʈ(�ڽ�)�� ������ update�� �ϰ� ����


//�浹�� ������Ʈ, �浹���� ���� ������Ʈ(UI, �����...) <- �̷� ������ ��� Ʈ��ó�� ������ �� ���ܰ� �������� ����. 
// ���� ��ǰ����� ������ �ʿ���(������Ʈ ����)
//������ 

class CCollider;

class CObject
{

private:
	wstring			m_ObjName;
	Vec2			m_vPos;
	Vec2			m_vScale;

	CCollider*		m_pCollider;


	bool			m_bAlive;			//�ڱ� �ڽ��� Ȱ��ȭ or ��Ȱ��ȭ. (���� ����)
	bool			m_bEnable;			//�Ͻ����� Ȱ��ȭ or ��Ȱ��ȭ. 

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }


	void SetName(const wstring& _strName) { m_ObjName = _strName; }
	const wstring& GetName() { return m_ObjName; }


	CCollider* GetCollider() { return m_pCollider; }


	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};


	bool IsDead() {
		return !m_bAlive;
	}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void update() = 0;

	//�θ𿡼� �Լ��� ������ ������, �ڽĿ��� �������̵� ���ϰ� ����. 
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};