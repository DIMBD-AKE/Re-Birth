#pragma once
#include "../GameEnum.h"
#include "../../stdafx.h"


class UIObject;
union STATUS;


class Character_Shield
{
public:
	SYNTHESIZE(CHAR_SUBCONDITION, m_eShieldCondition, ShieldCondition);		//���� ĳ���� ���� 
	Model*						m_pShieldChr;							//���� ĳ���� ����
	UIObject*					m_pShieldHp;							//����� HP
	GET(STATUS*, m_Status, status);										//�������ͽ� ���Ͽ� ���� 

	GET(int, m_nShieldMaxHp, ShieldMaxHp);								//�ǵ� ü��
	SYNTHESIZE(int, m_nShieldCurHp, ShieldCurHp);								//�ǵ� ����ü��;
	SYNTHESIZE(bool, m_bIsDie,IsDie);								//����ִ�

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

