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
	float fDelay;

	void Attack() {}
	void Skill1() {}
	void Skill2() {}
	void Render() {}
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

struct ST_CHR_STAT;

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
	bool			m_isInvShow;

	// 장비
	TestItem *		m_pEquip[EQUIP_END];
	D3DXVECTOR2		m_vEquipPos;
	bool			m_isEquipShow;


private:
	void InitPos();

public:
	Inventory();
	~Inventory();

	// 인벤토리 생성
	void CreateInventory(int col, int row);

	void OpenInventory() { m_isInvShow = !m_isInvShow; }
	void OpenEquip() { m_isEquipShow = !m_isEquipShow; }

	void Update();
	void Render();

	TestItem * GetFirstItem();
	ST_CHR_STAT GetEquipStat();
};

