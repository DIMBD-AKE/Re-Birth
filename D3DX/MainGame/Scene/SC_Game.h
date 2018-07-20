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
	UIObject *			m_pUI;

	int					m_nStage;
	float				m_fGenTime;
	static float		m_fElapseTime;

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

	static void WriteRank(string name, int item = -1);
};

