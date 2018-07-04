#pragma once

class Map;
class CharacterParant;
//Jae
class PathFind;
class MonsterManager;
//Youn
class ItemParent;
class HealthPotion;

class SC_Test : public Scene
{
private:
	CharacterParant*	m_pTestModel;
	Map *		m_pSampleMap;

	//Jae
	PathFind* m_pPathFind;
	MonsterManager* m_pMM;
	//youn
	ItemParent* m_pItem;
	HealthPotion* m_pPotion;

public:
	SC_Test();
	~SC_Test();

	void Release();
	void Init();
	void Update();
	void Render();
};

