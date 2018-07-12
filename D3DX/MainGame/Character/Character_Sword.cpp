#include "../../stdafx.h"
#include "Character_Sword.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"


Character_Sword::Character_Sword()
{
}


Character_Sword::~Character_Sword()
{
}

void Character_Sword::Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager)
{
	m_eChrType = CHRTYPE_SWORD;

	if (order == CHAR_ONE)
	{
		//�Ϻ�����ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī", MODELTYPE_X);

		
		
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 1.0f;
		m_Status->chr.fPhyRate = 1.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 10000;
		m_Status->chr.nCurrentStam = 50;
		m_Status->chr.nDef = 2;
		m_Status->chr.nMaxHp = 10000;
		m_Status->chr.nMaxStam = 50;
		m_Status->chr.fRange = 3.0f;
		m_Status->chr.fScale = 5.0f;
		CharacterParant::Init(map, order, pMonsterManager);
		
		
		//��Ʈ����Ʈ UI
		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));

		//��ųUI
		m_pUISkill->SetTexture(TEXTUREMANAGER->GetTexture("��ī_��ų"));
		m_pUISkill->SetPosition(D3DXVECTOR3(1200, 730, 0));
	}
	else if (order == CHAR_TWO)
	{
		//��Į��ĳ
		m_pCharacter = MODELMANAGER->GetModel("����", MODELTYPE_X);
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 40;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 40;
		m_Status->chr.fRange = 5.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(map, order, pMonsterManager);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));
		//��ųUI
		m_pUISkill->SetTexture(TEXTUREMANAGER->GetTexture("����_��ų"));
		m_pUISkill->SetPosition(D3DXVECTOR3(1200, 730, 0));
	}
	else if (order == CHAR_THREE)
	{
		//������ ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("����", MODELTYPE_X);
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.0f;
		m_Status->chr.fCheRate = 5.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 60.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 60;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 5.0f;
		m_Status->chr.fScale = 30.0f;
		CharacterParant::Init(map, order, pMonsterManager);

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
		m_pUIobj->SetPosition(D3DXVECTOR3(1300, 550, 0));
		//��ųUI
		m_pUISkill->SetTexture(TEXTUREMANAGER->GetTexture("����_��ų"));
		m_pUISkill->SetPosition(D3DXVECTOR3(1200, 730, 0));

	}

}

void Character_Sword::Update()
{
	if (m_pCharacter && m_eCondition != CHAR_NONE)
	{
		Controller();
		//UnderAttacked();
		KeyControl();
		Move();
		
		m_pInventory->Update();
		
		m_pCharacter->World();
		
		m_pUIobj->Update();
		m_pUISkill->Update();
		SkillIconAlpha();
	}
}

void Character_Sword::Render()
{


	if (m_pCharacter && m_eCondition != CHAR_NONE)
	{
		m_pCharacter->Render();
		//CharacterParant::Render();
		m_pInventory->Render();

		//��Ʈ����Ʈ 
		m_pUIobj->Render();
		m_pUISkill->Render();
		
		//if (m_bIsUnderAttacked)
		//{
			AppearDamage();
		//}
		CharacterParant::Render();
	}
}



