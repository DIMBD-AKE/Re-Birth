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
	
	char keyName[1024];

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp))	
			break;

			if (c == 'D')
			{
				char* path = GetToken();
				string des = path;
				Ap.SetDesc(des);

			}
			else if (c == 'T')
			{
				char* path = GetToken();
				Ap.m_pTexture = TEXTUREMANAGER->AddTexture(keyName, path);
				Ap.m_imageInfo = TEXTUREMANAGER->GetInfo(keyName);
				m_mIdArmor.insert(make_pair(Ap.GetID(), Ap));
				int a = 0;
			}
		
			if (c == '/')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				continue;
			}
			else if (c == '#')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				ZeroMemory(&Ap, sizeof(ArmorParent));
			}
			else if (c == 'N')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				char name[1024];
				sscanf_s(szTemp, " %s", name, 1024);
				string rt(name);
				Ap.SetName(rt);
			}
			else if (c == 'R')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				char rarity[1024];
				sscanf_s(szTemp, " %s", rarity, 1024);
				string rt(rarity);
				Ap.SetRarity(rt);
			}

			else if (c == 'I')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				int Id;
				sscanf_s(szTemp, " %d", &Id);
				Ap.SetID(Id);
			}
			else if (c == 'S')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				STATUS* st = new STATUS;
				sscanf_s(szTemp, " %f %f %f %d %d %d %d %d %f %f %f",
					&st->item.fAtkSpeed, &st->item.fCoolTime1, &st->item.fCoolTime2,
					&st->item.nSkillAtk1, &st->item.nSkillAtk2, &st->item.nAtk, &st->item.nDef,
					&st->item.nHp, &st->item.fAgi, &st->item.fHit, &st->item.fSpeed);
				Ap.SetItemStat(st);
			}
			else if (c == 'E')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				EQUIPTYPE et;
				sscanf_s(szTemp, " %d", &et);
				Ap.SetEquipType(et);
			}
			else if (c == 'K')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				sscanf_s(szTemp, " %s", keyName, 1024);
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