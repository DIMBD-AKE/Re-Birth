#pragma once

//struct ST_CHA_HP
//{
//	int m_nCurrentHP;
//	int m_nMaxHp;
//};
//
//union UN_HP
//{
//	ST_CHA_HP m_stCharHP;
//
//	int m_nItemHP;
//};

class Status
{
public:

	//UN_HP		m_unHP;
	

	int		m_nCurrentHP;	//캐릭터(적, 플레이어) 현재 피
	int		m_nMaxHp;		//캐릭터(적, 플레이어) 최대 피

	int		m_nItemHP;		//아이템 효과로 주는 피

	int		m_nAtk;			//공격력 (물,마,원 공통으로 연산통해서 값 바꾸면 될듯 싶습니다.)
	int		m_nDef;			//방어력

	float	m_fAgi;			//회피력
	float	m_fHit;			//명중률
	float	m_fSpeed;		//이동속도

	

public:
	Status();
	~Status();
};
