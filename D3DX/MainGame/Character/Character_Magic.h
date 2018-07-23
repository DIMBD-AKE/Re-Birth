#pragma once
#include "CharacterParant.h"
class Character_Magic :
	public CharacterParant
{
private:
	int					m_nMagicCount;			//클릭카운트 변수
	Particle*			m_pMeteorPaticle;		//메테오 파티클변수
	Particle*			m_pMegaCristalPaticle;		//메테오 파티클변수
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
	void MgShield();
	void Meteor();
	void MeteorClick();
	void MeteorDamage();
	void MegaCristalReady();
	void MegaCristal();
	void MegaCristalDamage();
	void VskillUpdate();
	
};

