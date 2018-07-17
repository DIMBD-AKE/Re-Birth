#pragma once
#include "ItemHeaderIndex.h"


#define ITEMMANAGER ItemManager::GetInstance()

struct ST_SKILL;

class ItemManager
{
	SINGLETONE(ItemManager);
private:
	typedef map<int, ItemParent*> mItemList;
	typedef map<int, ItemParent*>::iterator mItItemList;
	typedef map<string, ST_SKILL*> mSkillDataList;
	mItemList m_mIdItem;
	mSkillDataList m_mSkList;

	FILE *	m_fp;
	char	m_szToken[1024];
	
private:	
	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhite(IN char c);
	bool	IsEqual(IN const char* str1, IN const char* str2);

public:
	void SetUp();
	void Load(IN const char* szFolder, IN const char* szFile);
	void LoadSkillData(IN const char* szFolder, IN const char* szFile);
	ItemParent* GetItem(int keyNum);

	int FindItem(int keyNum);

	void Destroy();
};

