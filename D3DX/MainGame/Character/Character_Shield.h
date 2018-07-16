#pragma once
#include "../GameEnum.h"
#include "../../stdafx.h"


class UIObject;
union STATUS;


class Character_Shield
{
public:
	SYNTHESIZE(CHAR_SUBCONDITION, m_eShieldCondition, ShieldCondition);		//쉴드 캐릭터 상태 
	Model*						m_pShieldChr;							//쉴드 캐릭터 변수
	UIObject*					m_pShieldHp;							//쉴드용 HP
	GET(STATUS*, m_Status, status);										//스테이터스 유니온 변수 

	GET(int, m_nShieldMaxHp, ShieldMaxHp);								//실드 체력
	SYNTHESIZE(int, m_nShieldCurHp, ShieldCurHp);								//실드 현재체력;
	SYNTHESIZE(bool, m_bIsDie,IsDie);								//살아있늬

public:
	Character_Shield();
	~Character_Shield();

	void Init(D3DXVECTOR3 pos);
	void Render();
	void Update(D3DXVECTOR3 pos, D3DXVECTOR3 Rot);
	void ChangeSubChrAni();
	void KeyControl();
	void ShieldProgressBar();
	void Die();

};

