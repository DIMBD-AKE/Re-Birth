#pragma once
#include "BossParent.h"

class FinalBoss :
	public BossParent
{

protected:

	virtual void DropItemSetup() override;

	virtual void ChangeAni() override;

	virtual void Pattern() override;

	virtual void SetupStat() override;
	virtual void SetupSkill() override;

	virtual void Attack() override;
	virtual void Move() override;
	virtual void SkillUse() override;
	//패시브스킬 함수
	void Passive();
	//패시브스킬 발동 조건 함수
	bool AbleSummon();
	//스킬1 함수
	void Skill();
	//스킬 2 함수
	void Skill2();
	//스킬 2 캐스팅함수
	void Casting();

public:
	FinalBoss();
	virtual ~FinalBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;

	
};

