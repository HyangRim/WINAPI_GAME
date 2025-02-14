#pragma once

//��ũ�δ� �ڵ带 ġȯ�ϴ� ��. 
//���� �Լ��� ȣ���� ���� ��� ����Ī�� ��� �� ����. 
//�������� ��ũ�δ� �Լ��� �ƴ϶�, �״�� �ڵ带 ġȯ�ϴ°Ŷ�

//������ �ٸ� ������ �� �� ����...

//�̷��� �ϸ� ���� ������ �Ű澲�� �ʾƵ� �ȴٴ� ��
//�ݴ�� �̷��� �ϸ��� ����. 
//������ ���� ������ �ϴ� ���.

//SingleTon ��ũ��. 

#define SINGLE(type)public: \
					static type* GetInstance()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					private:\
						type();\
						~type();

#define fDT CTimeMgr::GetInstance()->GetfDT()
#define DT	CTimeMgr::GetInstance()->GetDT()

#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key, state) CkeyMgr::GetInstance()->GetKeyState(key) == state

#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define MOUSE_POS CkeyMgr::GetInstance()->GetMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 64

enum class GROUP_TYPE {
	DEFAULT,
	TILE,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE {
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE {
	HOLLOW,
	END,
};

enum class PEN_TYPE {
	RED,
	GREEN, 
	BLUE,
	END,
};



enum class EVENT_TYPE {
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,




	END,
};