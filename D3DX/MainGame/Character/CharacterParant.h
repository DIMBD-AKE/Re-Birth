#pragma once

class TestItem;
class Map;
class Inventory;
class UIObject;
class MonsterManager;
class ItemParent;
union STATUS;
struct ST_DAMAGE;




//ĳ������ ���� Ŭ����

enum CHRTYPE   //ĳ���� Ÿ��
{
	CHRTYPE_GUN,
	CHRTYPE_SWORD,
	CHRTYPE_MAGIC
};

enum CHARSELECT
{
	CHAR_ONE,
	CHAR_TWO,
	CHAR_THREE
};

enum ANIMATIONTYPE
{
	ANI_IDLE,				//������
	ANI_RUN,				//�̵�(�޸���)
	ANI_SKILL,				//��ų����
	ANI_ATTACK,				//�Ϲݰ���
	ANI_DIE,				//����
	ANI_HIT,				//�ǰݻ���
	ANI_BATTLEREADY			//���õǾ�����.
};

enum CHAR_CONDITION			//ĳ���� �����
{
	CHAR_IDLE,				//ĳ���� ���
	CHAR_DASH_FRONT,		//ĳ���� �뽬 ��
	CHAR_DASH_BACK,			//ĳ���� �뽬 ��
	CHAR_RUN_FRONT,			//ĳ���� �޸���
	CHAR_RUN_BACK,			//ĳ���� �ڷ� �޸���
	CHAR_SKILL,				//ĳ���� ��ų����
	CHAR_ATTACK,			//ĳ���� �Ϲݰ���
	CHAR_DIE,				//ĳ���� ����
	CHAR_HIT,				//ĳ���� �ǰ�
	CHAR_BATTLEREADY,		//ĳ���� ���õ�
	CHAR_NONE				//�������� None����
};



class CharacterParant
{
protected:
	CHRTYPE					m_eChrType;			//ĳ���� Ÿ��
	SYNTHESIZE(CHARSELECT, m_eCharSelect, CharSelect);	 //�ش� Ŭ���� ĳ������ 1��° Ȥ�� 2��°
	GET(CHAR_CONDITION,	m_eCondition, Condition);		//ĳ���� ����

	TestItem*				m_pFirstItem;		//ù���� ��ų ���


	GET(Model*,m_pCharacter,Character);			//ĳ���� �ɹ� ���� 
	Map*					m_pSampleMap;		//������ �޴� �ɹ� ����
	GET(Inventory*,m_pInventory,m_Inventory);		//�κ��丮�� ����
	STATUS*					m_Status;			//�������ͽ� ���Ͽ� ���� 
	UIObject*				m_pUIobj;			//UI������Ʈ�� ����
	MonsterManager*			m_pMonsterManager;	//���� �Ŵ����� ����

	D3DXVECTOR3				m_vfront;			//�̵��� ���� ����Ʈ����

	int						m_nCalAction;		//�׼� ������ ���� ����
	bool					m_bIsFront;			//������ ������
	bool					m_bIsDash;			//�뽬�ߴ�
	bool					m_bIsDead;			//�׾���
	float					m_fStamina;			//���׹̳� ������
	

	void SKill();
	void Move();
	void Controller();
	void Debug();
	void CheckDirection();
	void ControllStamina();
	void UnderAttacked();
	
	void SetCurrentHP(int hp);
	void CalculDamage(float damage);
	void Attack();


	int						m_temp;			//�ִϸ��̼� Ȯ�ο� �ӽú���


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager);
	virtual void Update() = 0;
	virtual void Render();
	virtual void KeyControl(); 
	virtual void ChangeAnimation();
};