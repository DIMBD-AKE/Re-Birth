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

	
	//플레이어 
	MODELMANAGER->AddModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("아카날", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	MODELMANAGER->AddModel("헤스티아", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("메그너스", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("리아", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("스카디", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	MODELMANAGER->AddModel("베카", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("벨벳", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	//실드캐릭터
	MODELMANAGER->AddModel("렘논", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);
}

void LoadingSC::AddTexture()
{
	TEXTUREMANAGER->AddTexture("MonBackBar", "./Model/Enemy/UI/백바.jpg");
	TEXTUREMANAGER->AddTexture("MonFrontBar", "./Model/Enemy/UI/프론트바.jpg");

	TEXTUREMANAGER->AddTexture("BossBackBar", "./Model/Enemy/UI/보스백바.jpg");
	TEXTUREMANAGER->AddTexture("BossFrontBar", "./Model/Enemy/UI/보스프론트바.jpg");




	//플레이어 사진
	TEXTUREMANAGER->AddTexture("아카날_사진", "Texture/Portrait/Portrait_PC_Aknal_S_Icon.png");
	TEXTUREMANAGER->AddTexture("아린_사진", "Texture/Portrait/Portrait_PC_Arin_S_Icon.png");
	TEXTUREMANAGER->AddTexture("베카_사진", "Texture/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	TEXTUREMANAGER->AddTexture("헤스티아_사진", "Texture/Portrait/Portrait_PC_Hestia_S_Icon.png");
	TEXTUREMANAGER->AddTexture("메그너스_사진", "Texture/Portrait/Portrait_Pc_Magnus_Icon.png");
	TEXTUREMANAGER->AddTexture("리아_사진", "Texture/Portrait/Portrait_PC_Riah_S_Icon.png");
	TEXTUREMANAGER->AddTexture("스카디_사진", "Texture/Portrait/Portrait_PC_Skadi_S_Icon.png");
	TEXTUREMANAGER->AddTexture("벨벳_사진", "Texture/Portrait/velvet.png");

	//플레이어 데미지 이미지 
	TEXTUREMANAGER->AddTexture("숫자0", "Texture/Damage/0.png");
	TEXTUREMANAGER->AddTexture("숫자1", "Texture/Damage/1.png");
	TEXTUREMANAGER->AddTexture("숫자2", "Texture/Damage/2.png");
	TEXTUREMANAGER->AddTexture("숫자3", "Texture/Damage/3.png");
	TEXTUREMANAGER->AddTexture("숫자4", "Texture/Damage/4.png");
	TEXTUREMANAGER->AddTexture("숫자5", "Texture/Damage/5.png");
	TEXTUREMANAGER->AddTexture("숫자6", "Texture/Damage/6.png");
	TEXTUREMANAGER->AddTexture("숫자7", "Texture/Damage/7.png");
	TEXTUREMANAGER->AddTexture("숫자8", "Texture/Damage/8.png");
	TEXTUREMANAGER->AddTexture("숫자9", "Texture/Damage/9.png");

	TEXTUREMANAGER->AddTexture("숫자0_r", "Texture/Damage/0_r.png");
	TEXTUREMANAGER->AddTexture("숫자1_r", "Texture/Damage/1_r.png");
	TEXTUREMANAGER->AddTexture("숫자2_r", "Texture/Damage/2_r.png");
	TEXTUREMANAGER->AddTexture("숫자3_r", "Texture/Damage/3_r.png");
	TEXTUREMANAGER->AddTexture("숫자4_r", "Texture/Damage/4_r.png");
	TEXTUREMANAGER->AddTexture("숫자5_r", "Texture/Damage/5_r.png");
	TEXTUREMANAGER->AddTexture("숫자6_r", "Texture/Damage/6_r.png");
	TEXTUREMANAGER->AddTexture("숫자7_r", "Texture/Damage/7_r.png");
	TEXTUREMANAGER->AddTexture("숫자8_r", "Texture/Damage/8_r.png");
	TEXTUREMANAGER->AddTexture("숫자9_r", "Texture/Damage/9_r.png");

	//플레이어 프로그래스바
	TEXTUREMANAGER->AddTexture("플레이어_프론트바", "Texture/PlayerProgressBar/frontBar.jpg");
	TEXTUREMANAGER->AddTexture("플레이어_백바", "Texture/PlayerProgressBar/backBar.jpg");

	TEXTUREMANAGER->AddTexture("스테미나_프론트바", "Texture/PlayerProgressBar/staminaFrontBar.jpg");
	TEXTUREMANAGER->AddTexture("스테미나_백바", "Texture/PlayerProgressBar/staminaBackBar.jpg");

	//쉴드 프로그래스바
	TEXTUREMANAGER->AddTexture("실드_프론트바", "Texture/PlayerProgressBar/shieldHp.jpg");
	TEXTUREMANAGER->AddTexture("실드_백바", "Texture/PlayerProgressBar/shieldBack.jpg");

	//로딩 이미지
	TEXTUREMANAGER->AddTexture("로딩이미지", "Texture/Loading/Load1.png");

}

void LoadingSC::Update()
{
	LoadingImg->SetTexture(TEXTUREMANAGER->GetTexture("로딩이미지"));
	LoadingImg->Update();
}

void LoadingSC::Render()
{
	LoadingImg->Render();

}
