#include "../../stdafx.h"
#include "BasicSword.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Character/CharacterParant.h"



BasicSword::BasicSword()
{
	m_sName = "장검";
	m_sItemDescription = "기본 지급되는 장검 균형이 잘 잡혀있다";
	m_stEquipType = EQUIP_FIRSTWEAPON;
	m_nId = 10;
	
}


BasicSword::~BasicSword()
{
}

void BasicSword::SetUp()
{
	m_pItemStatus = new STATUS;
	SetStatusZero();

	m_pItemStatus->item.fAtkSpeed = 1.0f;
	m_pItemStatus->item.fCoolTime1 = 10.0f;
	m_pItemStatus->item.fCoolTime2 = 0.0f;
	m_pItemStatus->item.fHit = 0.5f;
	m_pItemStatus->item.fSpeed = 10.0f;
	m_pItemStatus->item.nAtk = 5;
	m_pItemStatus->item.nSkillAtk1 = 10;

	m_pTexture = TEXTUREMANAGER->AddTexture("Normal Blade", "Texture/Item/Item Num 321 Normal Blade.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("Normal Blade");
}
