#include "../../../stdafx.h"
#include "HealthHighPotion.h"
#include "../../Status.h"
#include "../../Character/CharacterParant.h"

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
	m_pTexture = TEXTUREMANAGER->AddTexture("HealthHighPotion", "Texture/Item/Item Num 201 Magic HealthHighPoition.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("HealthHighPotion");
}

void HealthHighPotion::Use(CharacterParant & pCharacter)
{
	pCharacter.m_Status->chr.nCurrentHP += pCharacter.m_Status->chr.nMaxHp*m_fHealAmount;
}
