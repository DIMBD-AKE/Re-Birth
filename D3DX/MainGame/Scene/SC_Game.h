#pragma once

class Map;
class CharacterParant;
class Npc;
class MonsterManager;
class DropManager;

class Pet;

class SC_Game : public Scene, public IUIFunction
{
private:
	Map *				m_pMap;
	CharacterParant *	m_pCharacter;
	MonsterManager *	m_pMM;
	DropManager *		m_pDropManager;
	Npc*				m_pNpc;

	UIObject *			m_pGameUI;
	UIObject *			m_pPauseUI;

	Pet*				m_pPet;

	bool				m_isStart;

	int					m_nStage;
	float				m_fGenTime;
	float				m_fElapseTime;
	string				m_sChrName;

	vector<Particle*>	m_vecParticle;

public:
	SC_Game();
	virtual ~SC_Game();

	virtual void OnClick(UIObject * pSender);

	virtual void Release();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ShowElapseTime();
	void ClearStage();
	void NextStage();

	void WriteRank();
};

