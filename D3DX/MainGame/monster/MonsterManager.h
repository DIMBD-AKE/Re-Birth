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
	void MakeElizabeth(DropManager* pDropManager);
	void MakeAssis(DropManager* pDropManager);

	//���Ÿ�
	void MakeNerisa(DropManager* pDropManager);
	void MakeNike(DropManager* pDropManager);

	//����
	void MakeDarkHell(DropManager* pDropManager);
	void MakeNifilHeim(DropManager* pDropManager);

public:
	MonsterManager();
	~MonsterManager();

	void Setup(Map* map, CharacterParant** character);
	void Update();
	void Render();

	//���� ����� �Լ�
	void MakeMonster(DropManager* pDropManager);

	//void SetSpawnSpot(vector<D3DXVECTOR3> spawnVec) { m_vSpawnSpot = spawnVec; }
	//
	//make(spawn[i])
};

