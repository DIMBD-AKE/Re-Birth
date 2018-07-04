#include "../../stdafx.h"
#include "HealthPotion.h"
#include "../Character/CharacterParant.h"
#include "../Status.h"

HealthPotion::HealthPotion()
{
	m_sName = "�ϱ� ü������";
	m_sItemDescription = "�⺻���� ü�¹��� 100�� HP�� ȸ����Ų��";
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


	m_pTexture = TEXTUREMANAGER->AddTexture("����", "Texture/Item/����.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("����");
}
