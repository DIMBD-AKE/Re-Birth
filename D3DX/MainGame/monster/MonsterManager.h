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

	CharacterParant** m_ppCharacter;
	//vector<MonsterParent> m_vMM;

private:

	//근접
	void MakeElizabeth(DropManager* pDropManager, bool isSummon = false);
	void MakeAssis(DropManager* pDropManager, bool isSummon = false);

	//원거리
	void MakeNerisa(DropManager* pDropManager, bool isSummon = false);
	void MakeNike(DropManager* pDropManager, bool isSummon = false);

	//마법
	void MakeDarkHell(DropManager* pDropManager, bool isSummon = false);
	void MakeNifilHeim(DropManager* pDropManager, bool isSummon = false);

	//중간보스
	void MakeMiddleBoss(DropManager* pDropManager);

	void MakeFinalBoss(DropManager* pDropManager);
	

public:
	MonsterManager();
	~MonsterManager();

	void Setup(Map* map, CharacterParant** character);
	void Update();
	void Render();

	//몬스터 만드는 함수
	void MakeMonster(DropManager* pDropManager);
	//최종보스의 패시브통해 생성되는 함수
	void MakeMonster();
	//최종 보스 사망시 소환 몬스터 제거 함수
	void DeleteSummonMonster();

	bool IsMiddleBossDie(OUT D3DXVECTOR3* diePos);
	bool IsBossDie();

	//void SetSpawnSpot(vector<D3DXVECTOR3> spawnVec) { m_vSpawnSpot = spawnVec; }
	//
	//make(spawn[i])
};

