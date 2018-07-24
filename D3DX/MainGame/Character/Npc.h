#pragma once


class Map;
class CharacterParant;


class Npc
{
private:
	Map *				m_pMap;			//������ �޴� �ɹ� ����
	Model*				m_pNpc;			//NPC�� 
	CharacterParant*	m_pPlayer;		//�÷��̾�
	bool				m_bIsCollision;	//�浹�ߴ�?
	Dialogue*			m_pContext;		//���̾�α�
	GET(bool, m_bIsAppear, IsAppear);	//�����ߴ�?


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

