#include "MonsterUseHeader.h"
#include "MonsterManager.h"
#include "TotalMonster.h"
#include "../Map.h"


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
	
	for (int i = 0; i < m_pMap->GetSpawnEnemy().size(); ++i)
	{
		m_vSpawnIndex.push_back(i);
	}

	Shuffle();

	m_nDieMonsterNum = 0;
}

void MonsterManager::Update()
{
	assert(m_vSpawnSpot.size() > 0 && "������� ���Ͱ� �����ϴ�.");

	char temp[222];
	sprintf_s(temp, sizeof(temp), "���� ���� �� : %d",	m_nDieMonsterNum);
	TEXT->Add(temp, 100, 100, 20);

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

				m_nDieMonsterNum++;
				//�¾� ȣ���Ͽ� �ٽ� ������Ѵ�.
				//m_vMM[i]->Setup(m_pMap, m_vSpawnSpot[spotIndex]);


			}
		}
		else
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
void MonsterManager::MakeMonster(DropManager* pDropManager, int stage)
{
	switch (stage)
	{
	case 0:
		Stage1(pDropManager);
		break;

	case 1:
		Stage2(pDropManager);
		break;

	case 2:
		Stage3(pDropManager);
		break;

	case 3:
		Stage4(pDropManager);
		break;

	default:
		break;
	}
	/*
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
	*/
	
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
void MonsterManager::MakeElizabeth(DropManager* pDropManager, int spawnIndex, bool isSummon)
{

	//���� ����
	MonsterParent* elizabeth;
	elizabeth = new Elizabeth;
	elizabeth->Setup(m_pMap, m_vSpawnSpot[m_vSpawnIndex[spawnIndex]], isSummon);
	elizabeth->SetCharacter(m_ppCharacter);
	elizabeth->SetDropManager(pDropManager);

	m_vMM.push_back(elizabeth);
}

void MonsterManager::MakeAssis(DropManager* pDropManager, int spawnIndex, bool isSummon)
{
	

	//���� ����
	MonsterParent* assis;
	assis = new Assis;
	assis->Setup(m_pMap, m_vSpawnSpot[m_vSpawnIndex[spawnIndex]], isSummon);
	assis->SetCharacter(m_ppCharacter);
	assis->SetDropManager(pDropManager);

	m_vMM.push_back(assis);
}


//���Ÿ�
void MonsterManager::MakeNerisa(DropManager* pDropManager, int spawnIndex, bool isSummon)
{
	

	//���� ����
	MonsterParent* nerisa;
	nerisa = new Nerisa;
	nerisa->Setup(m_pMap, m_vSpawnSpot[m_vSpawnIndex[spawnIndex]], isSummon);
	nerisa->SetCharacter(m_ppCharacter);
	nerisa->SetDropManager(pDropManager);

	m_vMM.push_back(nerisa);
}

void MonsterManager::MakeNike(DropManager* pDropManager, int spawnIndex, bool isSummon)
{
	

	//���� ����
	MonsterParent* nike;
	nike = new Nike;
	nike->Setup(m_pMap, m_vSpawnSpot[m_vSpawnIndex[spawnIndex]], isSummon);
	nike->SetCharacter(m_ppCharacter);
	nike->SetDropManager(pDropManager);

	m_vMM.push_back(nike);
}


//����
void MonsterManager::MakeDarkHell(DropManager* pDropManager, int spawnIndex, bool isSummon)
{
	

	//���� ����
	MonsterParent* darkHell;
	darkHell = new DarkHell;
	darkHell->Setup(m_pMap, m_vSpawnSpot[m_vSpawnIndex[spawnIndex]], isSummon);
	darkHell->SetCharacter(m_ppCharacter);
	darkHell->SetDropManager(pDropManager);

	m_vMM.push_back(darkHell);
}

void MonsterManager::MakeNifilHeim(DropManager* pDropManager, int spawnIndex, bool isSummon)
{
	

	//���� ����
	MonsterParent* nifilHeim;
	nifilHeim = new NifilHeim;
	nifilHeim->Setup(m_pMap, m_vSpawnSpot[m_vSpawnIndex[spawnIndex]], isSummon);
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

void MonsterManager::Shuffle()
{
	srand(time(NULL));

	for (int i = 0; i < 300; i++) {
		int rnd1 = NRand(0, m_vSpawnIndex.size()-1);
		int rnd2 = NRand(0, m_vSpawnIndex.size()-1);

		int temp = m_vSpawnIndex[rnd2];
		m_vSpawnIndex[rnd2] = m_vSpawnIndex[rnd1];
		m_vSpawnIndex[rnd1] = temp;
	}
}

//����
void MonsterManager::Stage1(DropManager* pDropManager)
{
//	MakeMiddleBoss(pDropManager);

	for (int i = 0; i < 20; i+=2)
	{
		MakeElizabeth(pDropManager, i % m_vSpawnIndex.size() );

		MakeAssis(pDropManager, (i+1) % m_vSpawnIndex.size());
	}
}

//����
void MonsterManager::Stage2(DropManager* pDropManager)
{
	for (int i = 0; i < 20; i += 2)
	{
		MakeDarkHell(pDropManager, i % m_vSpawnIndex.size());

		MakeNifilHeim(pDropManager, (i + 1) % m_vSpawnIndex.size());
	}
}

//���Ÿ�
void MonsterManager::Stage3(DropManager* pDropManager)
{
	for (int i = 0; i < 20; i += 2)
	{
		MakeNerisa(pDropManager, i % m_vSpawnIndex.size());

		MakeNike(pDropManager, (i + 1) % m_vSpawnIndex.size());
	}
}

void MonsterManager::Stage4(DropManager* pDropManager)
{
	MakeFinalBoss(pDropManager);
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

void MonsterManager::DamageMonster(int monsterIndex, float damage)
{
	m_vMM[monsterIndex]->CalculDamage(damage, &m_nDieMonsterNum);
}
