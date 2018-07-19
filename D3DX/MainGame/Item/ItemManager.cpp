#include "../../stdafx.h"
#include "../Status.h"
#include "ItemManager.h"
#include "../SkillManager.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
	
}

void ItemManager::SetUp()
{
	TEXTUREMANAGER->AddTexture("Star", "Texture/Particle/Star.png"),
	PARTICLE->AddParticle("MAGIC", TEXTUREMANAGER->GetTexture("Star"), "Particle/Particle/Magic effect.ptc");
	PARTICLE->AddParticle("RARE", TEXTUREMANAGER->GetTexture("Star"), "Particle/Particle/Rare effect.ptc");
	PARTICLE->AddParticle("UNIQUE", TEXTUREMANAGER->GetTexture("Star"), "Particle/Particle/Unique effect.ptc");
	
	LoadSkillData("MainGame/Item/Data", "SkillData.txt");
	
	Load("MainGame/Item/Data", "SwordManArmor.txt");
	Load("MainGame/Item/Data", "BaBarianArmor.txt");
	Load("MainGame/Item/Data", "KnightArmor.txt");
	Load("MainGame/Item/Data", "MageArmor.txt");
	Load("MainGame/Item/Data", "ArcherArmor.txt");
	Load("MainGame/Item/Data", "ValkyrieArmor.txt");
	Load("MainGame/Item/Data", "Item-Potion.txt");
	Load("MainGame/Item/Data", "Weapon-Arrow.txt");
	Load("MainGame/Item/Data", "Weapon-Blade.txt");
	Load("MainGame/Item/Data", "Weapon-Side.txt");
	Load("MainGame/Item/Data", "Weapon-Staff.txt");
	Load("MainGame/Item/Data", "Weapon-TwoHandSword.txt");	
	
}

void ItemManager::Load(IN const char * szFolder, IN const char * szFile)
{
	ItemParent* Ap  = NULL;
	
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
			string path = GetToken();
			/*if(path == "Armor") Ap = new ArmorParent;
			else if (path == "TwoHandSword") Ap = new SwordParent;
			else if (path == "Blade") Ap = new BladeParent;
			else if (path == "Arrow") Ap = new GunParent;
			else if (path == "Staff") Ap = new WandParent;
			else if (path == "Side") Ap = new SideParent;
			else if (path == "Potion") Ap = new PotionParent;*/
			Ap = new ItemParent;
			Ap->SetUp();
			//ZeroMemory(Ap, sizeof(ItemParent));
			
		}

		else if (c == 'D')
		{
			string path = GetToken();
			
			char* des = new char [strlen(path.c_str()) + 1];
			strcpy_s(des, strlen(path.c_str()) + 1, path.c_str());
			Ap->SetDesc(des);
			int a = 0;
		}

		else if (c == 'T')
		{
			char* path = GetToken();
			Ap->m_pTexture = TEXTUREMANAGER->AddTexture(keyName, path);
			Ap->m_imageInfo = TEXTUREMANAGER->GetInfo(keyName);
			m_mIdItem.insert(make_pair(Ap->GetID(), Ap));
			
			int a = 0;
		}
		
		else if (c == '/')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			continue;
		}
		
		else if (c == 'N')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			char name[1024];
			sscanf_s(szTemp, " %s", name, 1024);
			string rt(name);
			Ap->SetName(rt);
		}
		else if (c == 'R')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			char rarity[1024];
			sscanf_s(szTemp, " %s", rarity, 1024);			
			string rt(rarity);
			if (rt == "Normal") Ap->SetRarity(RARITY_NORMAL);
			else if (rt == "Magic") Ap->SetRarity(RARITY_MAGIC);
			else if (rt == "Rare") Ap->SetRarity(RARITY_RARE);
			else if (rt == "Unique") Ap->SetRarity(RARITY_UNIQUE);
	
		}

		else if (c == 'I')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			int Id;
			sscanf_s(szTemp, " %d", &Id);
			Ap->SetID(Id);
		}
		else if (c == 'S')
		{
			c = fgetc(m_fp);
			if (c == 'T')
			{
				char szTemp[1024];
				fgets(szTemp, 1024, m_fp);

				STATUS* st = new STATUS;
				sscanf_s(szTemp, " %f %f %f %d %d %d %d %d %f %f %f",
					&st->item.fAtkSpeed, &st->item.fCoolTime1, &st->item.fCoolTime2,
					&st->item.nSkillAtk1, &st->item.nSkillAtk2, &st->item.nAtk, &st->item.nDef,
					&st->item.nHp, &st->item.fAgi, &st->item.fHit, &st->item.fSpeed);
				Ap->SetStatus(*st);
			}
			else if (c == 'K')
			{
				c = fgetc(m_fp);
				if (c == '1')
				{
					char szTemp[1024];
					fgets(szTemp, 1024, m_fp);

					char skillKeyName[1024];
					sscanf_s(szTemp, " %s", skillKeyName, 1024);
					string rt(skillKeyName);

					if (rt == "NULL")
					{
						Ap->SetSkill1(NULL);
						Ap->SetSkill1Data(NULL);
					}
					else
					{
						Skill* temp = SKILL->GetSkill(rt);
						Ap->SetSkill1(temp);
						Ap->SetSkill1Data(m_mSkList[rt]);
					}
				}
				else if (c == '2')
				{
					char szTemp[1024];
					fgets(szTemp, 1024, m_fp);

					char skillKeyName[1024];
					sscanf_s(szTemp, " %s", skillKeyName, 1024);
					string rt(skillKeyName);
					
					if (rt == "NULL")
					{
						Ap->SetSkill2(NULL);
						Ap->SetSkill2Data(NULL);
					}
					else
					{
						Skill* temp = SKILL->GetSkill(rt);
						Ap->SetSkill2(temp);
						Ap->SetSkill2Data(m_mSkList[rt]);
					}
				}
			}
			
		}
		else if (c == 'E')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			EQUIPTYPE et;
			sscanf_s(szTemp, " %d", &et);
			Ap->SetEquipType(et);
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

