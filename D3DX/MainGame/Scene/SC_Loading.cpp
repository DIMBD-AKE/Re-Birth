#include "../../stdafx.h"
#include "SC_Loading.h"
#include "../Loading.h"

#include "../Item/ItemManager.h"

SC_Loading::SC_Loading()
: m_pLoading(NULL)
{
}


SC_Loading::~SC_Loading()
{

}

void SC_Loading::Release()
{
	SAFE_DELETE(m_pLoading)
}

void SC_Loading::Init()
{
	m_pLoading = new Loading;
	m_pLoading->Setup();

	//char test[111];
	//sprintf_s(test, sizeof(test), "싱글톤 이닛중입니다");
	//TEXT->Add(test, 100, 100, 40);
	//TEXT->Render();
	SingletoneInit();
	AddModel();
	AddTexture();
	AddSound();

	//SCENE->ChangeScene("Test", true);
}

void SC_Loading::SingletoneInit()
{
	ITEMMANAGER->SetUp();
}

void SC_Loading::AddModel()
{
	//m_pLoading->LoadModel()
	//일반 몬스터
	m_pLoading->LoadModel("니케", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);
	m_pLoading->LoadModel("너리사", "Model/Enemy/Nerisa/", "Nerisa.x", MODELTYPE_X);
	m_pLoading->LoadModel("니플하임", "Model/Enemy/NifilHeim/", "NifilHeim.x", MODELTYPE_X);
	m_pLoading->LoadModel("다크헬", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	m_pLoading->LoadModel("아시스", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	m_pLoading->LoadModel("엘리자베스", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	//중간보스
	m_pLoading->LoadModel("나그로", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	//최종보스
	m_pLoading->LoadModel("보스", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);

	
	//플레이어 
	m_pLoading->LoadModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	m_pLoading->LoadModel("아카날", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	m_pLoading->LoadModel("헤스티아", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	m_pLoading->LoadModel("메그너스", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	m_pLoading->LoadModel("리아", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	m_pLoading->LoadModel("스카디", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	m_pLoading->LoadModel("베카", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	m_pLoading->LoadModel("벨벳", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	//실드캐릭터
	m_pLoading->LoadModel("렘논", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);
}

void SC_Loading::AddTexture()
{
	//m_pLoading->LoadTexture()
	m_pLoading->LoadTexture("MonBackBar", "./Model/Enemy/UI/백바.jpg");
	m_pLoading->LoadTexture("MonFrontBar", "./Model/Enemy/UI/프론트바.jpg");

	m_pLoading->LoadTexture("BossBackBar", "./Model/Enemy/UI/보스백바.jpg");
	m_pLoading->LoadTexture("BossFrontBar", "./Model/Enemy/UI/보스프론트바.jpg");




	//플레이어 사진
	m_pLoading->LoadTexture("아카날_사진", "Texture/Portrait/Portrait_PC_Aknal_S_Icon.png");
	m_pLoading->LoadTexture("아린_사진", "Texture/Portrait/Portrait_PC_Arin_S_Icon.png");
	m_pLoading->LoadTexture("베카_사진", "Texture/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	m_pLoading->LoadTexture("헤스티아_사진", "Texture/Portrait/Portrait_PC_Hestia_S_Icon.png");
	m_pLoading->LoadTexture("메그너스_사진", "Texture/Portrait/Portrait_Pc_Magnus_Icon.png");
	m_pLoading->LoadTexture("리아_사진", "Texture/Portrait/Portrait_PC_Riah_S_Icon.png");
	m_pLoading->LoadTexture("스카디_사진", "Texture/Portrait/Portrait_PC_Skadi_S_Icon.png");
	m_pLoading->LoadTexture("벨벳_사진", "Texture/Portrait/velvet.png");

	//플레이어 데미지 이미지 
	m_pLoading->LoadTexture("숫자0", "Texture/Damage/0.png");
	m_pLoading->LoadTexture("숫자1", "Texture/Damage/1.png");
	m_pLoading->LoadTexture("숫자2", "Texture/Damage/2.png");
	m_pLoading->LoadTexture("숫자3", "Texture/Damage/3.png");
	m_pLoading->LoadTexture("숫자4", "Texture/Damage/4.png");
	m_pLoading->LoadTexture("숫자5", "Texture/Damage/5.png");
	m_pLoading->LoadTexture("숫자6", "Texture/Damage/6.png");
	m_pLoading->LoadTexture("숫자7", "Texture/Damage/7.png");
	m_pLoading->LoadTexture("숫자8", "Texture/Damage/8.png");
	m_pLoading->LoadTexture("숫자9", "Texture/Damage/9.png");

	m_pLoading->LoadTexture("숫자0_r", "Texture/Damage/0_r.png");
	m_pLoading->LoadTexture("숫자1_r", "Texture/Damage/1_r.png");
	m_pLoading->LoadTexture("숫자2_r", "Texture/Damage/2_r.png");
	m_pLoading->LoadTexture("숫자3_r", "Texture/Damage/3_r.png");
	m_pLoading->LoadTexture("숫자4_r", "Texture/Damage/4_r.png");
	m_pLoading->LoadTexture("숫자5_r", "Texture/Damage/5_r.png");
	m_pLoading->LoadTexture("숫자6_r", "Texture/Damage/6_r.png");
	m_pLoading->LoadTexture("숫자7_r", "Texture/Damage/7_r.png");
	m_pLoading->LoadTexture("숫자8_r", "Texture/Damage/8_r.png");
	m_pLoading->LoadTexture("숫자9_r", "Texture/Damage/9_r.png");

	//플레이어 프로그래스바
	m_pLoading->LoadTexture("플레이어_프론트바", "Texture/PlayerProgressBar/frontBar.jpg");
	m_pLoading->LoadTexture("플레이어_백바", "Texture/PlayerProgressBar/backBar.jpg");

	m_pLoading->LoadTexture("스테미나_프론트바", "Texture/PlayerProgressBar/staminaFrontBar.jpg");
	m_pLoading->LoadTexture("스테미나_백바", "Texture/PlayerProgressBar/staminaBackBar.jpg");

	//쉴드 프로그래스바
	m_pLoading->LoadTexture("실드_프론트바", "Texture/PlayerProgressBar/shieldHp.jpg");
	m_pLoading->LoadTexture("실드_백바", "Texture/PlayerProgressBar/shieldBack.jpg");

	//로딩 이미지
	TEXTUREMANAGER->AddTexture("로딩이미지", "Texture/Loading/Load1.png");

}

void SC_Loading::AddSound()
{
	m_pLoading->LoadSound("Main Theme", "Sound/01. Premonition.mp3", true);
}

void SC_Loading::Update()
{
	m_pLoading->Update();

	if (m_pLoading->loadingDone())
	{
		SCENE->ChangeScene("Test", true);
		SOUND->Play("Main Theme");
	}
}

void SC_Loading::Render()
{
	m_pLoading->Render();
}
