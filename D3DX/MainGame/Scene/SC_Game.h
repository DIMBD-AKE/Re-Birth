#pragma once

class Map;
class CharacterParant;
class MonsterManager;
class DropManager;

class SC_Game : public Scene
{
private:
	Map *				m_pMap;
	CharacterParant *	m_pCharacter;
	MonsterManager *	m_pMM;
	DropManager *		m_pDropManager;

	int					m_nStage;
	float				m_fPlayTime;
	float				m_fGenTime;

public:
	SC_Game();
	virtual ~SC_Game();

	virtual void Release();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ClearStage();
	void NextStage();
};

