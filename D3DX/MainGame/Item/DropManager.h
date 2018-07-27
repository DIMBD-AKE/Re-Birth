#pragma once

class CharacterParant;
class Pet;

struct ST_DROPBOX
{
	int itemID;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
};

class DropManager
{
private:
	vector<ST_DROPBOX>		m_vecDrop;
	Model *					m_pModel;

public:
	DropManager();
	~DropManager();

	void Init();

	void AddDropItem(int itemID, D3DXVECTOR3 pos);
	bool GetDropItem(CharacterParant * character, Pet * pet);

	vector<ST_DROPBOX>& GetDropList() { return m_vecDrop; }

	void Render();
};