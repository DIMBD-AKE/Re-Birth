#pragma once

class TestItem
{
public:
	TestItem() {}
	~TestItem() {}
	string sName;
	string sDesc;
	int nId;
	float fPower;
	float fSpeed;
};

enum EQUIPTYPE
{
	EQUIP_FIRSTWEAPON,
	EQUIP_SECONDWEAPON,
	EQUIP_HELMET,
	EQUIP_CHEST,
	EQUIP_GLOVES,
	EQUIP_BOOTS,
	EQUIP_END
};

class Inventory
{
private:
	typedef vector<TestItem*> InvRow;

private:
	TestItem *		m_pHoldItem;

	// 인벤토리
	vector<InvRow>	m_vecInventory;
	D3DXVECTOR2		m_vInvPos;
	POINT			m_ptSlotSize;
	int				m_nSlotSpacing;

	// 장비
	TestItem *		m_pEquip[EQUIP_END];
	D3DXVECTOR2		m_vEquipPos;

private:
	void InitPos();

public:
	Inventory();
	~Inventory();

	void CreateInventory(int col, int row);

	void OpenInventory();
	void OpenEquip();
};

