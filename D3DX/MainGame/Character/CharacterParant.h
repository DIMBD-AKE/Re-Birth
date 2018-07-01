#pragma once

class TestItem;
class Map;
class Inventory;

//ĳ������ ���� Ŭ����

enum CHRTYPE   //ĳ���� Ÿ��
{
	CHRTYPE_GUN,
	CHRTYPE_SWORD,
	CHRTYPE_MAGIC
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
	CHAR_RUN,				//ĳ���� �޸���
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
	//ST_CHR_STAT				m_stDefaltStat;		//������� [��]�� ����
	//ST_CHR_STAT				m_stFinalStat;		//������� [��]�� ����

	TestItem*				m_pFirstItem;		//ù���� ��ų ���


	Model*					m_pCharacter;		//ĳ���� �ɹ� ���� 
	Map*					m_pSampleMap;		//������ �޴� �ɹ� ����
	Inventory *				m_pInventory;		//�κ��丮�� ����

	D3DXVECTOR3				m_vfront;			//�̵��� ���� ����Ʈ����


	bool					m_bIsPressW;		//WŰ�� ������ �ִ��� �Ұ�

	void SKill();
	void Move();
	

	int						m_temp;			//�ִϸ��̼� Ȯ�ο� �ӽú���


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(Map* map);
	virtual void Update() = 0;
	virtual void Render();
	virtual void ChangeAnimation();
};