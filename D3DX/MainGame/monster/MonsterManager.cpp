#include "../../stdafx.h"
#include "MonsterManager.h"
#include "MonsterParent.h"

MonsterManager::MonsterManager()
{
	MonsterParent* test;
	test = new MonsterParent;

	m_vMM.push_back(test);
}


MonsterManager::~MonsterManager()
{
}
