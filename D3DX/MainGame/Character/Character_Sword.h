#pragma once
#include "CharacterParant.h"
class Character_Sword :
	public CharacterParant
{
private:
	//
	bool m_bIsFskill;
	int m_nDC;
	float m_fDeltaY;
	float m_fDelta;
	bool m_bEnemySkillMoving;
	bool m_bIsTarget;
	float VskillInterval;
	D3DXMATRIX*	 velvetFinal;
	float		m_fVelvetInterval;
	D3DXVECTOR3		m_vVelvetFinal;
	bool			m_bIsVelvetFinal;
	int				m_nVelvetCount;
	int				m_nVelvetEnd;
	float			m_fOriginSpeed;
	vector<EffectObject*>	m_vecSkillEffect;
	//

public:
	Character_Sword();
	virtual ~Character_Sword();


	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void Attack();

	//skill 
	void Shunpo(); //�Ϻ��� ��ĳ ��ų
	void Bash(); // ��Ӹ� ���˻� ���� ��ų
	void GrabSlash(); //������ ��ĳ ���� ��ų

	void SkillDealing();
	void SkillEnemyMoving();
	void TargetSword();
	void velvetFinalSKILL();
	void VelvetCount();

	void SkillEffect();
	//
};
