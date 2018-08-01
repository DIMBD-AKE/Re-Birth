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

	D3DXMATRIX*				m_pFistBody[FISTBODY_END];			//본 매트릭스 받기 위함
	ST_SPHERE				m_stBound[FISTBODY_END];			//바운드 박스 씌우기 위함
	D3DXMATRIX*				m_pDummyRoot;						//파이란 본 더미루트
	D3DXVECTOR3				m_vDummyVector;						//더미루트 점벡터
	float					m_fAttackInterval;					//어택용 인터벌
	int						m_nDC;
	float					m_fGumgangInterval;					//금강불괴 인터벌

public:
	Character_fist();
	virtual ~Character_fist();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();
	void Debug();

	void Skill1();
	void Skill2();
	void SkillDealing();


};

