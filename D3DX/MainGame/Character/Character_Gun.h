#pragma once
#include "CharacterParant.h"
class Character_Gun :
	public CharacterParant
{
protected:

	bool				m_bshoot;	//Å¾ºä½Ã ÃÑ½ú´Ï?
	EffectObject*		m_pMagicBullet;
	vector<Particle*>	m_vecWindStorm;
	float				m_fWindTime;

public:
	Character_Gun();
	virtual ~Character_Gun();


	

	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();
	void MultiAttack();
	void setCameraView();
	void GunClick();
	void GunShot();

	void MagicBullet();
	void MagicBulletUpdate();

	void WindStorm();
	void WindStormUpdate();

	int FindNearTarget(int ignore, D3DXVECTOR3 pos, float angle, float maxLength);
	int FindRandomTarget(int ignore, D3DXVECTOR3 pos, float angle, float maxLength);
};

