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
	

	int		m_nCurrentHP;	//ĳ����(��, �÷��̾�) ���� ��
	int		m_nMaxHp;		//ĳ����(��, �÷��̾�) �ִ� ��

	int		m_nItemHP;		//������ ȿ���� �ִ� ��

	int		m_nAtk;			//���ݷ� (��,��,�� �������� �������ؼ� �� �ٲٸ� �ɵ� �ͽ��ϴ�.)
	int		m_nDef;			//����

	float	m_fAgi;			//ȸ�Ƿ�
	float	m_fHit;			//���߷�
	float	m_fSpeed;		//�̵��ӵ�

	

public:
	Status();
	~Status();
};
