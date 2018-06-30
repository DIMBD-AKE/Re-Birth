#pragma once

class TestItem;
class Map;

//캐릭터의 원형 클래스

enum CHRTYPE   //캐릭터 타입
{
	CHRTYPE_GUN,
	CHRTYPE_SWORD,
	CHRTYPE_MAGIC
};

enum ANIMATIONTYPE
{
	ANI_IDLE,				//대기상태
	ANI_RUN,				//이동(달리기)
	ANI_SKILL,				//스킬공격
	ANI_ATTACK,				//일반공격
	ANI_DIE,				//죽음
	ANI_HIT					//피격상태
};

struct ST_CHR_STAT  //기본 캐릭터 스텟
{
	float MoveSpeed;		//이동속도
	float STR;				//근접 공격력
	float INT;				//마법 공격력
	float DEX;				//원거리 공격력
	float AGI;				//회피력 
	float DEF;				//방어력
	float HP;				//체력
};




class CharacterParant
{
protected:
	CHRTYPE					m_eChrType;			//캐릭터 타입
	ST_CHR_STAT				m_stDefaltStat;		//장비장착 [전]의 스텟
	ST_CHR_STAT				m_stFinalStat;		//장비장착 [후]의 스탯

	TestItem*				m_pFirstItem;		//첫번쨰 스킬 장비


	Model*					m_pCharacter;		//캐릭터 맴버 변수 
	Map*					m_pSampleMap;		//맵정보 받는 맴버 변수

	D3DXVECTOR3				m_vfront;			//이동을 위한 프론트벡터


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