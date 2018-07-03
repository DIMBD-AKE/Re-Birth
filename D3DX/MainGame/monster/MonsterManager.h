#pragma once

class MonsterParent;
class Map;

//������� ���͵��� �Ѱ��ϴ� Ŭ����
class MonsterManager
{

	GET(vector<MonsterParent*>, m_vMM, MonsterManager);
	SET(vector<D3DXVECTOR3>, m_vSpawnSpot, SpawnSpat);

	Map* m_pMap;
	//vector<MonsterParent> m_vMM;

public:
	MonsterManager();
	~MonsterManager();

	void Setup(Map* map);
	void Update();
	void Render();

	//���� ����� �Լ�
	void MakeMonster();

	//void SetSpawnSpot(vector<D3DXVECTOR3> spawnVec) { m_vSpawnSpot = spawnVec; }
	//
	//make(spawn[i])
};

