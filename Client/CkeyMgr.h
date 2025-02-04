#pragma once


//#include �Ŵ� �� ������. �׷���. 




//�������̱� ������, �� ������ �ð��� ������ ��. DT��� �ð��� ������ŭ ���� �������� ������ -> �׷��� �׸� �� �츮�� ��
//A ��ü�� �̵������� ��, B��ü���� ���� �Ͼ �ǰ�? �װ� �ƴ��� �ʳ�? �׷��� ���������ζ�� �׷��� ��. 

//�� ��� �۾��� �Ϸ� ���� �� ��ΰ� ���ÿ� �Ͼ ������� ���߸� ��. 
//���� ������ ó�� �ް�, ������ ó�� ���� ���Ҽ��� ����. 
// 
//���� KeyManager�� �ʿ��� ���� 
//1. ������ ����ȭ. �� �����ӿ� ��� �Ͼ�� ��. 

//2. �����쿡�� ������� �Լ��δ� ��ü���� �̺�Ʈ�� ����Ǿ� ���� ����
//EX) ����Ű�� �����ִٸ� �ñ��� �� �ƴ϶�, �̹��� ���ȴ�(Down), �̹��� �´�(Up) <- �̷� �͵� �����������. 
#include "define.h"



//Ű ����.
enum class KEY_STATE {
	TAP,	//�� ���� ����
	HOLD,	//������ �ִ�
	AWAY,	//�� �� ����
	NONE,	// ������ ���� ����. �������� ������ ���� ����. 
};


//�������� �� �ִ� Ű 

enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	
	LAST,
};

struct tKeyInfo{
	KEY_STATE		eState;			//Ű�� ���°�. 
	bool			bPrevPush;		//������ �� Ű�� ���ȴ��� �� ���ȴ���
};
class CkeyMgr
{
	SINGLE(CkeyMgr);

private:
	//������ INDEX����, �� KEY��. 
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();


public:
	KEY_STATE GetKeyState(KEY _eKey) {
		return m_vecKey[(int)_eKey].eState;
	};
};

