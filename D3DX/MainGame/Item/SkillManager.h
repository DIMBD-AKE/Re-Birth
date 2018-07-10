#pragma once
#include "SkillParent.h"

class SkillManager
{
private:
	map<string, SkillParent*>	m_mSkillIndex;
	FILE *	m_fp;
	char	m_szToken[1024];
private:
	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhite(IN char c);
	bool	IsEqual(IN const char* str1, IN const char* str2);

public:
	SkillManager();
	~SkillManager();
	void Load(IN const char* szFolder, IN const char* szFile);
	SkillParent* GetSkill(string keyName);
};

