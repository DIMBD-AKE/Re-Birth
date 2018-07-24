#pragma once


class Map;
class CharacterParant;


class Npc
{
private:
	Map *				m_pMap;			//맵정보 받는 맴버 변수
	Model*				m_pNpc;			//NPC모델 
	CharacterParant*	m_pPlayer;		//플레이어
	bool				m_bIsCollision;	//충돌했늬?
	Dialogue*			m_pContext;		//다이얼로그
	GET(bool, m_bIsAppear, IsAppear);	//등장했늬?


public:
	Npc();
	~Npc();

	void Init(D3DXVECTOR3 pos);
	void Update();
	void Render();
	void CheckCollision();
	void Talk();
	void Debug();

	void SetPlayerMemoryAddressLink(CharacterParant* player) { m_pPlayer = player; }

};

