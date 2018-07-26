#pragma once

class MonsterParent;
class Map;
class CharacterParant;
class DropManager;
class Npc;

//만들어진 몬스터들을 총괄하는 클래스
class MonsterManager
{

	GET(vector<MonsterParent*>, m_vMM, MonsterVector);
	SET(vector<D3DXVECTOR3>, m_vSpawnSpot, SpawnSpat);

private:
	Map* m_pMap;

	CharacterParant** m_ppCharacter;
	vector<int> m_vSpawnIndex;

	int m_nDieMonsterNum;

	bool m_bAppearMiddleBoss;

	int m_nKeyMonsterIndex;
	bool m_bAppearKeyMonster;
	//vector<MonsterParent> m_vMM;

private:

	//근접
	void MakeElizabeth(DropManager* pDropManager,int spawnIndex, bool isSummon = false);
	void MakeAssis(DropManager* pDropManager, int spawnIndex, bool isSummon = false);

	//원거리
	void MakeNerisa(DropManager* pDropManager, int spawnIndex, bool isSummon = false);
	void MakeNike(DropManager* pDropManager, int spawnIndex, bool isSummon = false);

	//마법
	void MakeDarkHell(DropManager* pDropManager, int spawnIndex, bool isSummon = false);
	void MakeNifilHeim(DropManager* pDropManager, int spawnIndex, bool isSummon = false);

	//중간보스
	void MakeMiddleBoss(DropManager* pDropManager);

	void MakeFinalBoss(DropManager* pDropManager);
	
	void Shuffle();

	void Stage1(DropManager* pDropManager);
	void Stage2(DropManager* pDropManager);
	void Stage3(DropManager* pDropManager);
	void Stage4(DropManager* pDropManager);
public:
	MonsterManager();
	~MonsterManager();

	void Setup(Map* map, CharacterParant** character);
	void Update(int stage);
	void Render();

	//몬스터 만드는 함수
	void MakeMonster(DropManager* pDropManager,  int stage);
	//최종보스의 패시브통해 생성되는 함수
	void MakeMonster();
	//최종 보스 사망시 소환 몬스터 제거 함수
	void DeleteSummonMonster();

	bool IsMiddleBossDie(OUT D3DXVECTOR3* diePos);
	bool IsBossDie();
	bool isKeyMonsterDie();

	void SetNpc(Npc* npc);

	void DamageMonster(int monsterIndex, float damage);

	//void SetSpawnSpot(vector<D3DXVECTOR3> spawnVec) { m_vSpawnSpot = spawnVec; }
	//
	//make(spawn[i])
};

