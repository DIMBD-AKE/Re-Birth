#include "../../stdafx.h"
#include "HealthHighPotion.h"
#include "../Status.h"
#include "../Character/CharacterParant.h"

HealthHighPotion::HealthHighPotion()
{
	m_sName = "��� ü������";
	m_sItemDescription = "��� ġ�� ���� �ִ�ü���� 25�ۼ�Ʈ�� ȸ����Ų��";
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
	m_pTexture = TEXTUREMANAGER->AddTexture("�������", "Texture/Item/�������.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("�������");
}

void HealthHighPotion::Use(CharacterParant & pCharacter)
{
	pCharacter.m_Status->chr.nCurrentHP += pCharacter.m_Status->chr.nMaxHp*m_fHealAmount;
}
