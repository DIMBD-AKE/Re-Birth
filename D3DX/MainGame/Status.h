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
		// ������ ���� + ĳ���� ���� = �ɷ�ġ
		int		nCurrentHP;		//ĳ����(��, �÷��̾�) ���� ��
		int		nMaxHp;			//ĳ����(��, �÷��̾�) �ִ� ��

		float	nCurrentStam;	//ĳ���� ���� ���׹̳�
		int		nMaxStam;		//ĳ���� ��ü ���׹̳�

		int		nAtk;			//�⺻���ݷ�
		float	fPhyRate;		//�������
		float	fMagicRate;		//�������
		float	fCheRate;		//ȭ�а��
		float	fAtkSpeed;		//���ݼӵ� (���ӵ��� * ����)

		int		nDef;			//����
		float	fAgi;			//ȸ�Ƿ�
		float	fHit;			//���߷�
		float	fSpeed;			//�̵��ӵ�
		float	fRange;			//���� �Ÿ�
		float	fScale;			//���� ����
	} chr;

	struct ST_STATUS_ITEM
	{
		float	fAtkSpeed;		//���ݼӵ�
		float	fCoolTime1;		//��ų1 ��Ÿ��
		float	fCoolTime2;		//��ų2 ��Ÿ��

		int      nSkillAtk1;	//��ų1 ������
		int      nSkillAtk2;	//��ų2 ������

		int		nAtk;			//���ݷ� ������
		int		nDef;			//���� ������
		int		nHp;			//ü�� ������
		float	fAgi;			//ȸ�Ƿ� ������
		float	fHit;			//���߷� ������
		float	fSpeed;			//�̵��ӵ� ������
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
