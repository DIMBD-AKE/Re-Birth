#include "Character_Shield.h"
#include "../Status.h"



Character_Shield::Character_Shield()
{
	
}


Character_Shield::~Character_Shield()
{
	SAFE_DELETE(m_pShieldChr);
	SAFE_RELEASE(m_pShieldHp);
	
}

void Character_Shield::Init(D3DXVECTOR3 pos)
{
	// 쉴드 캐릭터 
	ST_SIZEBOX box1;
	box1.highX = 50.0f;
	box1.highY = 180.0f;
	box1.highZ = 50.0f;
	box1.lowX = -50.0f;
	box1.lowY = 10.0f;
	box1.lowZ = -50.0f;

	m_pShieldChr = MODELMANAGER->GetModel("렘논", MODELTYPE_X);
	m_pShieldChr->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	m_pShieldChr->SetPosition(pos);
	

	m_pShieldHp = new UIObject;
	m_pShieldHp->SetTexture(TEXTUREMANAGER->GetTexture("실드_프론트바"));
	UIObject* SbackBar = new UIObject;
	SbackBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
	SbackBar->SetTexture(TEXTUREMANAGER->GetTexture("실드_백바"));
	m_pShieldHp->AddChild(SbackBar);


	m_pShieldChr->CreateBound(box1);
	m_pShieldChr->SetBoundSphere(m_pShieldChr->GetOrigBoundSphere().center, 100.0f);
	
	m_eShieldCondition = SUB_BATTLEREADY;
	ChangeSubChrAni();

	//m_Status->chr.nCurrentHP = 500;
	//m_Status->chr.nMaxHp = 500;
	m_bIsDie = false;
	m_nShieldMaxHp = 1000;
	m_nShieldCurHp = 1000;
	
}

void Character_Shield::Render()
{
	m_pShieldChr->Render();
	m_pShieldHp->Render();
}

void Character_Shield::Update(D3DXVECTOR3 pos, D3DXVECTOR3 Rot)
{
	m_pShieldChr->World();
	m_pShieldChr->SetPosition(pos);
	m_pShieldChr->SetRotation(Rot);
	m_pShieldHp->Update();
	ShieldProgressBar();


	KeyControl();

	//if (m_nShieldCurHp <= 0)
	//{
	//	m_nShieldCurHp = m_nShieldMaxHp;
	//}
}

void Character_Shield::ChangeSubChrAni()
{
	switch (m_eShieldCondition)
	{
	case SUB_IDLE:
		m_pShieldChr->SetBlendAnimation("IDLE");
		m_pShieldChr->SetBlendTime(0.57);
		m_pShieldChr->SetAnimationSpeed(1.0f);
		break;
	case SUB_RUN:
		m_pShieldChr->SetAnimation("MOVE");
		break;
	case SUB_DIE:
		m_pShieldChr->SetAnimation("DIE");
		m_pShieldChr->SetAnimationSpeed(1.0f);
		break;
	case SUB_BATTLEREADY:
		m_pShieldChr->SetAnimation("BATTLEREADY");
		m_pShieldChr->SetBlendTime(0.57);
		m_pShieldChr->SetAnimationSpeed(1.0f);
		break;
	case SUB_NONE:
		break;
	}
}

void Character_Shield::KeyControl()
{
	if (m_pShieldChr->IsAnimationEnd() && m_eShieldCondition == SUB_BATTLEREADY)
	{
		m_eShieldCondition = SUB_IDLE;
		ChangeSubChrAni();
	}
	if (m_pShieldChr->IsAnimationEnd() && m_eShieldCondition == SUB_DIE)
	{
		m_eShieldCondition = SUB_NONE;
		ChangeSubChrAni();
	}
}

void Character_Shield::ShieldProgressBar()
{
	
	float tempC = (float)m_nShieldCurHp / m_nShieldMaxHp;


	m_pShieldHp->SetScale(D3DXVECTOR3(tempC, 1, 1));

	D3DXVECTOR3 ShieldPos = *m_pShieldChr->GetPosition();
	ShieldPos.y += 5.0f;

	auto temp = Convert3DTo2D(ShieldPos);

	ShieldPos.x = temp.x;
	ShieldPos.y = temp.y;
	ShieldPos.z = 0;
	m_pShieldHp->SetPosition(ShieldPos);
	m_pShieldHp->Update();
	
}

void Character_Shield::Die()
{
	m_eShieldCondition = SUB_DIE;
	ChangeSubChrAni();
}

