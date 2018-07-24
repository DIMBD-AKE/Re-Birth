#pragma once
#include "CharacterParant.h"
enum FISTBODY
{
	FISTBODY_LEFTHAND,
	FISTBODY_RIGHTHAND,
	FISTBODY_LEFTLEG,
	FISTBODY_RIGHTLEG,
	FISTBODY_END
};

class Character_fist :
	public CharacterParant
{
private:

	D3DXMATRIX*				m_pFistBody[FISTBODY_END];			//�� ��Ʈ���� �ޱ� ����
	ST_SPHERE				m_stBound[FISTBODY_END];			//�ٿ�� �ڽ� ����� ����

	float					m_fAttackInterval;					//���ÿ� ���͹�


public:
	Character_fist();
	virtual ~Character_fist();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();
	void Debug();

};

