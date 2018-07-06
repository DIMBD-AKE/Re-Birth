#include "../../stdafx.h"
#include "../Status.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::Load(IN const char * szFolder, IN const char * szFile)
{
	ArmorParent Ap;

	string	sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	fopen_s(&m_fp, sFullPath.c_str(), "r");
	
	string keyName;

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp))	break;

		if (c == 'D' || c == 'T')
		{
			if (c == 'D')
			{
			
			}
			else 
			{
				TEXTUREMANAGER->AddTexture(keyName, )
			}
		}

		else
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			if (c == '/')
			{
				continue;
			}
			else if (c == '#')
			{
				ZeroMemory(&Ap, sizeof(ArmorParent));
			}
			else if (c == 'N')
			{
				string name;
				sscanf_s(szTemp, " %s", name, 1024);
				Ap.SetName(name);
			}
			else if (c == 'R')
			{
				string rarity;
				sscanf_s(szTemp, " %s", rarity, 1024);
				Ap.SetRarity(rarity);
			}

			else if (c == 'I')
			{
				int Id;
				sscanf_s(szTemp, " %f", &Id);
				Ap.SetID(Id);
			}
			else if (c == 'S')
			{
				STATUS* st;
				sscanf_s(szTemp, " %f %f %f %d %d %d %d %d %f %f %f",
					&st->item.fAtkSpeed, &st->item.fCoolTime1, &st->item.fCoolTime2,
					&st->item.nSkillAtk1, &st->item.nSkillAtk2, &st->item.nAtk, &st->item.nDef,
					&st->item.nHp, &st->item.fAgi, &st->item.fHit, &st->item.fSpeed);
				Ap.SetItemStat(st);
			}
			else if (c == 'E')
			{
				EQUIPTYPE et;
				sscanf_s(szTemp, " %d", &et);
				Ap.SetEquipType(et);
			}
			else if (c == 'K')
			{
				sscanf_s(szTemp, " %s", keyName, 1024);
			}
		}

	}

	fclose(m_fp);

}

char* ItemManager::GetToken()
{
	int nReadCount = 0;
	bool isQuote = false;

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp))	break;

		if (c == '\"')
		{
			if (isQuote)
				break;

			isQuote = true;
			continue;
		}

		if (!isQuote && IsWhite(c))
		{
			if (nReadCount == 0)
				continue;
			else
				break;
		}

		m_szToken[nReadCount++] = c;
	}

	if (nReadCount == 0)
		return NULL;

	m_szToken[nReadCount] = '\0';

	return m_szToken;
}
int	ItemManager::GetInteger()
{
	return atoi(GetToken());
}
float ItemManager::GetFloat()
{
	return (float)atof(GetToken());
}
bool ItemManager::IsWhite(IN char c)
{
	return c < 33;
}
bool ItemManager::IsEqual(IN const char* str1, IN const char* str2)
{
	return strcmp(str1, str2) == 0;
}