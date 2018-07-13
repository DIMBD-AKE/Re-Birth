#include "../../stdafx.h"
#include "ItemParent.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Character/CharacterParant.h"

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

void ItemParent::Use(CharacterParant& pCharacter)
{

}

void ItemParent::Attack(CharacterParant* pCharacter,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
	//for (int i = 0; i < pMonsterManager->GetMonsterManager().size(); ++i)
	//{
	//	D3DXVECTOR3 pos = *(pCharacter->GetCharacter()->GetPosition());
	//	D3DXVECTOR3 rot = *(pCharacter->GetCharacter()->GetRotation());
	//	if (pMonsterManager->GetMonsterManager()[i]->GetIsResPawn())continue;
	//	else
	//	{
	//		float radius = pMonsterManager->GetMonsterManager()[i]->GetModel()->GetBoundSphere().radius;
	//		D3DXVECTOR3 mosPos = *(pMonsterManager->GetMonsterManager()[i]->GetModel()->GetPosition());
	//		float distance = D3DXVec3Length(&(mosPos - pos));
	//		if (distance - radius > m_fRange) continue;
	//		else
	//		{
	//			D3DXVECTOR3 delta = mosPos - pos;
	//			if(atan2(delta.x, delta.z)>m_fScale) continue;

	//			int Atk = pCharacter->m_Status->chr.nAtk * m_pItemStatus->item.nAtk;



	//			pMonsterManager->GetMonsterManager()[i]->SetCurrentHP(0);
	//		}
	//	}
	//}
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
	ZeroMemory(m_pItemStatus, sizeof(STATUS));
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
