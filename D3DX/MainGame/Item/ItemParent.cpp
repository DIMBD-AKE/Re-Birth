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
	m_pTexture = TEXTUREMANAGER->AddTexture("장검", "Texture/Item/장검.jpg");
	m_imageInfo = TEXTUREMANAGER->GetInfo("장검");
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
			//pMonsterManager->GetMonsterManager()[i]->GetModel()->Getposition();
			
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
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	D3DXMATRIX	mat;

	float scaleX = size / (float)m_imageInfo.Width;
	float scaleY = size / (float)m_imageInfo.Height;

	D3DXMatrixScaling(&mat, scaleX, scaleY, 1);

	mat._41 = pos.x;
	mat._42 = pos.y;
	mat._43 = pos.z;

	SPRITE->SetTransform(&mat);

	SPRITE->Draw(m_pTexture, NULL, NULL, NULL, 0xffffffff);



	SPRITE->End();
}
