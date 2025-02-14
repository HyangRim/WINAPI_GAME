#pragma once


#include "global.h"
class CAnimator;
class CTexture;

//�����Ӹ��� ������ ���� ����.

//vLT : �»��. vSlice : �ڸ� ����. fDuration : �� �����ӿ��� �ӹ��� �ð�. 
//�� �����ӿ��� �ӹ��� �ð�. 
struct tAnimFrm {
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
	float	fDuration;
};

class CAnimation
{
private:
	wstring					m_strName;
	CAnimator*				m_pAnimator;

	CTexture*				m_pTex;			//Animation�� ����ϴ� �ؽ���
	vector<tAnimFrm>		m_vecFrm;		//��� ������ ����
	int						m_iCurFrm;		//���� ������. 
	float					m_fAccTime;		//�ð� ����
	int						m_iFrameCount;


	bool					m_bFinish;		//�ִϸ��̼��� �������� �˸�. 



public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT iFrameCount);


public:
	const wstring& GetName() { return m_strName; }
	bool	IsFinish() { return m_bFinish; }

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	void SetFrame(int _iframeIDX) {
		m_bFinish = false;
		m_iCurFrm = _iframeIDX;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIDX) {
		return m_vecFrm[_iIDX];
	}
	
	int GetMaxFrame() { return static_cast<UINT>(m_vecFrm.size()); }
public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

