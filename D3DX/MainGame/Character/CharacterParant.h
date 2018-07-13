#pragma once

class TestItem;
class Map;
class Inventory;
class UIObject;
class MonsterManager;
class ItemParent;
union STATUS;
struct ST_DAMAGE;




//캐릭터의 원형 클래스

enum CHRTYPE   //캐릭터 타입
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
	ANI_IDLE,				//대기상태
	ANI_RUN,				//이동(달리기)
	ANI_SKILL,				//스킬공격
	ANI_ATTACK,				//일반공격
	ANI_DIE,				//죽음
	ANI_HIT,				//피격상태
	ANI_BATTLEREADY			//선택되었을때.
};

enum CHAR_CONDITION			//캐릭터 컨디션
{
	CHAR_IDLE,				//캐릭터 대기
	CHAR_DASH_FRONT,		//캐릭터 대쉬 앞
	CHAR_DASH_BACK,			//캐릭터 대쉬 뒤
	CHAR_RUN_FRONT,			//캐릭터 달리기
	CHAR_RUN_BACK,			//캐릭터 뒤로 달리기
	CHAR_SKILL,				//캐릭터 스킬쓰기
	CHAR_ATTACK,			//캐릭터 일반공격
	CHAR_DIE,				//캐릭터 죽음
	CHAR_HIT,				//캐릭터 피격
	CHAR_BATTLEREADY,		//캐릭터 선택됨
	CHAR_NONE				//죽은뒤의 None상태
};

struct ST_DAMAGETEXT			//데미지 텍스트용 구조체
{
	int Damage;
	float time;
	float endTime;
	float angle;
	float alpha;
	float x;

};


struct ST_PLAYERDAMAGED
{
	float startDamageTime;
	float endDamageTime;
};

class CharacterParant
{
protected:
	CHRTYPE					m_eChrType;				//캐릭터 타입
	SYNTHESIZE(CHARSELECT, m_eCharSelect, CharSelect);	 //해당 클래스 캐릭터의 1번째 혹은 2번째
	GET(CHAR_CONDITION,	m_eCondition, Condition);		//캐릭터 상태

	TestItem*				m_pFirstItem;			//첫번쨰 스킬 장비


	GET(Model*,m_pCharacter,Character);				//캐릭터 맴버 변수 
	Map*					m_pSampleMap;			//맵정보 받는 맴버 변수
	GET(Inventory*,m_pInventory,m_Inventory);		//인벤토리용 변수
	GET(STATUS*,m_Status, status);					//스테이터스 유니온 변수 
	UIObject*				m_pUIobj;				//UI오브젝트용 변수
	UIObject*				m_pUIDamage[10];			//데미지용 UIObj변수
	UIObject*				m_pHPBar;					//hp프로그래스바
	UIObject*				m_pStaminaBar;				//스테미너 프로그래스바
	
	MonsterManager*			m_pMonsterManager;		//몬스터 매니저용 변수
	
	D3DXVECTOR3				m_vfront;				//이동을 위한 프론트벡터
	D3DXVECTOR3				m_vPotalfront;			//포탈 이동을 위한 프론트 벡터

	int						m_nCalAction;			//액션 프레임 계산용 변수
	int						m_nDamage;				//데미지 띄우기용 변수 

	vector<ST_DAMAGETEXT>		m_vecDamage;			//데미지 저장용 변수

	bool					m_bIsFront;				//앞인지 뒤인지
	bool					m_bIsDash;				//대쉬했늬
	bool					m_bIsAttack;			//일반공격 했늬?
	bool					m_bIsUnderAttacked;		//공격받았니?
	bool					m_bIsSkill;				//스킬썼니?
	bool					m_bIsInvincible;			//무적이니
	bool					m_bIsPotal;				//지금 포탈 눌렀니?
	float					m_fDamageCount;			//데미지 띄우는 카운트
	float					m_fDamageAngle;			//데미지 앵글

	GET(bool,m_bIsDead,IsDead);						//죽었늬
	float					m_fStamina;				//스테미나 게이지
	

	vector<D3DXVECTOR3*>	m_vecVertex;			//디버그용 벡터
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
	void UnderAttacked();
	
	void SetCurrentHP(int hp);
	void CalculDamage(float damage);
	void Attack();
	void CountAppearDamage();
	void SkillIconAlpha();
	void PlayerProgressBar();
	void MGSKill();

	int						m_temp;			//애니메이션 확인용 임시변수


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager);
	virtual void Update() = 0;
	virtual void Render();
	virtual void KeyControl(); 
	virtual void ChangeAnimation();
};