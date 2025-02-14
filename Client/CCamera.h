#pragma once


class CObject;
class CCamera
{

	SINGLE(CCamera)

private:
	//�׸����� ���� ī�޶��� ��ǥ�� ���� ����ؼ� ������.
	//�浹 ��ü�� �� ��ǥ�迡 �״��. 

	Vec2			m_vLookAt;			//ī�޶� ���� ��ġ
	Vec2			m_vCurLookAt;		//���� ��ġ�� ���� ��ġ ����. 
	Vec2			m_prevLookAt;		//ī�޶� ���� ���� ������ ��ġ. 
	

	CObject*		m_pTargetObj;		//ī�޶� Ÿ�� ������Ʈ <- ī�޶� �ش� Ÿ���� �i�ƴٴ�. 

	Vec2			m_vDiff;			//�ػ� �߽���ġ��, ī�޶� LootAt���� ���� ��. 
	float			m_fTime;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�. 
	float			m_fSpeed;			//Ÿ���� ���󰡴� �ӵ�. 
	float			m_fAccTime;			//���� �ð�. 

public:
	void SetLookAt(Vec2 _vLook) { 
		m_vLookAt = _vLook; 
		float fmoveDistance = (m_vLookAt - m_prevLookAt).Length();
		m_fSpeed = fmoveDistance / m_fTime;
		m_fAccTime = 0.f;
	
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }


	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) {
		return _vObjPos - m_vDiff;
	}

	Vec2 GetRealPos(Vec2 _vRenderPos) { { return _vRenderPos + m_vDiff; } }

public:
	void update();

private:
	void CalDiff();
};

