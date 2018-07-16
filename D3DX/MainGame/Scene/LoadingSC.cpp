#include "../../stdafx.h"
#include "LoadingSC.h"

#include "../Item/ItemManager.h"

LoadingSC::LoadingSC()
{
}


LoadingSC::~LoadingSC()
{

}

void LoadingSC::Release()
{

}

void LoadingSC::Init()
{
	SingletoneInit();
	AddModel();
	AddTexture();

	SCENE->ChangeScene("Test", true);
}

void LoadingSC::SingletoneInit()
{
	ITEMMANAGER->SetUp();
}

void LoadingSC::AddModel()
{
	//�Ϲ� ����
	MODELMANAGER->AddModel("����", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�ʸ���", "Model/Enemy/Nerisa/", "Nerisa.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��������", "Model/Enemy/NifilHeim/", "NifilHeim.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ũ��", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�ƽý�", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	//�߰�����
	MODELMANAGER->AddModel("���׷�", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	//��������
	MODELMANAGER->AddModel("����", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);

	
}

void LoadingSC::AddTexture()
{
	TEXTUREMANAGER->AddTexture("MonBackBar", "./Model/Enemy/UI/���.jpg");
	TEXTUREMANAGER->AddTexture("MonFrontBar", "./Model/Enemy/UI/����Ʈ��.jpg");

	TEXTUREMANAGER->AddTexture("BossBackBar", "./Model/Enemy/UI/�������.jpg");
	TEXTUREMANAGER->AddTexture("BossFrontBar", "./Model/Enemy/UI/��������Ʈ��.jpg");
}

void LoadingSC::Update()
{

}

void LoadingSC::Render()
{

}
