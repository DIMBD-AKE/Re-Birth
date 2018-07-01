#pragma once

class TestItem;
class Map;

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
	ANI_HIT					//�ǰݻ���
};

struct ST_CHR_STAT  //�⺻ ĳ���� ����
{
	float MoveSpeed;		//�̵��ӵ�
	float STR;				//���� ���ݷ�
	float INT;				//���� ���ݷ�
	float DEX;				//���Ÿ� ���ݷ�
	float AGI;				//ȸ�Ƿ� 
	float DEF;				//����
	float HP;				//ü��
};




class CharacterParant
{
protected:
	CHRTYPE					m_eChrType;			//ĳ���� Ÿ��
	ST_CHR_STAT				m_stDefaltStat;		//������� [��]�� ����
	ST_CHR_STAT				m_stFinalStat;		//������� [��]�� ����

	TestItem*				m_pFirstItem;		//ù���� ��ų ���


	Model*					m_pCharacter;		//ĳ���� �ɹ� ���� 
	Map*					m_pSampleMap;		//������ �޴� �ɹ� ����

	D3DXVECTOR3				m_vfront;			//�̵��� ���� ����Ʈ����


	void SKill();
	void Move();
	

public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init();
	virtual void Update() = 0;
	virtual void Render();
	void SetMap(Map* map);
};