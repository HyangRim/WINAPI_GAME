#pragma once


class CObject;
class CTexture;
enum class CAM_EFFECT {
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect {
	CAM_EFFECT	eEffect;			//ī�޶� ȿ��
	float		fDuration;		//ȿ�� �ִ� ���� �ð�.
	float		fCurTime;			// ī�޶� ȿ�� ���� ����� �ð�. 
};

class CCamera
{

	SINGLE(CCamera)

private:
	//�׸����� ���� ī�޶��� ��ǥ�� ���� ����ؼ� ������.
	//�浹 ��ü�� �� ��ǥ�迡 �״��. 

	Vec2				m_vLookAt;			//ī�޶� ���� ��ġ
	Vec2				m_vCurLookAt;		//���� ��ġ�� ���� ��ġ ����. 
	Vec2				m_prevLookAt;		//ī�޶� ���� ���� ������ ��ġ. 
	

	CObject*			m_pTargetObj;		//ī�޶� Ÿ�� ������Ʈ <- ī�޶� �ش� Ÿ���� �i�ƴٴ�. 

	Vec2				m_vDiff;			//�ػ� �߽���ġ��, ī�޶� LootAt���� ���� ��. 
	float				m_fTime;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�. 
	float				m_fSpeed;			//Ÿ���� ���󰡴� �ӵ�. 
	float				m_fAccTime;			//���� �ð�. 

	list<tCamEffect>	m_listCamEffect;
	CTexture* m_pVeilTex;			//ī�޶� ������ �ؽ���(����������)

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

	void FadeIn(float _fDuration) {
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == ef.fDuration) assert(nullptr);
	}
	void FadeOut(float _fDuration) {
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == ef.fDuration) assert(nullptr);
	}

public:

	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();
};

