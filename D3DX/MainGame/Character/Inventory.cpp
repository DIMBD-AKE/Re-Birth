#include "../../stdafx.h"
#include "../Item/ItemParent.h"
#include "../Item/HealthPotion.h"
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
	// X ¹öÆ°
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
			if (PtInRect(&rc, MOUSE_POS) && m_vecInventory[i][j].item)
			{
				m_ptHIIndex.x = j;
				m_ptHIIndex.y = i;
				m_eHIType = EQUIP_END;
				m_pHoldItem = m_vecInventory[i][j];
				m_vecInventory[i][j].item = NULL;
				m_vecInventory[i][j].count = 0;
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
		if (PtInRect(&rc, MOUSE_POS) && m_pEquip[i].item)
		{
			m_eHIType = (EQUIPTYPE)i;
			m_pHoldItem = m_pEquip[i];
			m_pEquip[i].item = NULL;
			m_pEquip[i].count = 0;
		}
	}
}

void Inventory::ChangeItem()
{
	if (!m_pHoldItem.item) return;

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
				// Áßº¹Ã¼Å© ÇÊ¿ä
				if (m_vecInventory[i][j].item)
				{
					// Æ÷¼Ç °ãÄ§
					if (m_vecInventory[i][j].item->GetEquipType() == EQUIP_POTION &&
						m_pHoldItem.item->GetEquipType() == EQUIP_POTION)
					{
						SAFE_DELETE(m_pHoldItem.item);
						m_vecInventory[i][j].count += m_pHoldItem.count;
						find = true;
					}
					// È¦µå°¡ ÀåºñÀÏ¶§
					if (m_eHIType != EQUIP_END && !find)
					{
						// °°ÀºÀåºñ¶ó¸é ±³È¯
						if (m_vecInventory[i][j].item->GetEquipType() == m_pHoldItem.item->GetEquipType())
						{
							m_pEquip[m_eHIType] = m_vecInventory[i][j];
							m_vecInventory[i][j] = m_pHoldItem;
						}
						else
							m_pEquip[m_eHIType] = m_pHoldItem;
						find = true;
					}
					if (!find)
					{
						m_vecInventory[m_ptHIIndex.y][m_ptHIIndex.x] = m_vecInventory[i][j];
						m_vecInventory[i][j] = m_pHoldItem;
						find = true;
					}
				}
				else
				{
					m_vecInventory[i][j] = m_pHoldItem;
					find = true;
				}
				m_pHoldItem.item = NULL;
				m_pHoldItem.count = 0;
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
			// ÀÎº¥Åä¸® ¾ÆÀÌÅÛ
			if (m_eHIType == EQUIP_END)
			{
				if (m_pHoldItem.item->GetEquipType() == i)
				{
					if (m_pEquip[i].item)
						m_vecInventory[m_ptHIIndex.y][m_ptHIIndex.x] = m_pEquip[i];
					m_pEquip[i] = m_pHoldItem;
					find = true;
				}
				else
				{
					m_vecInventory[m_ptHIIndex.y][m_ptHIIndex.x] = m_pHoldItem;
					find = true;
				}
			}
			else
			{
				m_pEquip[m_eHIType] = m_pHoldItem;
				find = true;
			}			
			m_pHoldItem.item = NULL;
			m_pHoldItem.count = 0;
		}
	}

	if (!find)
	{
		if (m_eHIType == EQUIP_END)
			m_vecInventory[m_ptHIIndex.y][m_ptHIIndex.x] = m_pHoldItem;
		else
			m_pEquip[m_eHIType] = m_pHoldItem;
		m_pHoldItem.item = NULL;
		m_pHoldItem.count = 0;
	}
}

