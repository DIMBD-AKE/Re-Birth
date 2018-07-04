#pragma once

#define CURRENTHP chr.nCurrentHP
#define MAXHP chr.nMaxHp

#define ATK chr.nAtk
#define PHYRATE chr.fPhyRate
#define MAGICRATE chr.fMagicRate
#define CHERATE chr.fCheRate
#define ATKSPEED chr.fAtkSpeed

#define DEF chr.nDef
#define AGI chr.fAgi
#define HIT chr.fHit
#define SPEED chr.fSpeed

union STATUS
{
	struct ST_STATUS_CHARACTER
	{
		// 아이템 스텟 + 캐릭터 스텟 = 능력치
		int		nCurrentHP;		//캐릭터(적, 플레이어) 현재 피
		int		nMaxHp;			//캐릭터(적, 플레이어) 최대 피

		int		nAtk;			//기본공격력
		float	fPhyRate;		//물리계수
		float	fMagicRate;		//마법계수
		float	fCheRate;		//화학계수
		float	fAtkSpeed;		//공격속도 (장비속도에 * 연산)

		int		nDef;			//방어력
		float	fAgi;			//회피력
		float	fHit;			//명중률
		float	fSpeed;			//이동속도
	} chr;

	struct ST_STATUS_ITEM
	{
		float	fAtkSpeed;		//공격속도
		float	fCoolTime1;		//스킬1 쿨타임
		float	fCoolTime2;		//스킬2 쿨타임

		int		nAtk;			//공격력 증가량
		int		nDef;			//방어력 증가량
		int		nHp;			//체력 증가량
		float	fAgi;			//회피력 증가량
		float	fHit;			//명중률 증가량
		float	fSpeed;			//이동속도 증가량
	} item;
};

struct ST_DAMAGE
{
	int		nDamage;
	float	fPhyRate;
	float	fMagicRate;
	float	fCheRate;
};


#define CURRENTHP chr.nCurrentHP