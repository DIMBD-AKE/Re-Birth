#pragma once
#include "../GameEnum.h"

class TestItem;
class Map;
class Inventory;
class UIObject;
class MonsterManager;
class ItemParent;
class Character_Shield;
class Npc;
class DamageUI;
class DropManager;
union STATUS;
struct ST_DAMAGE;
class Pet;



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


struct ST_STATUS
{
	float ElpTime;				//�Ϸ��� 
	float ApplyTime;			//���ӽð�
	float DamageDelay;			//������ �����̽ð�
};


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

	TestItem*				m_pFirstItem;				//ù���� ��ų ���
	Npc*					m_pNpc;						//NPCŬ���� ����
	Pet*					m_pPet;						//��Ŭ���� ����

	ST_STATUS				m_bCharStatus[STAT_END];				//ĳ���� �����̻� ���� 
	
	
	
	
	GET(Model*, m_pCharacter, Character);				//ĳ���� �ɹ� ���� 
	
	GET(Map*,m_pSampleMap, SampleMap);					//������ �޴� �ɹ� ����
	GET(Inventory*, m_pInventory, m_Inventory);				//�κ��丮�� ����
	GET(STATUS*, m_Status, status);							//�������ͽ� ���Ͽ� ���� 
	UIObject*				m_pUIobj;						//UI������Ʈ�� ����
	
	UIObject*				m_pHPBar;						//hp���α׷�����
	UIObject*				m_pStaminaBar;					//���׹̳� ���α׷�����
	UIObject*				m_pShieldHp;					//����� HP
	UIObject*				m_pChrStat;						//ĳ���� �������ͽ� 
	UIObject*				m_pInheritateIco;				//ĳ���� ������ųUI
	UIObject*				m_pInheritateIco2;				//ĳ���� ������ų ������
	UIObject*				m_pInheritateIco3;				//ĳ���� ������ų ������
	UIObject*				m_pSkillBar;					//ĳ���� ��ų��
	UIObject*				m_pMagicShield;					//�����ǵ�
	UIObject*				m_pAimLine;						//���ؼ� 
	UIObject*				m_pTalkBar;						//��ȭâ
	UIObject*				m_SkillToolTip;					//��ų ����â

	MonsterManager*			m_pMonsterManager;				//���� �Ŵ����� ����
	Character_Shield*		m_pShieldChr;					//����ĳ���Ϳ� ���� 

	D3DXVECTOR3				m_vfront;						//�̵��� ���� ����Ʈ����
	D3DXVECTOR3				m_vPotalfront;					//��Ż �̵��� ���� ����Ʈ ����
	D3DXVECTOR3				m_vMeteo;						//���׿� ���� 
	D3DXVECTOR3				m_vGun;							//�Ѻ���
	D3DXVECTOR3				m_vMegaCri;						//�ް�ũ����ŻŬ����ǥ


	int						m_nCalAction;					//�׼� ������ ���� ����
	int						m_nDamage;						//������ ����� ���� 
	int						m_nAppear;						//����ĳ���� ������ 
	int						m_nIndex;						//���� ���Ϳ� �ε���
	int						m_nDamageCount;					//������ ī��Ʈ 
	int*					m_npStage;						//�������� ī��Ʈ


	DamageUI*				m_pDamage;						//������ Ŭ���� ������
	
	bool					m_bIsFront;						//������ ������
	bool					m_bIsDash;						//�뽬�ߴ�
	bool					m_bIsAttack;					//�Ϲݰ��� �ߴ�?
	bool					m_bIsUnderAttacked;				//���ݹ޾Ҵ�?
	bool					m_bIsSkill;						//��ų���?
	bool					m_bIsInvincible;					//�����̴�
	bool					m_bIsPotal;						//���� ��Ż ������?
	bool					m_bIsSubChr;					//����ĳ���� ���Դ�?
	bool					m_bIsWalk;						//�Ȱ� �ִ�
	bool					m_isCutScene;					//�ƾ��̴�?
	bool					m_bisMgShield;					//���� �ǵ� ������?
	bool					m_bIsMeteo;						//���׿� ��
	bool					m_bIsMeteoClick;				//���׿� �� �ϱ��� Ŭ��
	bool					m_bIsGunView;					//�ѽ��ȭ�� ��ȯ�Ұ�
	bool					m_bIsMegaCristal;						//�ް�ũ����Ż �ߴ�
	bool					m_bIsMegaCirstalClick;					//�ް�ũ����Ż Ŭ���ߴ�
	bool					m_bIceStat;						//���̽� ���� �Ұ�
	bool					m_bIsStun;						//���ϻ��� �Ұ�
	SET(bool, m_bSkillUnSealed, SkillUnSealed);					//��ų �رݿ� �Ұ�

	float					m_fDamageCount;					//������ ���� ī��Ʈ
	float					m_fDamageAngle;					//������ �ޱ�
	float					m_fElpTime;						//����Ʈ�� �Ϸ��� ī��Ʈ
	float					m_fPrevTime;					//����Ʈ ���ؽð�
	float					m_fEffectInterval;				//����Ʈ ���͹�
	float					m_fModelAlpha;					//�� ���İ�
	float					m_fDot;							//���ݽ� ��������
	float					m_fFireCount;					//�����̻� �� ������
	float					m_fGuard;						//����� �Ϸ���Ÿ��

	GET(bool, m_bIsDead, IsDead);								//�׾���
	
	float					m_fStamina;						//���׹̳� ������

	vector<EffectObject*>	m_vecEffect;					//����Ʈ ������Ʈ��
	vector<D3DXVECTOR3*>	m_vecVertex;					//����׿� ����
	vector<int>				m_vecTarget;					//���ʹ� Ÿ������ ����
	ST_PLAYERDAMAGED		m_stDamaged;					//��ųŸ�ӿ� ����ü ����

	Particle*		m_pParticle;
	Particle*		m_pParticle2;
	Particle*		m_pParticle3;
	Particle*		m_pParticle4;
	Particle*		m_pParticle5;

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
	void Reset(Map* map, MonsterManager* pMonsterManager,DropManager* Drop, Pet* p);
	void SetTarget();
	void CutScene();
	void SetModelAlpha();
	void SetPlayerStatus();
	void SkillToolTip(D3DXVECTOR3 pos);
	void SetCameraNormalView();
	void Getstage(int* stage) { m_npStage = stage; }
	void Guard();
	void Restore();
	void SummonPet();
	int						m_temp;			//�ִϸ��̼� Ȯ�ο� �ӽú���


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void ChangeAnimation();

	


	void SetNpcMemoryAddressLink(Npc* npc) { m_pNpc = npc; }
	void setPlayerStatus(CHAR_STATUS status, float applytime, float damageDelay) { m_bCharStatus[status].ApplyTime = applytime; 
	m_bCharStatus->ElpTime = 0; m_bCharStatus->DamageDelay = damageDelay; }


	bool getPlayerStatus(CHAR_STATUS status) { return m_bCharStatus[status].ElpTime >=  m_bCharStatus[status].ApplyTime; }

};