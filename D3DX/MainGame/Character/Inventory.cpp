#include "../../stdafx.h"
#include "Inventory.h"
#include "CharacterParant.h"
#include "../Status.h"

void Inventory::InitPos()
{
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
			rc.left = m_fSlotSpacing + m_vInvPos.x + (m_ptSlotSize.x + m_fSlotSpacing) * j;
			rc.top = m_fSlotSpacing + m_vInvPos.y + (m_ptSlotSize.y + m_fSlotSpacing) * i;
			rc.right = rc.left + m_ptSlotSize.x;
			rc.bottom = rc.top + m_ptSlotSize.y;
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

	m_pSlotTex = TEXTUREMANAGER->AddTexture("UI Inventory Slot", "UI/Inventory Slot.png");
	D3DXIMAGE_INFO info = TEXTUREMANAGER->GetInfo("UI Inventory Slot");
	m_ptSlotSize.x = info.Width;
	m_ptSlotSize.y = info.Height;
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
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	if (m_isEquipShow)
	{
		
	}

	if (m_isInvShow)
	{
		for (int i = 0; i < m_ptInvSize.y; i++)
		{
			for (int j = 0; j < m_ptInvSize.x; j++)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
				pos.x = m_fSlotSpacing + m_vInvPos.x + (m_ptSlotSize.x + m_fSlotSpacing) * j;
				pos.y = m_fSlotSpacing + m_vInvPos.y + (m_ptSlotSize.y + m_fSlotSpacing) * i;
				SPRITE->Draw(m_pSlotTex, NULL, NULL, &pos, 0xFFFFFFFF);
			}
		}
	}
	SPRITE->End();
}

TestItem * Inventory::GetFirstItem()
{
	return nullptr;
}

STATUS Inventory::GetEquipStat()
{
	return STATUS();
}
