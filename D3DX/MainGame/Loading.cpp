#include "../stdafx.h"
#include "Loading.h"

//로딩에 쓰일 아이템 하나하나의 함수들
LoadItem::LoadItem()
{

}

LoadItem::~LoadItem()
{

}

void LoadItem::LoadModel(string keyName, string folderPath, string fileName, MODELTYPE type)
{
	/*
	string keyName;
	string folderPath;	//텍스쳐는 이 변수가 path다
	string fileName;
	MODELTYPE type;
	*/
	/*
		LK_MODEL,		//모델
	LK_TEXTURE,		//텍스쳐
	LK_SINGLETONE,	//싱글톤
	LK_END		
	*/

	m_eKind = LK_MODEL;
	m_stResource.keyName = keyName;
	m_stResource.folderPath = folderPath;
	m_stResource.fileName = fileName;
	m_stResource.type = type;
}

void LoadItem::LoadTexture(string keyName, string path)
{
	m_eKind = LK_TEXTURE;
	m_stResource.keyName = keyName;
	m_stResource.folderPath = path;
}

void LoadItem::LoadSound(string keyName, string path, bool loop)
{
	m_eKind = LK_SOUND;
	m_stResource.keyName = keyName;
	m_stResource.folderPath = path;
	m_stResource.loop = loop;
}

void LoadItem::LoadParticle(string keyName, string TextureKeyName, string Path)
{
	//fileName
	m_eKind = LK_PARTICLE;
	m_stResource.keyName = keyName;
	m_stResource.folderPath = TextureKeyName;
	m_stResource.fileName = Path;
}


//로딩할 전체 클래스 함수들
Loading::Loading()
{

}


Loading::~Loading()
{
	for (int i = 0; i < m_vLoadItem.size(); i++)
	{
		SAFE_DELETE(m_vLoadItem[i]);
	}
}

void Loading::Setup()
{
	m_nCurrentGauge = 0;
}

BOOL Loading::LoadingDone()
{
	if (m_nCurrentGauge >= m_vLoadItem.size())
		return true;

	LoadItem* item = m_vLoadItem[m_nCurrentGauge];

	switch (item->GetLoadKind())
	{
	case LK_MODEL:
	{
		RESOURCE resource = item->GetItemResource();
		MODELMANAGER->AddModel(resource.keyName,
			resource.folderPath,
			resource.fileName,
			resource.type);
	}
	break;

	case LK_TEXTURE:
	{
		RESOURCE resource = item->GetItemResource();
		TEXTUREMANAGER->AddTexture(resource.keyName,
			resource.folderPath);
	}
	break;

	case LK_SOUND:
	{
		RESOURCE resource = item->GetItemResource();
		SOUND->AddSound(resource.keyName, resource.folderPath, resource.loop);
	}
	break;

	case LK_PARTICLE:
	{
		////AddParticle("ttest", TEXTUREMANAGER->GetTexture("파티클시험"), "./Particle/ttest.ptc");z
		RESOURCE resource = item->GetItemResource();
		PARTICLE->AddParticle(resource.keyName, 
			TEXTUREMANAGER->GetTexture(resource.folderPath),
			resource.fileName);
		//SOUND->AddSound(resource.keyName, resource.folderPath, resource.loop);
	}
	break;
	}
	m_nCurrentGauge++;

	return false;
}


void Loading::LoadModel(string keyName, string folderPath, string fileName, MODELTYPE type)
{
	LoadItem* item = new LoadItem;
	item->LoadModel(keyName, folderPath, fileName, type);

	m_vLoadItem.push_back(item);
}

void Loading::LoadTexture(string keyName, string path)
{
	LoadItem* item = new LoadItem;
	item->LoadTexture(keyName, path);

	m_vLoadItem.push_back(item);
}

void Loading::LoadSound(string keyName, string path, bool loop)
{
	LoadItem* item = new LoadItem;
	item->LoadSound(keyName, path, loop);

	m_vLoadItem.push_back(item);
}

void Loading::LoadParticle(string keyName, string TextureKeyName, string Path)
{
	LoadItem* item = new LoadItem;
	item->LoadParticle(keyName, TextureKeyName, Path);

	m_vLoadItem.push_back(item);
}

void Loading::LoadSingletone(string keyName, const char* fileName)
{

}
