#include "../../stdafx.h"
#include "HealthPotion.h"
#include "../Character/CharacterParant.h"
#include "../Status.h"

HealthPotion::HealthPotion()
{
	m_sName = "하급 체력포션";
	m_sItemDescription = "기본적인 체력물약 100의 HP를 회복시킨다";
	m_fHealAmount = 100;
	m_stEquipType = EQUIP_POTION;
	m_nId = 1;
}


HealthPotion::~HealthPotion()
{
}

void HealthPotion::SetUp()
{
	m_pItemStatus = new STATUS;
	SetStatusZero();


	m_pTexture = TEXTUREMANAGER->AddTexture("HealthPotion", "Texture/Item/Item Num 301 Normal HealthPotion.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("HealthPotion");
}
