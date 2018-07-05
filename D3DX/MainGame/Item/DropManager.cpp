#include "../../stdafx.h"
#include "DropManager.h"
#include "../Character/Inventory.h"
#include "../Character/CharacterParant.h"

DropManager::DropManager()
	: m_pModel(NULL)
{
}


DropManager::~DropManager()
{
}

void DropManager::Init()
{
	MODELMANAGER->AddModel("DropBox", "Model/Etc/", "DropBox.obj", MODELTYPE_OBJ);
	m_pModel = MODELMANAGER->GetModel("DropBox", MODELTYPE_OBJ);
	m_pModel->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
}

void DropManager::AddDropItem(int itemID, D3DXVECTOR3 pos)
{
	ST_DROPBOX box;
	box.itemID = itemID;
	box.pos = pos;
	box.rot.x = D3DXToRadian(rand() % 360);
	box.rot.y = D3DXToRadian(rand() % 360);
	box.rot.z = D3DXToRadian(rand() % 360);
	m_vecDrop.push_back(box);
}

bool DropManager::GetDropItem(CharacterParant * character)
{
	for (int i = 0; i < m_vecDrop.size(); i++)
	{
		m_pModel->SetPosition(m_vecDrop[i].pos);
		m_pModel->SetRotation(m_vecDrop[i].rot);
		if (character->GetCharacter()->IsCollisionSphere(m_pModel))
			if (character->GetCharacter()->IsCollisionOBB(m_pModel))
			{
				// 인벤토리 검사
				return true;
			}
	}

	return false;
}

void DropManager::Render()
{
	for (int i = 0; i < m_vecDrop.size(); i++)
	{
		m_pModel->SetPosition(m_vecDrop[i].pos);
		m_pModel->SetRotation(m_vecDrop[i].rot);
		m_pModel->World();
		m_pModel->Render();
	}
}