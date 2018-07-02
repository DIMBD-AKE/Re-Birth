#pragma once

union STATUS
{
	struct ST_STATUS_CHARACTER
	{
		// ������ ���� + ĳ���� ���� = �ɷ�ġ
		float	fCurrentHP;		//ĳ����(��, �÷��̾�) ���� ��
		float	fMaxHp;			//ĳ����(��, �÷��̾�) �ִ� ��

		float	fAtk;			//�⺻���ݷ�
		float	fPhyRate;		//�������
		float	fMagicRate;		//�������
		float	fCheRate;		//ȭ�а��
		float	fAtkSpeed;		//���ݼӵ� (���ӵ��� * ����)

		float	fDef;			//����
		float	fAgi;			//ȸ�Ƿ�
		float	fHit;			//���߷�
		float	fSpeed;			//�̵��ӵ�
	} chr;

	struct ST_STATUS_ITEM
	{
		float	fAtkSpeed;		//���ݼӵ�
		float	fCoolTime1;		//��ų1 ��Ÿ��
		float	fCoolTime2;		//��ų2 ��Ÿ��

		float	fAtk;			//���ݷ� ������
		float	fDef;			//���� ������
		float	fHp;			//ü�� ������
		float	fAgi;			//ȸ�Ƿ� ������
		float	fHit;			//���߷� ������
		float	fSpeed;			//�̵��ӵ� ������
	} item;
};

struct ST_DAMAGE
{
	float	fDamage;
	float	fPhyRate;
	float	fMagicRate;
	float	fCheRate;
};