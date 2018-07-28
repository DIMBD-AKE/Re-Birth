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
	//
};
