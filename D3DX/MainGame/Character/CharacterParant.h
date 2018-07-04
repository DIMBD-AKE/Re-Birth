#pragma once

class TestItem;
class Map;
class Inventory;
union STATUS;

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
	CHAR_BATTLEREADY		//ĳ���� ���õ�
};



class CharacterParant
{
protected:
	CHRTYPE					m_eChrType;			//ĳ���� Ÿ��
	SYNTHESIZE(CHARSELECT, m_eCharSelect, CharSelect);	 //�ش� Ŭ���� ĳ������ 1��° Ȥ�� 2��°
	CHAR_CONDITION			m_eCondition;		//ĳ���� ����

	TestItem*				m_pFirstItem;		//ù���� ��ų ���
	

	Model*					m_pCharacter;		//ĳ���� �ɹ� ���� 
	Map*					m_pSampleMap;		//������ �޴� �ɹ� ����
	Inventory *				m_pInventory;		//�κ��丮�� ����
	STATUS*					m_Status;			//�������ͽ� ���Ͽ� ���� 


	D3DXVECTOR3				m_vfront;			//�̵��� ���� ����Ʈ����

	int						m_nCalAction;		//�׼� ������ ���� ����
	bool					m_bIsFront;			//������ ������
	bool					m_bIsDash;			//�뽬�ߴ�
	float					m_fStamina;			//���׹̳� ������

	void SKill();
	void Move();
	void Controller();
	void Debug();
	void CheckDirection();
	void ControllStamina();

	int						m_temp;			//�ִϸ��̼� Ȯ�ο� �ӽú���


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(Map* map, CHARSELECT order);
	virtual void Update() = 0;
	virtual void Render();
	virtual void KeyControl(); 
	virtual void ChangeAnimation();
};