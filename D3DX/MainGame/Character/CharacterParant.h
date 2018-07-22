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




//캐릭터의 원형 클래스

//struct ST_DAMAGETEXT			//데미지 텍스트용 구조체
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
	GET(CHRTYPE, m_eChrType, CharType);				//캐릭터 타입
	SYNTHESIZE(CHARSELECT, m_eCharSelect, CharSelect);	 //해당 클래스 캐릭터의 1번째 혹은 2번째
	GET(CHAR_CONDITION, m_eCondition, Condition);		//캐릭터 상태
	GET(CHAR_SUBCONDITION, m_eSubCondition, SubCondition); //서브 캐릭터 상태
	GET(DropManager*, m_pDropManager, dropManager);			//드랍매니저
	CHAR_NUMTARGET			m_eNumTarget;				//캐릭터 타겟수 

	TestItem*				m_pFirstItem;			//첫번쨰 스킬 장비

	GET(Model*, m_pCharacter, Character);				//캐릭터 맴버 변수 
	
	Map*					m_pSampleMap;			//맵정보 받는 맴버 변수
	GET(Inventory*, m_pInventory, m_Inventory);		//인벤토리용 변수
	GET(STATUS*, m_Status, status);					//스테이터스 유니온 변수 
	UIObject*				m_pUIobj;				//UI오브젝트용 변수
	
	UIObject*				m_pHPBar;				//hp프로그래스바
	UIObject*				m_pStaminaBar;			//스테미너 프로그래스바
	UIObject*				m_pShieldHp;			//쉴드용 HP
	UIObject*				m_pChrStat;				//캐릭터 스테이터스 
	UIObject*				m_pInheritateIco;		//캐릭터 고유스킬UI
	UIObject*				m_pInheritateIco2;		//캐릭터 고유스킬 아이콘
	UIObject*				m_pInheritateIco3;		//캐릭터 고유스킬 아이콘
	UIObject*				m_pSkillBar;			//캐릭터 스킬바
	UIObject*				m_pMagicShield;			//마법실드
	UIObject*				m_pAimLine;				//조준선 


	MonsterManager*			m_pMonsterManager;		//몬스터 매니저용 변수
	Character_Shield*		m_pShieldChr;			//쉴드캐릭터용 변수 

	D3DXVECTOR3				m_vfront;				//이동을 위한 프론트벡터
	D3DXVECTOR3				m_vPotalfront;			//포탈 이동을 위한 프론트 벡터
	D3DXVECTOR3				m_vMeteo;				//메테오 벡터 
	D3DXVECTOR3				m_vGun;					//총벡터

	int						m_nCalAction;			//액션 프레임 계산용 변수
	int						m_nDamage;				//데미지 띄우기용 변수 
	int						m_nAppear;				//서브캐릭터 나오나 
	int						m_nIndex;				//몬스터 벡터용 인덱스
	int						m_nDamageCount;			//데미지 카운트 
	
	DamageUI*				m_pDamage;				//데미지 클래스 포인터
	
	bool					m_bIsFront;				//앞인지 뒤인지
	bool					m_bIsDash;				//대쉬했늬
	bool					m_bIsAttack;			//일반공격 했늬?
	bool					m_bIsUnderAttacked;		//공격받았니?
	bool					m_bIsSkill;				//스킬썼니?
	bool					m_bIsInvincible;			//무적이니
	bool					m_bIsPotal;				//지금 포탈 눌렀니?
	bool					m_bIsSubChr;			//서브캐릭터 나왔늬?
	bool					m_bIsWalk;				//걷고 있니
	bool					m_isCutScene;			//컷씬이니?
	bool					m_bisMgShield;			//매직 실드 켜졌니?
	bool					m_bIsMeteo;				//메테오 쾅
	bool					m_bIsMeteoClick;		//메테오 쾅 하기전 클릭
	bool					m_bIsGunView;			//총쏘기화면 전환불값
	float					m_fDamageCount;			//데미지 띄우는 카운트
	float					m_fDamageAngle;			//데미지 앵글
	float					m_fElpTime;				//이펙트용 일랩스 카운트
	float					m_fPrevTime;			//이펙트 기준시간
	float					m_fEffectInterval;		//이펙트 인터벌
	float					m_fModelAlpha;			//모델 알파값
	float					m_fDot;					//공격시 각도계산용

	GET(bool, m_bIsDead, IsDead);						//죽었늬
	float					m_fStamina;				//스테미나 게이지

	vector<EffectObject*>	m_vecEffect;			//이펙트 오브젝트용
	vector<D3DXVECTOR3*>	m_vecVertex;			//디버그용 벡터
	vector<int>				m_vecTarget;			//에너미 타겟저장 벡터
	ST_PLAYERDAMAGED		m_stDamaged;			//스킬타임용 구조체 변수

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

	int						m_temp;			//애니메이션 확인용 임시변수


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(CHRTYPE type, CHARSELECT order);
	virtual void Update();
	virtual void Render();
	virtual void KeyControl();
	virtual void ChangeAnimation();
};