#include "../../stdafx.h"
#include "../Item/ItemParent.h"
#include "Inventory.h"
#include "CharacterParant.h"
#include "../Status.h"

void Inventory::InitPos()
{
	m_fSlotSize = 50;
	m_fSlotSpacing = 5;

	m_vInvPos.x = m_vInvPos.y = 0;
	m_vEquipPos.x = m_vEquipPos.y = 0;

	m_ptEquipSlot[EQUIP_FIRSTWEAPON] = Util::MakePoint(47, 438);
	m_ptEquipSlot[EQUIP_POTION] = Util::MakePoint(343, 438);
	m_ptEquipSlot[EQUIP_HELMET] = Util::MakePoint(195, 58);
	m_ptEquipSlot[EQUIP_CHEST] = Util::MakePoint(195, 218);
	m_ptEquipSlot[EQUIP_GLOVES] = Util::MakePoint(47, 282);
	m_ptEquipSlot[EQUIP_BOOTS] = Util::MakePoint(195, 378);
	// X 버튼
	m_ptEquipSlot[EQUIP_END] = Util::MakePoint(795, 16);
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

	for (int i = 0; i < EQUIP_END; i++)
	{
		RECT rc;
		rc.left = m_vEquipPos.x + m_ptEquipSlot[i].x * m_fSlotResize;
		rc.top = m_vEquipPos.y + m_ptEquipSlot[i].y * m_fSlotResize;
		rc.right = rc.left + m_fSlotSize;
		rc.bottom = rc.top + m_fSlotSize;
		if (PtInRect(&rc, MOUSE_POS) && m_pEquip[i])
		{
			m_eHIType = (EQUIPTYPE)i;
			m_pHoldItem = m_pEquip[i];
			m_pEquip[i] = NULL;
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
			if (PtInRect(&rc, MOUSE_POS))
			{
				find = true;
				// 중복체크 필요
				m_vecInventory[i][j] = m_pHoldItem;
				m_pHoldItem = NULL;
			}
		}
	}

	for (int i = 0; i < EQUIP_END; i++)
	{
		RECT rc;
		rc.left = m_vEquipPos.x + m_ptEquipSlot[i].x * m_fSlotResize;
		rc.top = m_vEquipPos.y + m_ptEquipSlot[i].y * m_fSlotResize;
		rc.right = rc.left + m_fSlotSize;
		rc.bottom = rc.top + m_fSlotSize;
		if (PtInRect(&rc, MOUSE_POS))
		{
			// 장착가능한 장비인지 체크 필요
			find = true;
			// 중복체크 필요
			m_pEquip[i] = m_pHoldItem;
			m_pHoldItem = NULL;
		}
	}

	if (!find)
	{
		if (m_eHIType == EQUIP_END)
			m_vecInventory[m_ptHIIndex.y][m_ptHIIndex.x] = m_pHoldItem;
		else
			m_pEquip[m_eHIType] = m_pHoldItem;
		m_pHoldItem = NULL;
	}
}

