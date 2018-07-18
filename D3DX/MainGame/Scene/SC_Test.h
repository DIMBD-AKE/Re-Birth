#pragma once

class Map;
class CharacterParant;
class MonsterManager;
class DropManager;
class EffectObject;
class Skill;

class SC_Test : public Scene
{
private:
	Map *				m_pSampleMap;
	CharacterParant*	m_pCharacter;
	MonsterManager *	m_pMM;
	DropManager *		m_pDropManager;

	Skill * m_pSkill;
		
public:
	SC_Test();
	~SC_Test();

	void Release();
	void Init();
	void Update();
	void Render();
};

