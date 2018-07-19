#include "../../stdafx.h"
#include "ItemParent.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Character/CharacterParant.h"
#include "../SkillManager.h"


ItemParent::ItemParent()
	:m_pItemStatus(NULL)
	,m_pTexture(NULL)
	,m_pParticle(NULL)
{
}


ItemParent::~ItemParent()
{
	SAFE_DELETE(m_pItemStatus);
	SAFE_DELETE(m_pParticle);
	SAFE_DELETE(m_pSkill1);
	SAFE_DELETE(m_pSkill2);
	m_pTexture = NULL;
	int a = 0;
}

ItemParent * ItemParent::Clone()
{
	return new ItemParent(*this);
}

void ItemParent::SetUp()
{
	m_pItemStatus = new STATUS;
	SetStatusZero();
}

void ItemParent::Update()
{
	Skill1CoolTime();
	Skill2CoolTime();
	if (m_pSkill1) m_pSkill1->Update();
	if (m_pSkill2) m_pSkill2->Update();
}

void ItemParent::Render()
{
	if (m_pSkill1)
	{
		m_pSkill1->Render();

		SPRITE_BEGIN;
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		world._41 = 1200;
		world._42 = 600;
		SPRITE->SetTransform(&world);

		float CoolTime = (m_pItemStatus->item.fCoolTime1 - m_fSkill1CurrentCooltime) * 255 / m_pItemStatus->item.fCoolTime1;

		int alpha = CoolTime;
		TEXT->Add(to_string(int(m_fSkill1CurrentCooltime)), 1225, 625, 50, "³ª´®¸íÁ¶");
		

		SPRITE->Draw(m_pSkill1->GetIcon(), NULL, NULL, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		SPRITE_END;

		TEXT->Render();

	}
	if (m_pSkill2) m_pSkill2->Render();
}

void ItemParent::Use(CharacterParant& pCharacter)
{
	if (m_nId == 3)
	{
		pCharacter.SetCurrentHP(pCharacter.Getstatus()->chr.nCurrentHP + pCharacter.Getstatus()->chr.nMaxHp*0.75);
	}
	else if (m_nId == 103)
	{
		pCharacter.SetCurrentHP(pCharacter.Getstatus()->chr.nCurrentHP + pCharacter.Getstatus()->chr.nMaxHp*0.5);
	}
	else if (m_nId == 203)
	{
		pCharacter.SetCurrentHP(pCharacter.Getstatus()->chr.nCurrentHP + pCharacter.Getstatus()->chr.nMaxHp*0.30);
	}
	else if (m_nId == 303)
	{
		pCharacter.SetCurrentHP(pCharacter.Getstatus()->chr.nCurrentHP + pCharacter.Getstatus()->chr.nMaxHp*0.15);
	}
	else if (m_nId == 201)
	{
		pCharacter.SetCurrentHP(pCharacter.Getstatus()->chr.nCurrentHP + pCharacter.Getstatus()->chr.nMaxHp*0.15);
	}

	if (pCharacter.Getstatus()->chr.nCurrentHP > pCharacter.Getstatus()->chr.nMaxHp)pCharacter.SetCurrentHP(pCharacter.Getstatus()->chr.nMaxHp);
}

bool ItemParent::Skill1(CharacterParant* pCharacter, MonsterManager* pMonsterManager)
{
	if (m_pSkill1 && m_bSkill1Able)
	{
		m_pSkill1->Prepare(pCharacter, pMonsterManager->GetMonsterVector()[0], pMonsterManager->GetMonsterVector(), *m_Skill1Data, SKILLO_CHARACTER);
		m_pSkill1->Trigger();
		m_fSkill1CurrentCooltime = m_pItemStatus->item.fCoolTime1;
		return true;
	}
	return false;
}

bool ItemParent::Skill2(CharacterParant* pCharacter, MonsterManager* pMonsterManager)
{
	if (m_pSkill2 && m_bSkill2Able)
	{
		m_pSkill2->Prepare(pCharacter, NULL, pMonsterManager->GetMonsterVector(), *m_Skill2Data, SKILLO_CHARACTER);
		m_pSkill2->Trigger();
		m_fSkill2CurrentCooltime = m_pItemStatus->item.fCoolTime2;
		return true;
	}
	return false;
}

void ItemParent::SetStatusZero()
{
	ZeroMemory(m_pItemStatus, sizeof(STATUS));
	m_fSkill1CurrentCooltime = 0.0f;
	m_fSkill2CurrentCooltime = 0.0f;
	m_bSkill1Able = true;
	m_bSkill2Able = true;
}

void ItemParent::SetStatus(STATUS stat)
{
		m_pItemStatus->item.fAgi = stat.item.fAgi;
		m_pItemStatus->item.fAtkSpeed = stat.item.fAtkSpeed;
		m_pItemStatus->item.fCoolTime1 = stat.item.fCoolTime1;
		m_pItemStatus->item.fCoolTime2 = stat.item.fCoolTime2;
		m_pItemStatus->item.fHit = stat.item.fHit;
		m_pItemStatus->item.fSpeed = stat.item.fSpeed;
		m_pItemStatus->item.nAtk = stat.item.nAtk;
		m_pItemStatus->item.nDef = stat.item.nDef;
		m_pItemStatus->item.nHp = stat.item.nHp;
		m_pItemStatus->item.nSkillAtk1 = stat.item.nSkillAtk1;
		m_pItemStatus->item.nSkillAtk2 = stat.item.nSkillAtk2;
}

bool ItemParent::Skill1CoolTime()
{
	if (m_fSkill1CurrentCooltime > 0) m_bSkill1Able = false;

	if (!m_bSkill1Able)
	{
		m_fSkill1CurrentCooltime -= TIME->GetElapsedTime();
		if (m_fSkill1CurrentCooltime <= 0)
		{
			m_bSkill1Able = true;
			m_fSkill1CurrentCooltime = 0;
		}
	}

	return m_bSkill1Able;
}

bool ItemParent::Skill2CoolTime()
{
	if (m_fSkill2CurrentCooltime > 0) m_bSkill2Able = false;

	if (!m_bSkill2Able)
	{
		m_fSkill2CurrentCooltime -= TIME->GetElapsedTime();
		if (m_fSkill2CurrentCooltime <= 0)
		{
			m_bSkill2Able = true;
			m_fSkill2CurrentCooltime = 0;
		}
	}

	return m_bSkill2Able;
}

void ItemParent::Render(D3DXVECTOR3 pos, float size)
{
	D3DXMATRIX	mat;

	float scaleX = size / (float)m_imageInfo.Width;
	float scaleY = size / (float)m_imageInfo.Height;

	D3DXMatrixScaling(&mat, scaleX, scaleY, 1);

	mat._41 = pos.x;
	mat._42 = pos.y;
	mat._43 = pos.z;

	SPRITE->SetTransform(&mat);

	SPRITE->Draw(m_pTexture, NULL, NULL, NULL, 0xffffffff);

}

void ItemParent::EffectRender(D3DXVECTOR3 pos)
{
	if (m_pParticle)
	{
		m_pParticle->SetPosition(pos);
		m_pParticle->World();
		m_pParticle->Update();
		m_pParticle->Render();
	}
}
