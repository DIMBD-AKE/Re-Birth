#pragma once

#define CURRENTHP(varName)	varName->chr.nCurrentHP	
#define MAXHP(varName)	varName->chr.nMaxHp	

#define CURRENTSTAM(varName)	varName->chr.nCurrentStam	
#define MAXSTAM(varName)	varName->chr.nMaxStam	

#define ATK(varName)	varName->chr.nAtk	
#define PHYRATE(varName)	varName->chr.fPhyRate	
#define MAGICRATE(varName)	varName->chr.fMagicRate	
#define CHERATE(varName)	varName->chr.fCheRate	
#define ATKSPEED(varName)	varName->chr.fAtkSpeed	

#define DEF(varName)	varName->chr.nDef	
#define AGI(varName)	varName->chr.fAgi	
#define HIT(varName)	varName->chr.fHit	
#define SPEED(varName)	varName->chr.fSpeed	
#define RANGE(varName)  varName->chr.fRange
#define SCALE(varName)  varName->chr.fScale

union STATUS
{
	struct ST_STATUS_CHARACTER
	{
		// 아이템 스텟 + 캐릭터 스텟 = 능력치
		int		nCurrentHP;		//캐릭터(적, 플레이어) 현재 피
		int		nMaxHp;			//캐릭터(적, 플레이어) 최대 피

		float	nCurrentStam;	//캐릭터 현재 스테미나
		int		nMaxStam;		//캐릭터 전체 스테미나

		int		nAtk;			//기본공격력
		float	fPhyRate;		//물리계수
		float	fMagicRate;		//마법계수
		float	fCheRate;		//화학계수
		float	fAtkSpeed;		//공격속도 (장비속도에 * 연산)

		int		nDef;			//방어력
		float	fAgi;			//회피력
		float	fHit;			//명중률
		float	fSpeed;			//이동속도
		float	fRange;			//공격 거리
		float	fScale;			//공격 범위
	} chr;

	struct ST_STATUS_ITEM
	{
		float	fAtkSpeed;		//공격속도
		float	fCoolTime1;		//스킬1 쿨타임
		float	fCoolTime2;		//스킬2 쿨타임

		int      nSkillAtk1;	//스킬1 데미지
		int      nSkillAtk2;	//스킬2 데미지

		int		nAtk;			//공격력 증가량
		int		nDef;			//방어력 증가량
		int		nHp;			//체력 증가량
		float	fAgi;			//회피력 증가량
		float	fHit;			//명중률 증가량
		float	fSpeed;			//이동속도 증가량
	} item;

	void operator+= (STATUS status)
	{
		chr.nCurrentHP += status.chr.nCurrentHP;
		chr.nMaxHp += status.chr.nMaxHp;

		chr.nCurrentStam += status.chr.nCurrentStam;
		chr.nMaxStam += status.chr.nMaxStam;

		chr.nAtk += status.chr.nAtk;
		chr.fPhyRate += status.chr.fPhyRate;
		chr.fMagicRate += status.chr.fMagicRate;
		chr.fCheRate += status.chr.fCheRate;
		chr.fAtkSpeed += status.chr.fAtkSpeed;

		chr.nDef += status.chr.nDef;
		chr.fAgi += status.chr.fAgi;
		chr.fHit += status.chr.fHit;
		chr.fSpeed += status.chr.fSpeed;
		chr.fRange += status.chr.fRange;
		chr.fScale += status.chr.fScale;
	}

	void operator-= (STATUS status)
	{
		chr.nCurrentHP -= status.chr.nCurrentHP;
		chr.nMaxHp -= status.chr.nMaxHp;

		chr.nCurrentStam -= status.chr.nCurrentStam;
		chr.nMaxStam -= status.chr.nMaxStam;

		chr.nAtk -= status.chr.nAtk;
		chr.fPhyRate -= status.chr.fPhyRate;
		chr.fMagicRate -= status.chr.fMagicRate;
		chr.fCheRate -= status.chr.fCheRate;
		chr.fAtkSpeed -= status.chr.fAtkSpeed;

		chr.nDef -= status.chr.nDef;
		chr.fAgi -= status.chr.fAgi;
		chr.fHit -= status.chr.fHit;
		chr.fSpeed -= status.chr.fSpeed;
		chr.fRange -= status.chr.fRange;
		chr.fScale -= status.chr.fScale;
	}

	void operator*= (int scalar)
	{
		chr.nCurrentHP	*= scalar;
		chr.nMaxHp		*= scalar;


		chr.nAtk *= scalar;

		chr.nDef *=  scalar;
		chr.fAgi *=  scalar;
		chr.fHit *=  scalar;
		chr.fRange *=scalar;
	}
};

struct ST_DAMAGE
{
	int		nDamage;
	float	fPhyRate;
	float	fMagicRate;
	float	fCheRate;
};
