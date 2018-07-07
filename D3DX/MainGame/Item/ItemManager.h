#pragma once
#include "ItemHeaderIndex.h"

#define ITEMMANAGER ItemManager::GetInstance()

class ItemManager
{
	SINGLETONE(ItemManager);
private:
	typedef map<int, ItemParent> mItemList;
	typedef map<int, ItemParent>::iterator mItItemList;
	
	mItemList m_mIdItem;
	FILE *	m_fp;
	char	m_szToken[1024];
	
private:	
	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhite(IN char c);
	bool	IsEqual(IN const char* str1, IN const char* str2);

public:
	void Load(IN const char* szFolder, IN const char* szFile);
	ItemParent GetItem(int keyNum);

};

