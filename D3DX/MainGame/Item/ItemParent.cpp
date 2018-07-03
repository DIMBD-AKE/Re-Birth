#include "../../stdafx.h"
#include "ItemParent.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"


ItemParent::ItemParent()
{
}


ItemParent::~ItemParent()
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

void ItemParent::Render()
{
}
