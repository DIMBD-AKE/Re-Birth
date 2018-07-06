#pragma once
#include "ArmorParent.h"

class ItemManager
{
private:
	typedef map<int, ArmorParent> mArmor;
	GET(mArmor, m_mIdArmor, MIdArmor);
	FILE *	m_fp;
	char m_szToken[1024];


public:
	ItemManager();
	~ItemManager();

	void Load(IN const char* szFolder, IN const char* szFile);

	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool IsWhite(IN char c);
	bool IsEqual(IN const char* str1, IN const char* str2);
};

