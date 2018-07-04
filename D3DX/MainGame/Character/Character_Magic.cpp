#include "../../stdafx.h"
#include "Character_Magic.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Magic::Character_Magic()
{
}


Character_Magic::~Character_Magic()
{
}


void Character_Magic::Init(Map * map, CHARSELECT order)
{
	m_eChrType = CHRTYPE_MAGIC;

	if (order == CHAR_ONE)
	{
		//���� ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī��", MODELTYPE_X);
		//
		m_Status->chr.fAgi = 30.0f;
		m_Status->chr.fAtkSpeed = 55.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 5.0f;
		m_Status->chr.fMagicRate = 65.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 35;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		CharacterParant::Init(map, order);
	}
	else if (order == CHAR_TWO)
	{
		//���� ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("�콺Ƽ��", MODELTYPE_X);
		m_Status->chr.fAgi = 30.0f;
		m_Status->chr.fAtkSpeed = 55.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 5.0f;
		m_Status->chr.fMagicRate = 65.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 35;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 10;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 10;
		CharacterParant::Init(map, order);
	}
}

void Character_Magic::Update()
{
	if (m_pCharacter)
	{
		Controller();
		KeyControl();
		Move();
		m_pInventory->Update();

		m_pCharacter->World();
		m_pCharacter->Update();
	}
}

void Character_Magic::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		m_pInventory->Render();
	}
}


