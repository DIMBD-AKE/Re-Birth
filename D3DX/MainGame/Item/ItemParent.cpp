#include "../../stdafx.h"
#include "ItemParent.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Character/CharacterParant.h"

ItemParent::ItemParent()
{
}


ItemParent::~ItemParent()
{
}

void ItemParent::SetUp()
{
	/*m_pTexture = TEXTUREMANAGER->AddTexture("장검", "Texture/Item/장검.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("장검");*/
}

void ItemParent::Use(CharacterParant *& pCharacter)
{
}

void ItemParent::Attack(Model* pModel,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
	for (int i = 0; i < pMonsterManager->GetMonsterManager().size(); ++i)
	{
		D3DXVECTOR3 pos = *(pModel->GetPosition());
		D3DXVECTOR3 rot = *(pModel->GetRotation());
		if (!pMonsterManager->GetMonsterManager()[i]->GetIsResPawn())continue;
		else
		{
			float radius = *(pMonsterManager->GetMonsterManager()[i]->GetModel()->GetBoundSphere().radius);
			D3DXVECTOR3 mosPos = *(pMonsterManager->GetMonsterManager()[i]->GetModel()->GetPosition());
			float distance = D3DXVec3Length(&(mosPos - pos));
			if (distance - radius > m_fRange) continue;
			else
			{
				D3DXVECTOR3 delta = mosPos - pos;
				if(atan2(delta.x, delta.z)>m_fScale);
			}
		}
	}
}

void ItemParent::Skill1(Model* pModel,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
}

void ItemParent::Skill2(Model* pModel,ST_DAMAGE pStatus, MonsterManager* pMonsterManager)
{
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
