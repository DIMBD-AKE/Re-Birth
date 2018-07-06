#pragma once

class MonsterParent;
class Map;
class CharacterParant;
class DropManager;
//만들어진 몬스터들을 총괄하는 클래스
class MonsterManager
{

	GET(vector<MonsterParent*>, m_vMM, MonsterVector);
	SET(vector<D3DXVECTOR3>, m_vSpawnSpot, SpawnSpat);


	Map* m_pMap;

	CharacterParant* m_pCharacter;
	//vector<MonsterParent> m_vMM;

public:
	MonsterManager();
	~MonsterManager();

	void Setup(Map* map, CharacterParant* character);
	void Update();
	void Render();

	//몬스터 만드는 함수
	void MakeMonster(DropManager* pDropManager);

	//void SetSpawnSpot(vector<D3DXVECTOR3> spawnVec) { m_vSpawnSpot = spawnVec; }
	//
	//make(spawn[i])
};

