#include "../../stdafx.h"
#include "Inventory.h"
#include "CharacterParant.h"
#include "../Status.h"
#include "../Item/ItemParent.h"

void Inventory::InitPos()
{
	m_fSlotSize = 70;
	m_fSlotSpacing = 5;

	m_vInvPos.x = m_vInvPos.y = 0;
	m_vEquipPos.x = m_vEquipPos.y = 0;
}

void Inventory::PickItem()
{
	for (int i = 0; i < m_ptInvSize.y; i++)
	{
		for (int j = 0; j < m_ptInvSize.x; j++)
		{
			RECT rc;
			rc.left = m_fSlotSpacing + m_vInvPos.x + (m_fSlotSize + m_fSlotSpacing) * j;
			rc.top = m_fSlotSpacing + m_vInvPos.y + (m_fSlotSize + m_fSlotSpacing) * i;
			rc.right = rc.left + m_fSlotSize;
			rc.bottom = rc.top + m_fSlotSize;
			if (PtInRect(&rc, MOUSE_POS) && m_vecInventory[i][j])
			{
				m_ptHIIndex.x = j;
				m_ptHIIndex.y = i;
				m_eHIType = EQUIP_END;
				m_pHoldItem = m_vecInventory[i][j];
				m_vecInventory[i][j] = NULL;
			}
		}
	}
}

void Inventory::ChangeItem()
{
	if (!m_pHoldItem) return;

	bool find = false;
	for (int i = 0; i < m_ptInvSize.y; i++)
	{
		for (int j = 0; j < m_ptInvSize.x; j++)
		{
			RECT rc;
			rc.left = m_fSlotSpacing + m_vInvPos.x + (m_fSlotSize + m_fSlotSpacing) * j;
			rc.top = m_fSlotSpacing + m_vInvPos.y + (m_fSlotSize + m_fSlotSpacing) * i;
			rc.right = rc.left + m_fSlotSize;
			rc.bottom = rc.top + m_fSlotSize;
			if (PtInRect(&rc, MOUSE_POS) && m_pHoldItem)
			{
				find = true;
				if (m_vecInventory[i][j])
					m_vecInventory[m_ptHIIndex.x][m_ptHIIndex.y] = m_vecInventory[i][j];
				m_vecInventory[i][j] = m_pHoldItem;
				m_pHoldItem = NULL;
			}
		}
	}

	if (!find)
	{
		m_vecInventory[m_ptHIIndex.y][m_ptHIIndex.x] = m_pHoldItem;
		m_pHoldItem = NULL;
	}
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
	m_pInvTex = TEXTUREMANAGER->AddTexture("UI Inventory Background", "UI/Inventory Background.png");
}

void Inventory::Update()
{
	if (INPUT->KeyDown('I'))
	{
		if (!m_isInvShow)
		{
			ItemParent item;
			item.SetUp();
			AddItem(item);
		}
	}

	if (INPUT->KeyDown(VK_RBUTTON))
	{
		m_ptPrevMouse = MOUSE_POS;
		m_ptStartPos = m_vInvPos;
	}

	// 이동
	if (INPUT->KeyPress(VK_RBUTTON))
	{
		RECT rc;
		rc.left = m_vInvPos.x;
		rc.top = m_vInvPos.y;
		rc.right = rc.left + m_fSlotSpacing + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.x;
		rc.bottom = rc.top + m_fSlotSpacing + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.y;
		// 인벤토리 움직임
		if (PtInRect(&rc, MOUSE_POS) && m_isInvShow)
		{
			m_vInvPos.x = m_ptStartPos.x + MOUSE_POS.x - m_ptPrevMouse.x;
			m_vInvPos.y = m_ptStartPos.y + MOUSE_POS.y - m_ptPrevMouse.y;
		}
	}

	// 드래그
	if (INPUT->KeyDown(VK_LBUTTON))
		PickItem();

	if (INPUT->KeyUp(VK_LBUTTON))
		ChangeItem();
}

void Inventory::Render()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	if (m_isEquipShow)
	{
		
	}

	if (m_isInvShow)
	{
		D3DXMATRIX matS, matT;
		float rateX = (m_fSlotSpacing * 3 + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.x) / 
			(float)TEXTUREMANAGER->GetInfo("UI Inventory Background").Width;
		float rateY = (m_fSlotSpacing * 3 + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.y) /
			(float)TEXTUREMANAGER->GetInfo("UI Inventory Background").Height;

		D3DXMatrixScaling(&matS, rateX, rateY, 0);
		D3DXMatrixTranslation(&matT, m_vInvPos.x - m_fSlotSpacing, m_vInvPos.y - m_fSlotSpacing, 0.1);
		SPRITE->SetTransform(&(matS * matT));
		SPRITE->Draw(m_pInvTex, NULL, NULL, NULL, 0xFFFFFFFF);

		rateX = m_fSlotSize / (float)TEXTUREMANAGER->GetInfo("UI Inventory Slot").Width;
		rateY = m_fSlotSize / (float)TEXTUREMANAGER->GetInfo("UI Inventory Slot").Height;

		for (int i = 0; i < m_ptInvSize.y; i++)
		{
			for (int j = 0; j < m_ptInvSize.x; j++)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
				pos.x = m_fSlotSpacing + m_vInvPos.x + (m_fSlotSize + m_fSlotSpacing) * j;
				pos.y = m_fSlotSpacing + m_vInvPos.y + (m_fSlotSize + m_fSlotSpacing) * i;
				D3DXMatrixScaling(&matS, rateX, rateY, 0);
				D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);
				SPRITE->SetTransform(&(matS * matT));
				SPRITE->Draw(m_pSlotTex, NULL, NULL, NULL, 0xFFFFFFFF);
				if (m_vecInventory[i][j])
				{
					pos.x += m_fSlotSpacing;
					pos.y += m_fSlotSpacing;
					m_vecInventory[i][j]->Render(pos, m_fSlotSize - m_fSlotSpacing * 2);
				}
			}
		}
	}

	if (m_pHoldItem)
	{
		D3DXVECTOR3 pos;
		pos.x = MOUSE_POS.x - (m_fSlotSize - m_fSlotSpacing) / 2;
		pos.y = MOUSE_POS.y - (m_fSlotSize - m_fSlotSpacing) / 2;
		pos.z = 0;
		m_pHoldItem->Render(pos, m_fSlotSize - m_fSlotSpacing);
	}

	SPRITE->End();
}

ItemParent * Inventory::GetFirstItem()
{
	return nullptr;
}

STATUS Inventory::GetEquipStat()
{
	return STATUS();
}

bool Inventory::AddItem(ItemParent item)
{
	ItemParent * pItem = new ItemParent;
	*pItem = item;

	for (int i = 0; i < m_ptInvSize.y; i++)
	{
		for (int j = 0; j < m_ptInvSize.x; j++)
		{
			if (!m_vecInventory[i][j])
			{
				m_vecInventory[i][j] = pItem;
				return true;
			}
		}
	}

	SAFE_DELETE(pItem);
	return false;
}
