#pragma once

#include "../GameEnum.h"

class ItemParent;
union STATUS;
enum EQUIPTYPE;
class MonsterManager;
class CharacterParant;

struct ST_ITEMSTACK
{
	ItemParent * item;
	int count;
};

class Inventory
{
public:
	enum MOVETYPE
	{
		MOVETYPE_INVENTORY,
		MOVETYPE_EQUIP,
		MOVETYPE_END
	};

private:
	typedef vector<ST_ITEMSTACK> InvRow;

private:
	LPDIRECT3DTEXTURE9	m_pSlotTex;
	LPDIRECT3DTEXTURE9	m_pSlotOverTex;
	LPDIRECT3DTEXTURE9	m_pInvTex;
	LPDIRECT3DTEXTURE9	m_pEquipTex;

	float			m_fSlotResize;
	POINT			m_ptInvBGSize;
	POINT			m_ptEquipSize;

	// 캐릭터 정보
	CharacterParant*	m_pCharacter;

	// 창 이동
	POINT			m_ptPrevMouse;
	POINT			m_ptStartPos;
	MOVETYPE		m_eMoveType;

	// 홀드 아이템 정보
	ST_ITEMSTACK	m_pHoldItem;
	POINT			m_ptHIIndex;
	EQUIPTYPE 		m_eHIType;

	// 인벤토리
	vector<InvRow>	m_vecInventory;
	POINT			m_vInvPos;
	POINT			m_ptInvSize;
	float			m_fSlotSize;
	float			m_fSlotSpacing;
	bool			m_isInvShow;

	// 장비
	ST_ITEMSTACK	m_pEquip[EQUIP_END];
	POINT			m_ptEquipSlot[EQUIP_END + 1];
	POINT			m_vEquipPos;
	bool			m_isEquipShow;

private:
	void InitPos();
	void PickItem();
	void ChangeItem();
	void Move();
	void ShowInfo(ItemParent * pItem, D3DXVECTOR3 pos);

public:
	Inventory();
	~Inventory();

	// 인벤토리 생성
	void CreateInventory(int col, int row, CharacterParant * character);

	void OpenInventory() { m_isInvShow = !m_isInvShow; }
	void OpenEquip() { m_isEquipShow = !m_isEquipShow; }

	void Update();
	void Render();

	ItemParent * GetWeapon();
	ItemParent * GetPotion();


	bool GetSkill1(CharacterParant* pCharacter, MonsterManager* pMonster);
	bool GetSkill2(CharacterParant* pCharacter, MonsterManager* pMonster);
	STATUS GetEquipStat();
	bool AddItem(ItemParent* item);
};