void Inventory::Move()
{
	// À§Ä¡ ÃÊ±âÈ­
	if (INPUT->KeyDown(VK_RBUTTON))
	{
		RECT rc;
		rc.left = m_vInvPos.x; rc.top = m_vInvPos.y;
		rc.right = rc.left + m_ptInvBGSize.x; rc.bottom = rc.top + m_ptInvBGSize.y;
		// ÀÎº¥Åä¸®
		if (PtInRect(&rc, MOUSE_POS) && m_isInvShow)
		{
			m_ptStartPos = m_vInvPos;
			m_eMoveType = MOVETYPE_INVENTORY;
		}
		rc.left = m_vEquipPos.x; rc.top = m_vEquipPos.y;
		rc.right = rc.left + m_ptEquipSize.x; rc.bottom = rc.top + m_ptEquipSize.y;
		// ÀåÂøÃ¢
		if (PtInRect(&rc, MOUSE_POS) && m_isEquipShow)
		{
			m_ptStartPos = m_vEquipPos;
			m_eMoveType = MOVETYPE_EQUIP;
		}

		m_ptPrevMouse = MOUSE_POS;
	}

	// ÀÌµ¿
	if (INPUT->KeyPress(VK_RBUTTON))
	{
		RECT rc;
		rc.left = m_vInvPos.x;
		rc.top = m_vInvPos.y;
		rc.right = rc.left + m_ptInvBGSize.x;
		rc.bottom = rc.top + m_ptInvBGSize.y;
		// ÀÎº¥Åä¸®
		if (PtInRect(&rc, MOUSE_POS) && m_isInvShow && m_eMoveType == MOVETYPE_INVENTORY)
		{
			m_vInvPos.x = m_ptStartPos.x + MOUSE_POS.x - m_ptPrevMouse.x;
			m_vInvPos.y = m_ptStartPos.y + MOUSE_POS.y - m_ptPrevMouse.y;
		}
		rc.left = m_vEquipPos.x;
		rc.top = m_vEquipPos.y;
		rc.right = rc.left + m_ptEquipSize.x;
		rc.bottom = rc.top + m_ptEquipSize.y;
		// ÀåÂøÃ¢
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
	: m_isInvShow(false)
	, m_isEquipShow(false)
	, m_eMoveType(MOVETYPE_END)
{
}


Inventory::~Inventory()
{
	for (int i = 0; i < m_ptInvSize.y; i++)
		for (int j = 0; j < m_ptInvSize.x; j++)
			SAFE_DELETE(m_vecInventory[i][j].item);

	for (int i = 0; i < EQUIP_END; i++)
		SAFE_DELETE(m_pEquip[i].item);
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
		m_pEquip[i].item = NULL;

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
		if (m_isInvShow)
		{
			if (rand() % 2 == 0)
			{
				ItemParent item;
				item.SetUp();
				AddItem(item);
			}
			else
			{
				HealthPotion item;
				item.SetUp();
				AddItem(item);
			}
		}
	}

	Move();

	// ÀåºñÃ¢ ´Ý±â
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

	// µå·¡±×
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

		STATUS item = GetEquipStat();
		STATUS chr = *m_pChrStatus;
		chr.chr.nMaxHp += item.item.nHp;
		chr.chr.nAtk += item.item.nAtk;
		chr.chr.fAtkSpeed *= item.item.fAtkSpeed;
		chr.chr.nDef += item.item.nDef;
		chr.chr.fAgi += item.item.fAgi;
		chr.chr.fHit += item.item.fHit;
		chr.chr.fSpeed += item.item.fSpeed;

		for (int i = 0; i < EQUIP_END; i++)
		{
			pos.x = m_vEquipPos.x + m_ptEquipSlot[i].x * m_fSlotResize;
			pos.y = m_vEquipPos.y + m_ptEquipSlot[i].y * m_fSlotResize;
			rc.left = pos.x;
			rc.top = pos.y;
			rc.right = rc.left + m_fSlotSize;
			rc.bottom = rc.top + m_fSlotSize;
			// ¾ÆÀÌÅÛ
			if (m_pEquip[i].item)
			{
				pos.x += m_fSlotSpacing;
				pos.y += m_fSlotSpacing;
				m_pEquip[i].item->Render(pos, m_fSlotSize - m_fSlotSpacing * 2);
				if (m_pEquip[i].item)
					if (m_pEquip[i].item->GetEquipType() == EQUIP_POTION)
						TEXT->Add(to_string(m_pEquip[i].count),
							rc.right - 25 * m_fSlotResize,
							rc.bottom - 30 * m_fSlotResize,
							30 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			}
			// Å×µÎ¸®
			if (PtInRect(&rc, MOUSE_POS))
			{
				D3DXMatrixScaling(&matS, m_fSlotResize, m_fSlotResize, 0);
				D3DXMatrixTranslation(&matT, rc.left, rc.top, 0);
				SPRITE->SetTransform(&(matS * matT));
				SPRITE->Draw(m_pSlotOverTex, NULL, NULL, NULL, 0xFFFFFFFF);
			}
			// ½ºÅÝ
			char temp[64];
			TEXT->Add(to_string(chr.chr.nMaxHp), m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 135.5 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			TEXT->Add(to_string(chr.chr.nAtk), m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 215 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			sprintf_s(temp, 64, "%.2f", chr.chr.fAtkSpeed);
			TEXT->Add(temp, m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 268 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			TEXT->Add(to_string(chr.chr.nDef), m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 359 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			sprintf_s(temp, 64, "%.2f", chr.chr.fAgi);
			TEXT->Add(temp, m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 411 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			sprintf_s(temp, 64, "%.2f", chr.chr.fHit);
			TEXT->Add(temp, m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 463 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
			sprintf_s(temp, 64, "%.2f", chr.chr.fSpeed);
			TEXT->Add(temp, m_vEquipPos.x + 678 * m_fSlotResize,
				m_vEquipPos.y + 516 * m_fSlotResize, 36 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
		}
	}

	if (m_isInvShow)
	{
		float resizeX, resizeY;
		resizeX = (m_fSlotSpacing * 3 + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.x) /
			(float)TEXTUREMANAGER->GetInfo("UI Inventory Background").Width;
		resizeY = (m_fSlotSpacing * 3 + (m_fSlotSize + m_fSlotSpacing) * m_ptInvSize.y) /
			(float)TEXTUREMANAGER->GetInfo("UI Inventory Background").Height;

		// ¹è°æ
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
				// ½½·Ô
				D3DXMatrixScaling(&matS, m_fSlotResize, m_fSlotResize, 0);
				D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);
				SPRITE->SetTransform(&(matS * matT));
				SPRITE->Draw(m_pSlotTex, NULL, NULL, NULL, 0xFFFFFFFF);
				if (m_vecInventory[i][j].item)
					if (m_vecInventory[i][j].item->GetEquipType() == EQUIP_POTION)
						TEXT->Add(to_string(m_vecInventory[i][j].count),
							rc.right - 25 * m_fSlotResize,
							rc.bottom - 30 * m_fSlotResize, 
							30 * m_fSlotResize, "³ª´®½ºÄù¾î Regular", 0xFFFFFFFF);
				// ¾ÆÀÌÅÛ
				if (m_vecInventory[i][j].item)
				{
					pos.x += m_fSlotSpacing;
					pos.y += m_fSlotSpacing;
					m_vecInventory[i][j].item->Render(pos, m_fSlotSize - m_fSlotSpacing * 2);
				}
				// Å×µÎ¸®
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

	if (m_pHoldItem.item)
	{
		D3DXVECTOR3 pos;
		pos.x = MOUSE_POS.x - (m_fSlotSize - m_fSlotSpacing) / 2;
		pos.y = MOUSE_POS.y - (m_fSlotSize - m_fSlotSpacing) / 2;
		pos.z = 0;
		m_pHoldItem.item->Render(pos, m_fSlotSize - m_fSlotSpacing);
	}

	SPRITE->End();
}

ItemParent * Inventory::GetWeapon()
{
	return m_pEquip[EQUIP_FIRSTWEAPON].item;
}

ItemParent * Inventory::GetPotion()
{
	return m_pEquip[EQUIP_POTION].item;
}

STATUS Inventory::GetEquipStat()
{
	STATUS status;
	status.item.nAtk = 0;
	status.item.nDef = 0;
	status.item.nHp = 0;
	status.item.fAgi = 0;
	status.item.fHit = 0;
	status.item.fSpeed = 0;
	for (int i = 0; i < EQUIP_END; i++)
	{
		if (!m_pEquip[i].item) continue;
		if (!m_pEquip[i].item->GetItemStat()) continue;
		status.item.nAtk += m_pEquip[i].item->GetItemStat()->item.nAtk;
		status.item.nDef += m_pEquip[i].item->GetItemStat()->item.nDef;
		status.item.nHp += m_pEquip[i].item->GetItemStat()->item.nHp;
		status.item.fAgi += m_pEquip[i].item->GetItemStat()->item.fAgi;
		status.item.fHit += m_pEquip[i].item->GetItemStat()->item.fHit;
		status.item.fSpeed += m_pEquip[i].item->GetItemStat()->item.fSpeed;
	}
	return status;
}

bool Inventory::AddItem(ItemParent item)
{
	ItemParent * pItem = new ItemParent;;
	*pItem = item;

	// Áßº¹ °Ë»ç
	for (int i = 0; i < m_ptInvSize.y; i++)
	{
		for (int j = 0; j < m_ptInvSize.x; j++)
		{
			if (m_vecInventory[i][j].item)
			{
				if (m_vecInventory[i][j].item->GetID() == pItem->GetID() &&
					m_vecInventory[i][j].item->GetEquipType() == EQUIP_POTION)
				{
					m_vecInventory[i][j].count++;
					return true;
				}
			}
		}
	}

	// ºóÄ­ °Ë»ç
	for (int i = 0; i < m_ptInvSize.y; i++)
	{
		for (int j = 0; j < m_ptInvSize.x; j++)
		{
			if (!m_vecInventory[i][j].item)
			{
				m_vecInventory[i][j].item = pItem;
				m_vecInventory[i][j].count = 1;
				return true;
			}
		}
	}

	SAFE_DELETE(pItem);
	return false;
}
