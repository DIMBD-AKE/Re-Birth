#pragma once

class TestItem;
class Map;
class Inventory;

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
	ANI_HIT,				//피격상태
	ANI_BATTLEREADY			//선택되었을때.
};

enum CHAR_CONDITION			//캐릭터 컨디션
{
	CHAR_IDLE,				//캐릭터 대기
	CHAR_RUN,				//캐릭터 달리기
	CHAR_SKILL,				//캐릭터 스킬쓰기
	CHAR_ATTACK,			//캐릭터 일반공격
	CHAR_DIE,				//캐릭터 죽음
	CHAR_HIT,				//캐릭터 피격
	CHAR_BATTLEREADY		//캐릭터 선택됨
};



class CharacterParant
{
protected:
	CHRTYPE					m_eChrType;			//캐릭터 타입
	//ST_CHR_STAT				m_stDefaltStat;		//장비장착 [전]의 스텟
	//ST_CHR_STAT				m_stFinalStat;		//장비장착 [후]의 스탯

	TestItem*				m_pFirstItem;		//첫번쨰 스킬 장비


	Model*					m_pCharacter;		//캐릭터 맴버 변수 
	Map*					m_pSampleMap;		//맵정보 받는 맴버 변수
	Inventory *				m_pInventory;		//인벤토리용 변수

	D3DXVECTOR3				m_vfront;			//이동을 위한 프론트벡터


	bool					m_bIsPressW;		//W키를 누르고 있는지 불값

	void SKill();
	void Move();
	

	int						m_temp;			//애니메이션 확인용 임시변수


public:
	CharacterParant();
	virtual ~CharacterParant();

	virtual void Init(Map* map);
	virtual void Update() = 0;
	virtual void Render();
	virtual void ChangeAnimation();
};