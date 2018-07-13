#include "../../../stdafx.h"
#include "PotionParent.h"
#include "../../Status.h"
#include "../../Character/CharacterParant.h"

PotionParent::PotionParent()
{
}


PotionParent::~PotionParent()
{
}

PotionParent * PotionParent::Clone()
{
	return new PotionParent(*this);
}

void PotionParent::Use(CharacterParant& pCharacter)
{
	//pCharacter.m_Status->chr.nCurrentHP += m_fHealAmount;
}
