#include "../../../stdafx.h"
#include "GunParent.h"
#include "../../Status.h"
#include "../../monster/MonsterManager.h"
#include "../../monster/MonsterParent.h"

GunParent::GunParent()
{
}


GunParent::~GunParent()
{
}

GunParent * GunParent::Clone()
{
	return new GunParent(*this);
}

void GunParent::Skill1(CharacterParant* pCharacter, ST_DAMAGE pStatus, MonsterManager * pMonsterManager)
{
}
