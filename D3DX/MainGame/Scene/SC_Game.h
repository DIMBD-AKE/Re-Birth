#pragma once

class Map;
class CharacterParant;
class Npc;
class MonsterManager;
class DropManager;

class SC_Game : public Scene
{
private:
	Map *				m_pMap;
	CharacterParant *	m_pCharacter;
	MonsterManager *	m_pMM;
	DropManager *		m_pDropManager;
	UIObject *			m_pUI;
	Npc*				m_pNpc;


	bool				m_isRank;

	int					m_nStage;
	float				m_fGenTime;
	float				m_fElapseTime;
	string				m_sChrName;

	vector<Particle*>	m_vecParticle;

public:
	SC_Game();
	virtual ~SC_Game();

	virtual void Release();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ShowElapseTime();
	void ClearStage();
	void NextStage();

	void WriteRank();
};

