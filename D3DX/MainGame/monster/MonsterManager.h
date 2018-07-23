#pragma once

class MonsterParent;
class Map;
class CharacterParant;
class DropManager;
//������� ���͵��� �Ѱ��ϴ� Ŭ����
class MonsterManager
{

	GET(vector<MonsterParent*>, m_vMM, MonsterVector);
	SET(vector<D3DXVECTOR3>, m_vSpawnSpot, SpawnSpat);


	Map* m_pMap;

	CharacterParant** m_ppCharacter;
	//vector<MonsterParent> m_vMM;

private:

	//����
	void MakeElizabeth(DropManager* pDropManager, bool isSummon = false);
	void MakeAssis(DropManager* pDropManager, bool isSummon = false);

	//���Ÿ�
	void MakeNerisa(DropManager* pDropManager, bool isSummon = false);
	void MakeNike(DropManager* pDropManager, bool isSummon = false);

	//����
	void MakeDarkHell(DropManager* pDropManager, bool isSummon = false);
	void MakeNifilHeim(DropManager* pDropManager, bool isSummon = false);

	//�߰�����
	void MakeMiddleBoss(DropManager* pDropManager);

	void MakeFinalBoss(DropManager* pDropManager);
	

public:
	MonsterManager();
	~MonsterManager();

	void Setup(Map* map, CharacterParant** character);
	void Update();
	void Render();

	//���� ����� �Լ�
	void MakeMonster(DropManager* pDropManager);
	//���������� �нú����� �����Ǵ� �Լ�
	void MakeMonster();
	//���� ���� ����� ��ȯ ���� ���� �Լ�
	void DeleteSummonMonster();

	bool IsMiddleBossDie(OUT D3DXVECTOR3* diePos);
	bool IsBossDie();

	//void SetSpawnSpot(vector<D3DXVECTOR3> spawnVec) { m_vSpawnSpot = spawnVec; }
	//
	//make(spawn[i])
};

