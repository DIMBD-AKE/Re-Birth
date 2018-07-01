#include "../../stdafx.h"
#include "Inventory.h"
#include "CharacterParant.h"


void Inventory::InitPos()
{
	POINT size;
	size.x = size.y = 50;
	m_ptSlotSize = size;
	m_nSlotSpacing = 5;

	m_vInvPos = D3DXVECTOR2(0, 0);
	m_vEquipPos = D3DXVECTOR2(0, 0);
}

Inventory::Inventory()
	: m_pHoldItem(NULL)
{
	InitPos();
}


Inventory::~Inventory()
{
}

void Inventory::CreateInventory(int col, int row)
{
	for (int i = 0; i < col; i++)
	{
		m_vecInventory.push_back(InvRow());
		for (int j = 0; j < row; j++)
			m_vecInventory[i].push_back(NULL);
	}

	for (int i = 0; i < EQUIP_END; i++)
		m_pEquip[i] = NULL;
}

void Inventory::Update()
{
	
}

void Inventory::Render()
{
}

TestItem * Inventory::GetFirstItem()
{
	return nullptr;
}

ST_CHR_STAT Inventory::GetEquipStat()
{
	return ST_CHR_STAT();
}
