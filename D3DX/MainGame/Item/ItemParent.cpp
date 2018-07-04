#include "../../stdafx.h"
#include "ItemParent.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Character/CharacterParant.h"

ItemParent::ItemParent()
{
	m_fScale = 0;
}


ItemParent::~ItemParent()
{
}

void ItemParent::SetUp()
{
	m_pTexture = TEXTUREMANAGER->AddTexture("장검", "Texture/Item/장검.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("장검");
	m_pItemStatus = new STATUS;
	SetStatusZero();
}

void ItemParent::Use(CharacterParant& pCharacter)
{
}

void ItemParent::Attack(CharacterParant* pCharacter,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
	for (int i = 0; i < pMonsterManager->GetMonsterManager().size(); ++i)
	{
		D3DXVECTOR3 pos = *(pCharacter->m_pCharacter->GetPosition());
		D3DXVECTOR3 rot = *(pCharacter->m_pCharacter->GetRotation());
		if (pMonsterManager->GetMonsterManager()[i]->GetIsResPawn())continue;
		else
		{
			float radius = pMonsterManager->GetMonsterManager()[i]->GetModel()->GetBoundSphere().radius;
			D3DXVECTOR3 mosPos = *(pMonsterManager->GetMonsterManager()[i]->GetModel()->GetPosition());
			float distance = D3DXVec3Length(&(mosPos - pos));
			if (distance - radius > m_fRange) continue;
			else
			{
				D3DXVECTOR3 delta = mosPos - pos;
				if(atan2(delta.x, delta.z)>m_fScale) continue;

				int Atk = pCharacter->m_Status->chr.nAtk * m_pItemStatus->item.nAtk;



				pMonsterManager->GetMonsterManager()[i]->SetCurrentHP(0);
			}
		}
	}
}

void ItemParent::Skill1(CharacterParant* pCharacter,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
}

void ItemParent::Skill2(CharacterParant* pCharacter,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
}

void ItemParent::SetTarget()
{
}

void ItemParent::SetStatusZero()
{
	this->m_pItemStatus->item.fAgi = 0;
	this->m_pItemStatus->item.fAtkSpeed = 0;
	this->m_pItemStatus->item.fCoolTime1 = 0;
	this->m_pItemStatus->item.fCoolTime2 = 0;
	this->m_pItemStatus->item.fHit = 0;
	this->m_pItemStatus->item.fSpeed = 0;
	this->m_pItemStatus->item.nAtk = 0;
	this->m_pItemStatus->item.nDef = 0;
	this->m_pItemStatus->item.nHp = 0;
	this->m_pItemStatus->item.nSkillAtk1 = 0;
	this->m_pItemStatus->item.nSkillAtk2 = 0;
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
