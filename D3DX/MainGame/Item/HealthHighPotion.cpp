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
	m_pTexture = TEXTUREMANAGER->AddTexture("�������", "Texture/Item/�������.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("�������");
}

void HealthHighPotion::Use(CharacterParant & pCharacter)
{
	pCharacter.m_Status->chr.fCurrentHP += pCharacter.m_Status->chr.fMaxHp*m_fHealAmount;
}