void Inventory::Move()
{
	// 위치 초기화
	if (INPUT->KeyDown(VK_RBUTTON))
	{
		RECT rc;
		rc.left = m_vInvPos.x; rc.top = m_vInvPos.y;
		rc.right = rc.left + m_ptInvBGSize.x; rc.bottom = rc.top + m_ptInvBGSize.y;
		// 인벤토리
		if (PtInRect(&rc, MOUSE_POS) && m_isInvShow)
		{
			m_ptStartPos = m_vInvPos;
			m_eMoveType = MOVETYPE_INVENTORY;
		}
		rc.left = m_vEquipPos.x; rc.top = m_vEquipPos.y;
		rc.right = rc.left + m_ptEquipSize.x; rc.bottom = rc.top + m_ptEquipSize.y;
		// 장착창
		if (PtInRect(&rc, MOUSE_POS) && m_isEquipShow)
		{
			m_ptStartPos = m_vEquipPos;
			m_eMoveType = MOVETYPE_EQUIP;
		}

		m_ptPrevMouse = MOUSE_POS;
	}

	// 이동
	if (INPUT->KeyPress(VK_RBUTTON))
	{
		RECT rc;
		rc.left = m_vInvPos.x;
		rc.top = m_vInvPos.y;
		rc.right = rc.left + m_ptInvBGSize.x;
		rc.bottom = rc.top + m_ptInvBGSize.y;
		// 인벤토리
		if (PtInRect(&rc, MOUSE_POS) && m_isInvShow && m_eMoveType == MOVETYPE_INVENTORY)
		{
			m_vInvPos.x = m_ptStartPos.x + MOUSE_POS.x - m_ptPrevMouse.x;
			m_vInvPos.y = m_ptStartPos.y + MOUSE_POS.y - m_ptPrevMouse.y;
		}
		rc.left = m_vEquipPos.x;
		rc.top = m_vEquipPos.y;
		rc.right = rc.left + m_ptEquipSize.x;
		rc.bottom = rc.top + m_ptEquipSize.y;
		// 장착창
		if (PtInRect(&rc, MOUSE_POS) && m_isEquipShow && m_eMoveType == MOVETYPE_EQUIP)
		{
			m_vEquipPos.x = m_ptStartPos.x + MOUSE_POS.x - m_ptPrevMouse.x;
			m_vEquipPos.y = m_ptStartPos.y + MOUSE_POS.y - m_ptPrevMouse.y;
		}
	}

	if (INPUT->KeyUp(VK_RBUTTON))
		m_eMoveType = MOVETYPE_END;
}

void Inventory::ShowInfo()
{
}

Inventory::Inventory()
	: m_pHoldItem(NULL)
	, m_isInvShow(false)
	, m_isEquipShow(false)
	, m_eMoveType(MOVETYPE_END)
{
}


Inventory::~Inventory()
{
	for (int i = 0; i < m_ptInvSize.y; i++)
		for (int j = 0; j < m_ptInvSize.x; j++)
			SAFE_DELETE(m_vecInventory[i][j]);

	for (int i = 0; i < EQUIP_END; i++)
		SAFE_DELETE(m_pEquip[i]);
}

