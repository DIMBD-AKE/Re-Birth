#pragma once


class Map;
class CharacterParant;


class Npc
{
private:
	Map *				m_pMap;			//������ �޴� �ɹ� ����
	Model*				m_pNpc;			//NPC�� 
	CharacterParant*	m_pPlayer;		//�÷��̾�
	
	Dialogue*			m_pContext;		//���̾�α�
	GET(bool, m_bIsAppear, IsAppear);	//�����ߴ�?
	GET(bool,m_bIsCollision, Collision);	 //�浹�ߴ�?
	bool				m_bTalk;		//��ȭ�ϰ� �ִ�?

public:
	Npc();
	~Npc();

	void Init(D3DXVECTOR3 pos);
	void Update();
	void Render();
	void CheckCollision();
	void Talk();
	void Debug();
	void SkillUnSeal();
	void PlusAttack();



	void SetPlayerMemoryAddressLink(CharacterParant* player) { m_pPlayer = player; }

};

