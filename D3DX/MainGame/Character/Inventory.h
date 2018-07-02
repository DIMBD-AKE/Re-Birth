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

union STATUS;

class Inventory
{
private:
	typedef vector<TestItem*> InvRow;

private:
	LPDIRECT3DTEXTURE9	m_pSlotTex;

	TestItem *		m_pHoldItem;

	// �κ��丮
	vector<InvRow>	m_vecInventory;
	D3DXVECTOR2		m_vInvPos;
	POINT			m_ptInvSize;
	POINT			m_ptSlotSize;
	float			m_fSlotSpacing;
	bool			m_isInvShow;

	// ���
	TestItem *		m_pEquip[EQUIP_END];
	D3DXVECTOR2		m_vEquipPos;
	bool			m_isEquipShow;


private:
	void InitPos();
	TestItem * PickItem();

public:
	Inventory();
	~Inventory();

	// �κ��丮 ����
	void CreateInventory(int col, int row);

	void OpenInventory() { m_isInvShow = !m_isInvShow; }
	void OpenEquip() { m_isEquipShow = !m_isEquipShow; }

	void Update();
	void Render();

	TestItem * GetFirstItem();
	STATUS GetEquipStat();
};

