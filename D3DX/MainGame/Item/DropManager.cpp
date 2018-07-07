#include "../../stdafx.h"
#include "DropManager.h"
#include "../Character/Inventory.h"
#include "../Character/CharacterParant.h"
#include "ItemManager.h"

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
	m_pModel->SetScale(D3DXVECTOR3(0.1, 0.1, 0.1));
}

void DropManager::AddDropItem(int itemID, D3DXVECTOR3 pos)
{
	ST_DROPBOX box;
	box.itemID = itemID;
	box.pos = pos;
	box.pos.y += 1;
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
				ItemParent item = ITEMMANAGER->GetItem(m_vecDrop[i].itemID);
				if (character->Getm_Inventory()->AddItem(item))
				{
					m_vecDrop.erase(m_vecDrop.begin() + i);
					return true;
				}
			}
	}

	return false;
}

void DropManager::Render()
{
	for (int i = 0; i < m_vecDrop.size(); i++)
	{
		m_vecDrop[i].rot += D3DXVECTOR3(1, 1, 1) * 0.01;
		m_pModel->SetRotation(m_vecDrop[i].rot);
		m_pModel->SetPosition(m_vecDrop[i].pos + 
			D3DXVECTOR3(0, sin(m_vecDrop[i].rot.x), 0) * 0.5);
		m_pModel->World();
		m_pModel->Render();
	}
}