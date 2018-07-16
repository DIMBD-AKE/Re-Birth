#include "Character_Shield.h"
#include "../Status.h"



Character_Shield::Character_Shield()
{
	
}


Character_Shield::~Character_Shield()
{
}

void Character_Shield::Init(D3DXVECTOR3 pos)
{

	TEXTUREMANAGER->AddTexture("실드_프론트바", "Texture/PlayerProgressBar/shieldHp.jpg");
	TEXTUREMANAGER->AddTexture("실드_백바", "Texture/PlayerProgressBar/shieldBack.jpg");
	MODELMANAGER->AddModel("렘논", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);

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
	
}

void Character_Shield::Render()
{
	m_pShieldChr->Render();
}

void Character_Shield::Update(D3DXVECTOR3 pos, D3DXVECTOR3 Rot)
{
	m_pShieldChr->World();
	m_pShieldChr->SetPosition(pos);
	m_pShieldChr->SetRotation(Rot);



	KeyControl();
}

void Character_Shield::ChangeSubChrAni()
{
	switch (m_eShieldCondition)
	{
	case SUB_IDLE:
		m_pShieldChr->SetBlendAnimation("IDLE");
		m_pShieldChr->SetBlendTime(0.27);
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
		m_pShieldChr->SetAnimationSpeed(1.0f);
		break;
	case CHAR_NONE:
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
}

