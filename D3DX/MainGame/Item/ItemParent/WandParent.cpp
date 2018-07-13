#include "../../../stdafx.h"
#include "WandParent.h"
#include "../../Status.h"
#include "../../monster/MonsterManager.h"
#include "../../monster/MonsterParent.h"

WandParent::WandParent()
{
}


WandParent::~WandParent()
{
}

WandParent * WandParent::Clone()
{
	return new WandParent(*this);
}

void WandParent::Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager * pMonsterManager)
{
}
