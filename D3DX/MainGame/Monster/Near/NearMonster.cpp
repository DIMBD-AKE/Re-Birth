#include "../../../stdafx.h"
#include "NearMonster.h"


NearMonster::NearMonster()
{
}


NearMonster::~NearMonster()
{

}

void NearMonster::Setup(Map* map, D3DXVECTOR3 spawnPos)
{
	//부모의 셋업을 호출해라
	MonsterParent::Setup(map, spawnPos);
}

void NearMonster::SetupStat()
{

}

void NearMonster::Attack()
{

}

void NearMonster::Skill()
{

}

void NearMonster::Move()
{

}

void NearMonster::DropItemSetup()
{

}