#pragma once
#include "BossParent.h"

struct ST_HANDMAT
{
	D3DXMATRIX* LeftHand1;	//���� �Ʒ� ��
	D3DXMATRIX* LeftHand2;	//���� �� ��
	D3DXMATRIX* RightHand1;	//������ �Ʒ� ��
	D3DXMATRIX* RightHand2;	//������ �� ��
};

class RealFinalboss :
	public BossParent
{
	ST_HANDMAT m_stHandMat;
	//virtual void ChangeAni() override;

	virtual void Pattern() override;

	virtual void SetupStat() override;
	virtual void SetupSkill() override;

	virtual void SetupSkill2() override;

	virtual void Attack() override;
	virtual void Move() override;
	virtual void SkillUse() override;
	//�нú꽺ų �Լ�
	virtual void Passive() override;
	//�нú꽺ų �ߵ� ���� �Լ�
	//bool AbleSummon();
	//��ų 2 �Լ�
	virtual void Skill2() override;
	//��ų 2 ĳ�����Լ�
	//virtual void Casting() override;

	//���� �ִϸ��̼� ��������
	void EnterAni();
	//�� ���� ��Ʈ���� ����
	void HandMatInit();

public:
	RealFinalboss();
	virtual ~RealFinalboss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;
};

