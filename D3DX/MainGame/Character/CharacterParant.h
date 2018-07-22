#pragma once
#include "../GameEnum.h"

class TestItem;
class Map;
class Inventory;
class UIObject;
class MonsterManager;
class ItemParent;
class Character_Shield;
class DamageUI;
class DropManager;
union STATUS;
struct ST_DAMAGE;




//ĳ������ ���� Ŭ����

//struct ST_DAMAGETEXT			//������ �ؽ�Ʈ�� ����ü
//{
//	int Damage;
//	float time;
//	float endTime;
//	float angle;
//	float alpha;
//	float x;
//
//};


struct ST_PLAYERDAMAGED
{
	float startDamageTime;
	float endDamageTime;
};

class CharacterParant
{
protected:
	GET(CHRTYPE, m_eChrType, CharType);				//ĳ���� Ÿ��
	SYNTHESIZE(CHARSELECT, m_eCharSelect, CharSelect);	 //�ش� Ŭ���� ĳ������ 1��° Ȥ�� 2��°
	GET(CHAR_CONDITION, m_eCondition, Condition);		//ĳ���� ����
	GET(CHAR_SUBCONDITION, m_eSubCondition, SubCondition); //���� ĳ���� ����
	GET(DropManager*, m_pDropManager, dropManager);			//����Ŵ���
	CHAR_NUMTARGET			m_eNumTarget;				//ĳ���� Ÿ�ټ� 

	TestItem*				m_pFirstItem;			//ù���� ��ų ���

	GET(Model*, m_pCharacter, Character);				//ĳ���� �ɹ� ���� 
	
	Map*					m_pSampleMap;			//������ �޴� �ɹ� ����
	GET(Inventory*, m_pInventory, m_Inventory);		//�κ��丮�� ����
	GET(STATUS*, m_Status, status);					//�������ͽ� ���Ͽ� ���� 
	UIObject*				m_pUIobj;				//UI������Ʈ�� ����
	
	UIObject*				m_pHPBar;				//hp���α׷�����
	UIObject*				m_pStaminaBar;			//���׹̳� ���α׷�����
	UIObject*				m_pShieldHp;			//����� HP
	UIObject*				m_pChrStat;				//ĳ���� �������ͽ� 
	UIObject*				m_pInheritateIco;		//ĳ���� ������ųUI
	UIObject*				m_pInheritateIco2;		//ĳ���� ������ų ������
	UIObject*				m_pInheritateIco3;		//ĳ���� ������ų ������
	UIObject*				m_pSkillBar;			//ĳ���� ��ų��
	UIObject*				m_pMagicShield;			//�����ǵ�
	UIObject*				m_pAimLine;				//���ؼ� 


	MonsterManager*			m_pMonsterManager;		//���� �Ŵ����� ����
	Character_Shield*		m_pShieldChr;			//����ĳ���Ϳ� ���� 

	D3DXVECTOR3				m_vfront;				//�̵��� ���� ����Ʈ����
	D3DXVECTOR3				m_vPotalfront;			//��Ż �̵��� ���� ����Ʈ ����
	D3DXVECTOR3				m_vMeteo;				//���׿� ���� 
	D3DXVECTOR3				m_vGun;					//�Ѻ���

	int						m_nCalAction;			//�׼� ������ ���� ����
	int						m_nDamage;				//������ ����� ���� 
	int						m_nAppear;				//����ĳ���� ������ 
	int						m_nIndex;				//���� ���Ϳ� �ε���
	int						m_nDamageCount;			//������ ī��Ʈ 
	
	DamageUI*				m_pDamage;				//������ Ŭ���� ������
	
	bool					m_bIsFront;				//������ ������
	bool					m_bIsDash;				//�뽬�ߴ�
	bool					m_bIsAttack;			//�Ϲݰ��� �ߴ�?
	bool					m_bIsUnderAttacked;		//���ݹ޾Ҵ�?
	bool					m_bIsSkill;				//��ų���?
	bool					m_bIsInvincible;			//�����̴�
	bool					m_bIsPotal;				//���� ��Ż ������?
	bool					m_bIsSubChr;			//����ĳ���� ���Դ�?
	bool					m_bIsWalk;				//�Ȱ� �ִ�
	bool					m_isCutScene;			//�ƾ��̴�?
	bool					m_bisMgShield;			//���� �ǵ� ������?
	bool					m_bIsMeteo;				//���׿� ��
	bool					m_bIsMeteoClick;		//���׿� �� �ϱ��� Ŭ��
	bool					m_bIsGunView;			//�ѽ��ȭ�� ��ȯ�Ұ�
	float					m_fDamageCount;			//������ ���� ī��Ʈ
	float					m_fDamageAngle;			//������ �ޱ�
	float					m_fElpTime;				//����Ʈ�� �Ϸ��� ī��Ʈ
	float					m_fPrevTime;			//����Ʈ ���ؽð�
	float					m_fEffectInterval;		//����Ʈ ���͹�
	float					m_fModelAlpha;			//�� ���İ�
	float					m_fDot;					//���ݽ� ��������

	GET(bool, m_bIsDead, IsDead);						//�׾���
	float					m_fStamina;				//���׹̳� ������

	vector<EffectObject*>	m_vecEffect;			//����Ʈ ������Ʈ��
	vector<D3DXVECTOR3*>	m_vecVertex;			//����׿� ����
	vector<int>				m_vecTarget;			//���ʹ� Ÿ������ ����
	ST_PLAYERDAMAGED		m_stDamaged;			//��ųŸ�ӿ� ����ü ����

	Particle*		m_pParticle;
	Particle*		m_pParticle2;
	Particle*		m_pParticle3;
	Particle*		m_pParticle4;

	void SKill();
	void Move();
	void AppearDamage();
	void Controller();
	void Debug();
	void CheckDirection();
	void ControllStamina();

	void shield();


	void SetCurrentHP(int hp);
	void CalculDamage(float damage);
	void CountAppearDamage();
	void SkillIconAlpha();
	void PlayerProgressBar();
	void Effect();
	void StoreEffect(int index);
	void StoreAttack(int index);
	void Reset(Map* map, MonsterManager* pMonsterManager,DropManager* Drop);
	void SetTarget();
	void CutScene();
	void SetModelAlpha();

	int						m_temp;			//�ִϸ��̼� Ȯ�ο� �ӽú���


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void ChangeAnimation();
};