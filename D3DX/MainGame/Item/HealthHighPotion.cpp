#include "../../stdafx.h"
#include "HealthHighPotion.h"
#include "../Status.h"
#include "../Character/CharacterParant.h"

HealthHighPotion::HealthHighPotion()
{
	m_fHealAmount = 0.25f;
	m_sItemDescription = EQUIP_POTION;
}


HealthHighPotion::~HealthHighPotion()
{
}

void HealthHighPotion::SetUp()
{
	m_pTexture = TEXTUREMANAGER->AddTexture("상급포션", "Texture/Item/상급포션.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("상급포션");
}

void HealthHighPotion::Use(CharacterParant & pCharacter)
{
	pCharacter.m_Status->chr.fCurrentHP += pCharacter.m_Status->chr.fMaxHp*m_fHealAmount;
}
