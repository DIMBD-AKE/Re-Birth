#include "MonsterUseHeader.h"
#include "MonsterManager.h"
#include "TotalMonster.h"

static int overlapInt;

MonsterManager::MonsterManager()
{

}


MonsterManager::~MonsterManager()
{
	//
	/*
	GET(vector<MonsterParent*>, m_vMM, MonsterVector);
	SET(vector<D3DXVECTOR3>, m_vSpawnSpot, SpawnSpat);


	Map* m_pMap;

	CharacterParant** m_ppCharacter;
	*/
	//SAFE_DELETE(m_pMap);
	for (int i = 0; i < m_vMM.size(); i++)
	{
		SAFE_DELETE(m_vMM[i]);
	}

	m_pMap = NULL;
	m_ppCharacter = NULL;

}

void MonsterManager::Setup(Map* map, CharacterParant** character)
{
	m_pMap = map;
	m_ppCharacter = character;
}

void MonsterManager::Update()
{
	assert(m_vSpawnSpot.size() > 0 && "������� ���Ͱ� �����ϴ�.");

	//char temp[222];
	//sprintf_s(temp, sizeof(temp), "%f",
	//	GetDistance(*m_vMM[0]->GetModel()->GetPosition(), *CHARACTER->GetPosition()));
	//TEXT->Add(temp, 100, 100, 20);

	for (int i = 0; i < m_vMM.size(); i++)
	{
		if (m_vMM[i]->GetIsResPawn())
		{

			//������ ���̸� ���� �ð����� ���ư���.
			m_vMM[i]->RespawnUpdate();

			//������ Ư���ð��� �Ǹ� �� �οﰪ�� false�� �ǰ� ��ȯ��Ű�� ���̵ǹǷ�
			//Ư�� ��ġ�� ����� ��Ų��.
			if (!m_vMM[i]->GetIsResPawn())
			{
				//m_vMM[i]->~MonsterParent();

				int spotSize = m_vSpawnSpot.size();

				srand(time(NULL));

				//���Ϳ��� ���� �ε��� ����
				int spotIndex = rand() % spotSize;

				m_vMM[i]->Respawn(m_vSpawnSpot[spotIndex]);
				//�¾� ȣ���Ͽ� �ٽ� ������Ѵ�.
				//m_vMM[i]->Setup(m_pMap, m_vSpawnSpot[spotIndex]);


			}
		}
		{
			m_vMM[i]->Update();
		}
	}

	if (INPUT->KeyDown('1'))
	{
		m_vMM[0]->SetAttak();
	}
	if (INPUT->KeyDown('2'))
	{
		m_vMM[0]->SetSkill();
		//m_vMM[2]->SetSkill();
	}
	if (INPUT->KeyDown('3'))
	{
		MakeMiddleBoss(NULL);
	}

	if (INPUT->KeyDown('5'))
	{
		MakeFinalBoss(NULL);
	}
}

void MonsterManager::Render()
{
	assert(m_vSpawnSpot.size() > 0 && "������� ���Ͱ� �����ϴ�.");

	//TEXT->Render();
	for (int i = 0; i < m_vMM.size(); i++)
	{
		m_vMM[i]->Render();
	}
}


//���� ����� �Լ�
void MonsterManager::MakeMonster(DropManager* pDropManager)
{
	int spotSize = m_vSpawnSpot.size();

	//���Ϳ��� ���� �ε��� ����
	//�ʱⰪ ���� ����
	overlapInt = rand() % spotSize;

	MakeElizabeth(pDropManager);
	
	MakeAssis(pDropManager);
	//
	MakeDarkHell(pDropManager);
	//
	MakeNifilHeim(pDropManager);
	
	MakeNerisa(pDropManager);
	
	MakeNike(pDropManager);
	//
	//
	//MakeFinalBoss(pDropManager);
	
}

void MonsterManager::MakeMonster()
{
	MakeElizabeth(NULL, true);

	MakeAssis(NULL, true);

	MakeDarkHell(NULL, true);

	MakeNifilHeim(NULL, true);

	MakeNerisa(NULL, true);

	MakeNike(NULL, true);
}

//����
void MonsterManager::MakeElizabeth(DropManager* pDropManager, bool isSummon)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	while (overlapInt == spotIndex)
	{
		spotIndex = rand() % spotSize;
	}
	
	overlapInt = spotIndex;

	//���� ����
	MonsterParent* elizabeth;
	elizabeth = new Elizabeth;
	elizabeth->Setup(m_pMap, m_vSpawnSpot[spotIndex], isSummon);
	elizabeth->SetCharacter(m_ppCharacter);
	elizabeth->SetDropManager(pDropManager);

	m_vMM.push_back(elizabeth);
}

void MonsterManager::MakeAssis(DropManager* pDropManager, bool isSummon)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	while (overlapInt == spotIndex)
	{
		spotIndex = rand() % spotSize;
	}

	overlapInt = spotIndex;

	//���� ����
	MonsterParent* assis;
	assis = new Assis;
	assis->Setup(m_pMap, m_vSpawnSpot[spotIndex], isSummon);
	assis->SetCharacter(m_ppCharacter);
	assis->SetDropManager(pDropManager);

	m_vMM.push_back(assis);
}


