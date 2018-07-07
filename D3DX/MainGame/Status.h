#pragma once

#define CURRENTHP(varName)	varName.chr.nCurrentHP	
#define MAXHP(varName)	varName.chr.nMaxHp	

#define CURRENTSTAM(varName)	varName.chr.nCurrentStam	
#define MAXSTAM(varName)	varName.chr.nMaxStam	

#define ATK(varName)	varName.chr.nAtk	
#define PHYRATE(varName)	varName.chr.fPhyRate	
#define MAGICRATE(varName)	varName.chr.fMagicRate	
#define CHERATE(varName)	varName.chr.fCheRate	
#define ATKSPEED(varName)	varName.chr.fAtkSpeed	

#define DEF(varName)	varName.chr.nDef	
#define AGI(varName)	varName.chr.fAgi	
#define HIT(varName)	varName.chr.fHit	
#define SPEED(varName)	varName.chr.fSpeed	



union STATUS
{
	struct ST_STATUS_CHARACTER
	{
		// ������ ���� + ĳ���� ���� = �ɷ�ġ
		int		nCurrentHP;		//ĳ����(��, �÷��̾�) ���� ��
		int		nMaxHp;			//ĳ����(��, �÷��̾�) �ִ� ��

		int		nCurrentStam;	//ĳ���� ���� ���׹̳�
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
};

struct ST_DAMAGE
{
	int		nDamage;
	float	fPhyRate;
	float	fMagicRate;
	float	fCheRate;
};
