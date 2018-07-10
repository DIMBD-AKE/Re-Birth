#include "../../stdafx.h"
#include "SkillManager.h"



char * SkillManager::GetToken()
{
	int nReadCount = 0;
	bool isQuote = false;

	while (true)
	{
		char d = fgetc(m_fp);

		if (feof(m_fp))	break;

		if (d == '\"')
		{
			if (isQuote)
				break;

			isQuote = true;
			continue;
		}

		if (!isQuote && IsWhite(d))
		{
			if (nReadCount == 0)
				continue;
			else
				break;
		}

		m_szToken[nReadCount++] = d;
	}

	if (nReadCount == 0)
		return NULL;

	m_szToken[nReadCount] = '\0';

	return m_szToken;
}

int SkillManager::GetInteger()
{
	return atoi(GetToken());
}

float SkillManager::GetFloat()
{
	return (float)atof(GetToken());
}

bool SkillManager::IsWhite(IN char c)
{
	return c < 33;
}

bool SkillManager::IsEqual(IN const char * str1, IN const char * str2)
{
	return strcmp(str1, str2) == 0;
}

SkillManager::SkillManager()
{
}


SkillManager::~SkillManager()
{
}

void SkillManager::Load(IN const char * szFolder, IN const char * szFile)
{
	SkillParent* Sp = NULL;

	string	sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	fopen_s(&m_fp, sFullPath.c_str(), "r");

	char keyName[1024];

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp))
			break;
		if (c == '#')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			ZeroMemory(Sp, sizeof(SkillParent*));
		}

		else if (c == 'D')
		{
			string path = GetToken();

			char* des = new char[strlen(path.c_str()) + 1];
			strcpy_s(des, strlen(path.c_str()) + 1, path.c_str());
		}

	}

	fclose(m_fp);
}

SkillParent* SkillManager::GetSkill(string keyName)
{
	map<string, SkillParent*>::iterator miterId = m_mSkillIndex.find(keyName);

	assert(miterId != m_mSkillIndex.end() && "매니저에 없는 아이템입니다");

	return miterId->second;
}
