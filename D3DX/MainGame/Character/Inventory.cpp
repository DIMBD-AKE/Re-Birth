#include "../../stdafx.h"
#include "Inventory.h"
#include "CharacterParant.h"


void Inventory::InitPos()
{
	m_fSlotSize = 50;
	m_fSlotSpacing = 5;

	m_vInvPos = D3DXVECTOR2(0, 0);
	m_vEquipPos = D3DXVECTOR2(0, 0);
}

TestItem * Inventory::PickItem()
{
	for (int i = 0; i < m_ptInvSize.y; i++)
	{
		for (int j = 0; j < m_ptInvSize.x; j++)
		{
			RECT rc;
			rc.left = m_vInvPos.x + (m_fSlotSize + m_fSlotSize) * j;
			rc.top = m_vInvPos.y + (m_fSlotSize + m_fSlotSize) * i;
			rc.right = rc.left + m_fSlotSize;
			rc.bottom = rc.top + m_fSlotSize;
			if (PtInRect(&rc, MOUSE_POS))
			{
				return m_vecInventory[i][j];
			}
		}
	}

	return NULL;
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
	m_ptInvSize.x = row;
	m_ptInvSize.y = col;

	InvRow invRow(row);
	for (int i = 0; i < col; i++)
		m_vecInventory.push_back(invRow);

	for (int i = 0; i < EQUIP_END; i++)
		m_pEquip[i] = NULL;

	//m_pSlotTex = TEXTUREMANAGER->AddTexture("UI Inventory Slot", "UI/Inventory Slot.png");
}

void Inventory::Update()
{
	if (INPUT->KeyDown('I'))
		OpenInventory();
	if (INPUT->KeyDown(VK_LBUTTON))
	{

	}
}

void Inventory::Render()
{
	if (m_isEquipShow)
	{
		
	}

	if (m_isInvShow)
	{
		for (int i = 0; i < m_ptInvSize.y; i++)
		{
			for (int j = 0; j < m_ptInvSize.x; j++)
			{
				D3DXVECTOR3 pos;
				pos.x = m_vInvPos.x + (m_fSlotSize + m_fSlotSize) * j;
				pos.y = m_vInvPos.y + (m_fSlotSize + m_fSlotSize) * i;
				pos.z = 0;
				SPRITE->Draw(m_pSlotTex, NULL, NULL, &pos, 0xFFFFFFFF);
			}
		}
	}
}

TestItem * Inventory::GetFirstItem()
{
	return nullptr;
}

void Inventory::GetEquipStat()
{
	
}
