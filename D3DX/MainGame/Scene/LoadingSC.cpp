#include "../../stdafx.h"
#include "LoadingSC.h"


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
	MODELMANAGER->AddModel("�ƽý�", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);

	SCENE->ChangeScene("Test", true);
}

void LoadingSC::Update()
{

}

void LoadingSC::Render()
{

}