//���Ÿ�
void MonsterManager::MakeNerisa(DropManager* pDropManager, bool isSummon)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	while (overlapInt == spotIndex)
	{
		spotIndex = rand() % spotSize;
	}

	overlapInt = spotIndex;

	//���� ����
	MonsterParent* nerisa;
	nerisa = new Nerisa;
	nerisa->Setup(m_pMap, m_vSpawnSpot[spotIndex], isSummon);
	nerisa->SetCharacter(m_ppCharacter);
	nerisa->SetDropManager(pDropManager);

	m_vMM.push_back(nerisa);
}

void MonsterManager::MakeNike(DropManager* pDropManager, bool isSummon)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	while (overlapInt == spotIndex)
	{
		spotIndex = rand() % spotSize;
	}

	overlapInt = spotIndex;

	//���� ����
	MonsterParent* nike;
	nike = new Nike;
	nike->Setup(m_pMap, m_vSpawnSpot[spotIndex], isSummon);
	nike->SetCharacter(m_ppCharacter);
	nike->SetDropManager(pDropManager);

	m_vMM.push_back(nike);
}


//����
void MonsterManager::MakeDarkHell(DropManager* pDropManager, bool isSummon)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	while (overlapInt == spotIndex)
	{
		spotIndex = rand() % spotSize;
	}

	overlapInt = spotIndex;

	//���� ����
	MonsterParent* darkHell;
	darkHell = new DarkHell;
	darkHell->Setup(m_pMap, m_vSpawnSpot[spotIndex], isSummon);
	darkHell->SetCharacter(m_ppCharacter);
	darkHell->SetDropManager(pDropManager);

	m_vMM.push_back(darkHell);
}

void MonsterManager::MakeNifilHeim(DropManager* pDropManager, bool isSummon)
{
	int spotSize = m_vSpawnSpot.size();

	srand(time(NULL));

	//���Ϳ��� ���� �ε��� ����
	int spotIndex = rand() % spotSize;

	while (overlapInt == spotIndex)
	{
		spotIndex = rand() % spotSize;
	}

	overlapInt = spotIndex;

	//���� ����
	MonsterParent* nifilHeim;
	nifilHeim = new NifilHeim;
	nifilHeim->Setup(m_pMap, m_vSpawnSpot[spotIndex], isSummon);
	nifilHeim->SetCharacter(m_ppCharacter);
	nifilHeim->SetDropManager(pDropManager);

	m_vMM.push_back(nifilHeim);
}

void MonsterManager::MakeMiddleBoss(DropManager* pDropManager)
{

	MonsterParent* finalBoss;

	finalBoss = new FinalBoss;
	finalBoss->SetupBoss(m_pMap, m_pMap->GetSpawnBoss());
	finalBoss->SetCharacter(m_ppCharacter);
	finalBoss->SetDropManager(pDropManager);
	dynamic_cast<FinalBoss*>(finalBoss)->SetMM(this);
	//finalBoss->SetupBoss(m_pMap, m_vSpawnSpot[0]);

	m_vMM.push_back(finalBoss);

}

void MonsterManager::MakeFinalBoss(DropManager* pDropManager)
{

	MonsterParent* realFinalBoss;

	realFinalBoss = new RealFinalboss;
	realFinalBoss->SetCharacter(m_ppCharacter);
	realFinalBoss->SetupBoss(m_pMap, m_pMap->GetSpawnBoss());
	realFinalBoss->SetDropManager(pDropManager);
	//dynamic_cast<FinalBoss*>(realFinalBoss)->SetMM(this);
	//finalBoss->SetupBoss(m_pMap, m_vSpawnSpot[0]);

	m_vMM.push_back(realFinalBoss);

}

void MonsterManager::DeleteSummonMonster()
{

	for (int i = 0; i < m_vMM.size();++i)
	{
		//��ȯ�ȸ��̳�
		if (m_vMM[i]->GetIsSummon())
		{
			m_vMM[i]->CalculDamage(11111);
			//SAFE_DELETE(m_vMM[i]);
			//m_vMM.erase(m_vMM.begin() + i);
		}
		//��ȯ�� ���̸� �ε��� ����
		//else ++i;
	}
}

bool MonsterManager::IsMiddleBossDie(OUT D3DXVECTOR3* diePos)
{
	//bool endGame = false;
	for (int i = 0; i < m_vMM.size(); i++)
	{
		if (m_vMM[i]->IsMiddleBossDie())
		{
			if(diePos)
				*diePos = *m_vMM[i]->GetModel()->GetPosition();
			return true;
		}
	}
	return false;
}

bool MonsterManager::IsBossDie()
{
	for (int i = 0; i < m_vMM.size(); i++)
	{
		if (m_vMM[i]->IsBossDie())		
		{
			
			return true;
		}
	}

	return false;
}

void MonsterManager::SetNpc(Npc * npc)
{
	for (int i = 0; i < m_vMM.size(); ++i)
	{
		m_vMM[i]->SetNPC(npc);
	}
}
