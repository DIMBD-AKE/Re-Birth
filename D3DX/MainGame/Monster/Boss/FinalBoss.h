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
	//�нú꽺ų �Լ�
	void Passive();
	//�нú꽺ų �ߵ� ���� �Լ�
	bool AbleSummon();
	//��ų1 �Լ�
	void Skill();
	//��ų 2 �Լ�
	void Skill2();
	//��ų 2 ĳ�����Լ�
	void Casting();

public:
	FinalBoss();
	virtual ~FinalBoss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;

	
};

