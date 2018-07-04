#include "../../stdafx.h"
#include "HealthHighPotion.h"
#include "../Status.h"
#include "../Character/CharacterParant.h"

HealthHighPotion::HealthHighPotion()
{
	m_sName = "상급 체력포션";
	m_sItemDescription = "상급 치유 물약 최대체력의 25퍼센트를 회복시킨다";
	m_fHealAmount = 0.25f;
	m_stEquipType = EQUIP_POTION;
	m_nId = 2;
}


HealthHighPotion::~HealthHighPotion()
{
}

void HealthHighPotion::SetUp()
{
	m_pItemStatus = new STATUS;
	SetStatusZero();
	m_pTexture = TEXTUREMANAGER->AddTexture("상급포션", "Texture/Item/상급포션.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("상급포션");
}

void HealthHighPotion::Use(CharacterParant & pCharacter)
{
	pCharacter.m_Status->chr.nCurrentHP += pCharacter.m_Status->chr.nMaxHp*m_fHealAmount;
}
