#pragma once

enum EQUIPTYPE
{
	EQUIP_FIRSTWEAPON,
	EQUIP_HELMET,
	EQUIP_CHEST,
	EQUIP_GLOVES,
	EQUIP_BOOTS,
	EQUIP_POTION,
	EQUIP_END
};

enum CHRTYPE   //ĳ���� Ÿ��
{
	CHRTYPE_GUN,
	CHRTYPE_SWORD,
	CHRTYPE_MAGIC
};

enum CHARSELECT
{
	CHAR_ONE,
	CHAR_TWO,
	CHAR_THREE
};


enum CHAR_CONDITION			//ĳ���� �����
{
	CHAR_IDLE,				//ĳ���� ���
	CHAR_DASH_FRONT,		//ĳ���� �뽬 ��
	CHAR_DASH_BACK,			//ĳ���� �뽬 ��
	CHAR_RUN_FRONT,			//ĳ���� �޸���
	CHAR_RUN_BACK,			//ĳ���� �ڷ� �޸���
	CHAR_SKILL,				//ĳ���� ��ų����
	CHAR_ATTACK,			//ĳ���� �Ϲݰ���
	CHAR_DIE,				//ĳ���� ����
	CHAR_HIT,				//ĳ���� �ǰ�
	CHAR_BATTLEREADY,		//ĳ���� ���õ�
	CHAR_NONE				//�������� None����
};


