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
	Map *				m_pMap;			//맵정보 받는 맴버 변수
	Model*				m_pNpc;			//NPC모델 
	CharacterParant*	m_pPlayer;		//플레이어
	
	Dialogue*			m_pContext;		//다이얼로그
	Dialogue*			m_pEndContext;	//받은후 대화
	GET(bool, m_bIsAppear, IsAppear);	//등장했늬?
	GET(bool,m_bIsCollision, Collision);	 //충돌했늬?
	bool				m_bReward;

	UIObject*			m_pPortrait;	//초상화
	UIObject*			m_pSelect;

	NPCREWARD			m_eSelectReward;
	NPCREWARD			m_eOverReward;

	bool				m_isOnce; // 나왔었는지

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

