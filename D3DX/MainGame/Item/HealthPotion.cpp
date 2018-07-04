#include "../../stdafx.h"
#include "HealthPotion.h"
#include "../Character/CharacterParant.h"


HealthPotion::HealthPotion()
{
	m_fHealAmount = 100;
	m_sItemDescription = EQUIP_POTION;
}


HealthPotion::~HealthPotion()
{
}

void HealthPotion::SetUp()
{
	m_pTexture = TEXTUREMANAGER->AddTexture("����", "Texture/Item/����.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("����");
}
