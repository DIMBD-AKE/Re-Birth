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
	MODELMANAGER->AddModel("아시스", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);

	SCENE->ChangeScene("Test", true);
}

void LoadingSC::Update()
{

}

void LoadingSC::Render()
{

}
