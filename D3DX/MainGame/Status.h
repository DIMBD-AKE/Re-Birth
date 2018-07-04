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
		// ������ ���� + ĳ���� ���� = �ɷ�ġ
		int		nCurrentHP;		//ĳ����(��, �÷��̾�) ���� ��
		int		nMaxHp;			//ĳ����(��, �÷��̾�) �ִ� ��

		int		nAtk;			//�⺻���ݷ�
		float	fPhyRate;		//�������
		float	fMagicRate;		//�������
		float	fCheRate;		//ȭ�а��
		float	fAtkSpeed;		//���ݼӵ� (���ӵ��� * ����)

		int		nDef;			//����
		float	fAgi;			//ȸ�Ƿ�
		float	fHit;			//���߷�
		float	fSpeed;			//�̵��ӵ�
	} chr;

	struct ST_STATUS_ITEM
	{
		float	fAtkSpeed;		//���ݼӵ�
		float	fCoolTime1;		//��ų1 ��Ÿ��
		float	fCoolTime2;		//��ų2 ��Ÿ��

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


#define CURRENTHP chr.nCurrentHP