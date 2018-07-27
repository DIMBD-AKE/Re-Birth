#pragma once


class Map;
class CharacterParant;
class UIObject;

enum NPCREWARD
{
	NPC_NONE,
	NPC_SKILL,
	NPC_PET
};

class Npc : public IUIFunction
{
private:
	Map *				m_pMap;			//������ �޴� �ɹ� ����
	Model*				m_pNpc;			//NPC�� 
	CharacterParant*	m_pPlayer;		//�÷��̾�
	
	Dialogue*			m_pContext;		//���̾�α�
	Dialogue*			m_pEndContext;	//������ ��ȭ
	GET(bool, m_bIsAppear, IsAppear);	//�����ߴ�?
	GET(bool,m_bIsCollision, Collision);	 //�浹�ߴ�?
	bool				m_bReward;

	UIObject*			m_pPortrait;	//�ʻ�ȭ
	UIObject*			m_pSelect;

	NPCREWARD			m_eSelectReward;
	NPCREWARD			m_eOverReward;

	bool				m_isOnce; // ���Ծ�����

public:
	Npc();
	~Npc();

	virtual void OnEntrance(UIObject * pSender) override;
	virtual void OnExit(UIObject * pSender) override;
	virtual void OnClick(UIObject * pSender) override;

	void Init(D3DXVECTOR3 pos);
	void Update();
	void Render();
	void CheckCollision();
	void SkillUnSeal();
	void PetUnlock();
	void PlusAttack();
	void CameraViewChange();

	void Once() { if (m_bIsAppear) m_isOnce = true; }

	void SetPlayerMemoryAddressLink(CharacterParant* player) { m_pPlayer = player; }

};

