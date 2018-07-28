#pragma once
#include "CharacterParant.h"
class Character_Magic :
	public CharacterParant
{
private:
	int					m_nMagicCount;				//Ŭ��ī��Ʈ ����
	Particle*			m_pMeteorPaticle;			//���׿� ��ƼŬ����
	Particle*			m_pMegaCristalPaticle;		//�ް�ũ����Ż ��ƼŬ����
	Particle*			m_pMeteorAfterPaticle;		//���׿� ������ �ܿ���ƼŬ 

	bool				m_bIsFire;					//�ܿ� ��Ʈ��

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