void ItemManager::LoadSkillData(IN const char * szFolder, IN const char * szFile)
{
	string	sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	fopen_s(&m_fp, sFullPath.c_str(), "r");

	char keyName[1024];


	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp))
			break;

		else if (c == '/')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);

			continue;
		}

		else if (c == 'N')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);
			sscanf_s(szTemp, " %s", keyName, 1024);
		}

		else if (c == 'S')
		{
			char szTemp[1024];
			fgets(szTemp, 1024, m_fp);


			ST_SKILL* sSkill = new ST_SKILL;
			ZeroMemory(sSkill, sizeof(ST_SKILL));
			sscanf_s(szTemp, " %d %f %f %f %f %d %f %f %f %f %d %f %f %f",
				&sSkill->nMaxTarget, &sSkill->fMinLength, &sSkill->fMaxLength, &sSkill->fAngle,
				&sSkill->fDamage, &sSkill->nDamageCount, &sSkill->fDamageInterval, &sSkill->fDamageDelay,
				&sSkill->fBuffTime, &sSkill->fYOffset, &sSkill->isAutoRot,
				&sSkill->fParticleTime, &sSkill->fParticleSpeed, &sSkill->fEffectTime
			);

			m_mSkList[keyName] = sSkill;
		}
	}

	fclose(m_fp);
}

ItemParent* ItemManager::GetItem(int keyNum)
{
	mItItemList miterId = m_mIdItem.find(keyNum);

	assert(miterId != m_mIdItem.end() && "매니저에 없는 아이템입니다");

	
	ItemParent* rt = miterId->second->Clone();
	rt->SetUp();
	if (miterId->second->GetRarity() == RARITY_NORMAL) 	rt->SetParticle(NULL);
	else if (miterId->second->GetRarity() == RARITY_RARE) rt->SetParticle(PARTICLE->GetParticle("RARE"));
	else if (miterId->second->GetRarity() == RARITY_MAGIC) rt->SetParticle(PARTICLE->GetParticle("MAGIC"));
	else if (miterId->second->GetRarity() == RARITY_UNIQUE) rt->SetParticle(PARTICLE->GetParticle("UNIQUE"));
	
	rt->SetStatus(*(miterId->second->GetItemStat()));

	if (miterId->second->GetSkill1())
	{
		Skill* temp = new Skill;
		*temp = *miterId->second->GetSkill1();
		rt->SetSkill1(temp);
	}

	if (miterId->second->GetSkill2())
	{
		Skill* dest = new Skill;
		*dest = *miterId->second->GetSkill2();
		rt->SetSkill2(dest);
	}
	return rt;
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

int ItemManager::FindItem(int keyNum)
{
	//아이템이 없는거면 1값 반환
	if (m_mIdItem.find(keyNum) == m_mIdItem.end())
	{
		return 1;
	}
	//아이템이 있으면 0 반환
	return 0;
}

void ItemManager::Destroy()
{
	mItItemList mIterItem;
		
	for (mIterItem = m_mIdItem.begin(); mIterItem != m_mIdItem.end(); ++mIterItem)
	{
 		SAFE_DELETE(mIterItem->second);
	}

	mSkillDataList::iterator mIterSkill;
	{
		for (mIterSkill = m_mSkList.begin(); mIterSkill != m_mSkList.end(); ++mIterSkill)
		{
			SAFE_DELETE(mIterSkill->second);
		}
	}
}
