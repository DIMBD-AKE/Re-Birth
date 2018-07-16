#include "../stdafx.h"
#include "Loading.h"

//�ε��� ���� ������ �ϳ��ϳ��� �Լ���
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
	string folderPath;	//�ؽ��Ĵ� �� ������ path��
	string fileName;
	MODELTYPE type;
	*/
	/*
		LK_MODEL,		//��
	LK_TEXTURE,		//�ؽ���
	LK_SINGLETONE,	//�̱���
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


//�ε��� ��ü Ŭ���� �Լ���
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

//��׶��� �� ���α׷����� �۾�
void Loading::Update()
{

	char test[111];
	sprintf_s(test, sizeof(test), "�ε��� %d / %d", m_nCurrentGauge, m_vLoadItem.size());
	TEXT->Add(test, 100, 100, 40);
	
}

//��׶��� �� ���α׷����� ����
void Loading::Render()
{
	TEXT->Render();
}


BOOL Loading::loadingDone()
{
	if (m_nCurrentGauge >= m_vLoadItem.size())
	{
		return true;
	}

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
		TEXTUREMANAGER->AddTexture(resource.keyName	,
			resource.folderPath);
	}
		break;

	default:
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

void Loading::LoadSingletone(string keyName, const char* fileName)
{

}
