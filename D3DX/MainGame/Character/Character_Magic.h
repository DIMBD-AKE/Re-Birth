#pragma once
#include "CharacterParant.h"
class Character_Magic :
	public CharacterParant
{
private:
	int					m_nMagicCount;				//클릭카운트 변수
	Particle*			m_pMeteorPaticle;			//메테오 파티클변수
	Particle*			m_pMegaCristalPaticle;		//메가크리스탈 파티클변수
	Particle*			m_pMeteorAfterPaticle;		//메테오 끝나고 잔열파티클 

	bool				m_bIsFire;					//잔열 컨트롤

public:
	Character_Magic();
	virtual ~Character_Magic();

	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();
	void targetAttack();
	void CristalField();
	void FireBall();
	void MgSkill();
	void Meteor();
	void MeteorClick();
	void MeteorDamage();
	void MegaCristalReady();
	void MegaCristal();
	void MegaCristalDamage();
	void VskillUpdate();
	void MeteorAfter();
	
};

