#include "../../../stdafx.h"
#include "SwordParent.h"
#include "../../Status.h"
#include "../../monster/MonsterManager.h"
#include "../../monster/MonsterParent.h"


SwordParent::SwordParent()
{
}


SwordParent::~SwordParent()
{
}

SwordParent * SwordParent::Clone()
{
	return new SwordParent(*this);
}

void SwordParent::Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager * pMonsterManager)
{
}

