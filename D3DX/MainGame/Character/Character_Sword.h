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
	void Shunpo(); //일본도 여캐 스킬
	void Bash(); // 긴머리 여검사 리아 스킬
	void GrabSlash(); //전기톱 여캐 벨벳 스킬

	void SkillDealing();
	void SkillEnemyMoving();
	//
};