void Inventory::CreateInventory(int col, int row)
{
	InitPos();

	m_ptInvSize.x = row;
	m_ptInvSize.y = col;

	InvRow invRow(row);
	for (int i = 0; i < col; i++)
		m_vecInventory.push_back(invRow);

	for (int i = 0; i < EQUIP_END; i++)
		m_pEquip[i] = NULL;

	m_pSlotTex = TEXTUREMANAGER->AddTexture("UI Inventory Slot", "UI/Inventory Slot.png");
	m_pSlotOverTex = TEXTUREMANAGER->AddTexture("UI Inventory Slot Over", "UI/Inventory Slot Over.png");
	m_pInvTex = TEXTUREMANAGER->AddTexture("UI Inventory Background", "UI/Inventory Background.png");
	m_pEquipTex = TEXTUREMANAGER->AddTexture("UI Inventory Equip", "UI/Inventory Equip.png");

	m_fSlotResize = m_fSlotSize / (float)TEXTUREMANAGER->GetInfo("UI Inventory Slot").Width;

	m_ptInvBGSize.x = m_fSlotSpacing + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.x;
	m_ptInvBGSize.y = m_fSlotSpacing + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.y;
	m_ptEquipSize.x = TEXTUREMANAGER->GetInfo("UI Inventory Equip").Width * m_fSlotResize;
	m_ptEquipSize.y = TEXTUREMANAGER->GetInfo("UI Inventory Equip").Height * m_fSlotResize;
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

	Move();

	// 장비창 닫기
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		RECT rc;
		rc.left = m_vEquipPos.x + m_ptEquipSlot[EQUIP_END].x * m_fSlotResize;
		rc.top = m_vEquipPos.y + m_ptEquipSlot[EQUIP_END].y * m_fSlotResize;
		rc.right = rc.left + 52 * m_fSlotResize;
		rc.bottom = rc.top + 52 * m_fSlotResize;
		if (PtInRect(&rc, MOUSE_POS))
			OpenEquip();
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

	D3DXMATRIX matS, matT;
	D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
	RECT rc;

	if (m_isEquipShow)
	{
		D3DXMatrixScaling(&matS, m_fSlotResize, m_fSlotResize, 0);
		D3DXMatrixTranslation(&matT, m_vEquipPos.x, m_vEquipPos.y, 0.1);
		SPRITE->SetTransform(&(matS * matT));
		SPRITE->Draw(m_pEquipTex, NULL, NULL, NULL, 0xFFFFFFFF);

		for (int i = 0; i < EQUIP_END; i++)
		{
			pos.x = m_vEquipPos.x + m_ptEquipSlot[i].x * m_fSlotResize;
			pos.y = m_vEquipPos.y + m_ptEquipSlot[i].y * m_fSlotResize;
			rc.left = pos.x;
			rc.top = pos.y;
			rc.right = rc.left + m_fSlotSize;
			rc.bottom = rc.top + m_fSlotSize;
			// 아이템
			if (m_pEquip[i])
			{
				pos.x += m_fSlotSpacing;
				pos.y += m_fSlotSpacing;
				m_pEquip[i]->item->Render(pos, m_fSlotSize - m_fSlotSpacing * 2);
			}
			// 테두리
			if (PtInRect(&rc, MOUSE_POS))
			{
				D3DXMatrixScaling(&matS, m_fSlotResize, m_fSlotResize, 0);
				D3DXMatrixTranslation(&matT, rc.left, rc.top, 0);
				SPRITE->SetTransform(&(matS * matT));
				SPRITE->Draw(m_pSlotOverTex, NULL, NULL, NULL, 0xFFFFFFFF);
			}
		}
	}

	if (m_isInvShow)
	{
		float resizeX, resizeY;
		resizeX = (m_fSlotSpacing * 3 + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.x) /
			(float)TEXTUREMANAGER->GetInfo("UI Inventory Background").Width;
		resizeY = (m_fSlotSpacing * 3 + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.y) /
			(float)TEXTUREMANAGER->GetInfo("UI Inventory Background").Height;

		// 배경
		D3DXMatrixScaling(&matS, resizeX, resizeY, 0);
		D3DXMatrixTranslation(&matT, m_vInvPos.x - m_fSlotSpacing, m_vInvPos.y - m_fSlotSpacing, 0.1);
		SPRITE->SetTransform(&(matS * matT));
		SPRITE->Draw(m_pInvTex, NULL, NULL, NULL, 0xFFFFFFFF);

		for (int i = 0; i < m_ptInvSize.y; i++)
		{
			for (int j = 0; j < m_ptInvSize.x; j++)
			{
				pos.x = m_fSlotSpacing + m_vInvPos.x + (m_fSlotSize + m_fSlotSpacing) * j;
				pos.y = m_fSlotSpacing + m_vInvPos.y + (m_fSlotSize + m_fSlotSpacing) * i;
				rc.left = pos.x;
				rc.top = pos.y;
				rc.right = rc.left + m_fSlotSize;
				rc.bottom = rc.top + m_fSlotSize;
				// 슬롯
				D3DXMatrixScaling(&matS, m_fSlotResize, m_fSlotResize, 0);
				D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);
				SPRITE->SetTransform(&(matS * matT));
				SPRITE->Draw(m_pSlotTex, NULL, NULL, NULL, 0xFFFFFFFF);
				// 아이템
				if (m_vecInventory[i][j])
				{
					pos.x += m_fSlotSpacing;
					pos.y += m_fSlotSpacing;
					m_vecInventory[i][j]->item->Render(pos, m_fSlotSize - m_fSlotSpacing * 2);
				}
				// 테두리
				if (PtInRect(&rc, MOUSE_POS))
				{
					D3DXMatrixScaling(&matS, m_fSlotResize, m_fSlotResize, 0);
					D3DXMatrixTranslation(&matT, rc.left, rc.top, 0);
					SPRITE->SetTransform(&(matS * matT));
					SPRITE->Draw(m_pSlotOverTex, NULL, NULL, NULL, 0xFFFFFFFF);
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
		m_pHoldItem->item->Render(pos, m_fSlotSize - m_fSlotSpacing);
	}

	SPRITE->End();
}

ItemParent * Inventory::GetWeapon()
{
	return nullptr;
}

ItemParent * Inventory::GetPotion()
{
	return NULL;
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
				m_vecInventory[i][j]->item = pItem;
				return true;
			}
		}
	}

	SAFE_DELETE(pItem);
	return false;
}
