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

enum CHRTYPE   //캐릭터 타입
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


enum CHAR_CONDITION			//캐릭터 컨디션
{
	CHAR_IDLE,				//캐릭터 대기
	CHAR_DASH_FRONT,		//캐릭터 대쉬 앞
	CHAR_DASH_BACK,			//캐릭터 대쉬 뒤
	CHAR_RUN_FRONT,			//캐릭터 달리기
	CHAR_RUN_BACK,			//캐릭터 뒤로 달리기
	CHAR_SKILL,				//캐릭터 스킬쓰기
	CHAR_ATTACK,			//캐릭터 일반공격
	CHAR_DIE,				//캐릭터 죽음
	CHAR_HIT,				//캐릭터 피격
	CHAR_BATTLEREADY,		//캐릭터 선택됨
	CHAR_NONE				//죽은뒤의 None상태
};


