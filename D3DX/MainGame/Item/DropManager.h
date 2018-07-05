#pragma once

struct ST_DROPBOX
{
	int itemID;
	D3DXVECTOR3 pos;
};

class DropManager
{
private:
	vector<ST_DROPBOX>		m_vecDrop;

public:
	DropManager();
	~DropManager();

	void AddDropItem(int itemID, D3DXVECTOR3 pos);
};