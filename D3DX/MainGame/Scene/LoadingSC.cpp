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
	//일반 몬스터
	MODELMANAGER->AddModel("니케", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);
	MODELMANAGER->AddModel("너리사", "Model/Enemy/Nerisa/", "Nerisa.x", MODELTYPE_X);
	MODELMANAGER->AddModel("니플하임", "Model/Enemy/NifilHeim/", "NifilHeim.x", MODELTYPE_X);
	MODELMANAGER->AddModel("다크헬", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	MODELMANAGER->AddModel("아시스", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	MODELMANAGER->AddModel("엘리자베스", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	//중간보스
	MODELMANAGER->AddModel("나그로", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	//최종보스
	MODELMANAGER->AddModel("보스", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);

	
}

void LoadingSC::AddTexture()
{
	TEXTUREMANAGER->AddTexture("MonBackBar", "./Model/Enemy/UI/백바.jpg");
	TEXTUREMANAGER->AddTexture("MonFrontBar", "./Model/Enemy/UI/프론트바.jpg");

	TEXTUREMANAGER->AddTexture("BossBackBar", "./Model/Enemy/UI/보스백바.jpg");
	TEXTUREMANAGER->AddTexture("BossFrontBar", "./Model/Enemy/UI/보스프론트바.jpg");
}

void LoadingSC::Update()
{

}

void LoadingSC::Render()
{

}
