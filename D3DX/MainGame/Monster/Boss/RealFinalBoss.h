#pragma once
#include "BossParent.h"

struct ST_HANDMAT
{
	D3DXMATRIX* LeftHand1;	//왼쪽 아래 손
	D3DXMATRIX* LeftHand2;	//왼쪽 위 손
	D3DXMATRIX* RightHand1;	//오른쪽 아래 손
	D3DXMATRIX* RightHand2;	//오른쪽 위 손
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
	//패시브스킬 함수
	virtual void Passive() override;
	//패시브스킬 발동 조건 함수
	//bool AbleSummon();
	//스킬 2 함수
	virtual void Skill2() override;
	//스킬 2 캐스팅함수
	//virtual void Casting() override;

	//등장 애니메이션 순차실행
	void EnterAni();
	//팔 들의 메트리스 지정
	void HandMatInit();

public:
	RealFinalboss();
	virtual ~RealFinalboss();

	virtual void SetupBoss(Map* map, D3DXVECTOR3 pos) override;
};

