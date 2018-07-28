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
	SAFE_RELEASE(m_pUI);
	SAFE_DELETE(m_pLoading)
}

void SC_Loading::Init()
{
	m_pLoading = new Loading;
	m_pLoading->Setup();

	InitUI();

	//char test[111];
	//sprintf_s(test, sizeof(test), "싱글톤 이닛중입니다");
	//TEXT->Add(test, 100, 100, 40);
	//TEXT->Render();
	SingletoneInit();
	AddModel();
	AddTexture();
	AddSound();
	AddParticle();

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
	//중간 보스
	m_pLoading->LoadModel("보스", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);
	//최종 보스
	m_pLoading->LoadModel("최종보스", "Model/Enemy/FinalBoss/", "LoadWell.x", MODELTYPE_X);
	
	//플레이어 
	m_pLoading->LoadModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	m_pLoading->LoadModel("아카날", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	m_pLoading->LoadModel("헤스티아", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	m_pLoading->LoadModel("메그너스", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	m_pLoading->LoadModel("리아", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	m_pLoading->LoadModel("스카디", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	m_pLoading->LoadModel("베카", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	m_pLoading->LoadModel("벨벳", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	m_pLoading->LoadModel("파이란", "Model/Character/Pyran/", "Pyran.x", MODELTYPE_X);
	//실드캐릭터
	m_pLoading->LoadModel("렘논", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);

	//NPC
	m_pLoading->LoadModel("리무", "Model/NPC/Rimoo/", "Rimoo.x", MODELTYPE_X);


	//Pet
	m_pLoading->LoadModel("강아지", "Model/Pet/Bentley/", "Bentley.x", MODELTYPE_X);
	m_pLoading->LoadModel("토끼", "Model/Pet/Bunny/", "Bunny.x", MODELTYPE_X);
	m_pLoading->LoadModel("구미호", "Model/Pet/Miho/", "Miho.x", MODELTYPE_X);
	m_pLoading->LoadModel("양", "Model/Pet/Miri/", "Miri.x", MODELTYPE_X);
	m_pLoading->LoadModel("고양이", "Model/Pet/Nero/", "Nero.x", MODELTYPE_X);
	m_pLoading->LoadModel("용", "Model/Pet/Nir/", "Nir.x", MODELTYPE_X);
	m_pLoading->LoadModel("피닉스", "Model/Pet/Nix/", "Nix.x", MODELTYPE_X);
	m_pLoading->LoadModel("팬더", "Model/Pet/Panda/", "Panda.x", MODELTYPE_X);
	m_pLoading->LoadModel("돼지", "Model/Pet/Penny/", "Penny.x", MODELTYPE_X);
}

void SC_Loading::AddTexture()
{
	//m_pLoading->LoadTexture()
	//몬스터 HP바
	m_pLoading->LoadTexture("MonBackBar", "./Model/Enemy/UI/백바.jpg");
	m_pLoading->LoadTexture("MonFrontBar", "./Model/Enemy/UI/프론트바.jpg");

	m_pLoading->LoadTexture("BossBackBar", "./Model/Enemy/UI/보스백바.jpg");
	m_pLoading->LoadTexture("BossFrontBar", "./Model/Enemy/UI/보스프론트바.jpg");

	//몬스터 데미지 이미지
	m_pLoading->LoadTexture("몬스터숫자0", "Texture/Damage/0_r.png");
	m_pLoading->LoadTexture("몬스터숫자1", "Texture/Damage/1_r.png");
	m_pLoading->LoadTexture("몬스터숫자2", "Texture/Damage/2_r.png");
	m_pLoading->LoadTexture("몬스터숫자3", "Texture/Damage/3_r.png");
	m_pLoading->LoadTexture("몬스터숫자4", "Texture/Damage/4_r.png");
	m_pLoading->LoadTexture("몬스터숫자5", "Texture/Damage/5_r.png");
	m_pLoading->LoadTexture("몬스터숫자6", "Texture/Damage/6_r.png");
	m_pLoading->LoadTexture("몬스터숫자7", "Texture/Damage/7_r.png");
	m_pLoading->LoadTexture("몬스터숫자8", "Texture/Damage/8_r.png");
	m_pLoading->LoadTexture("몬스터숫자9", "Texture/Damage/9_r.png");



	//플레이어 사진
	m_pLoading->LoadTexture("아카날_사진", "Texture/Portrait/Portrait_PC_Aknal_S_Icon.png");
	m_pLoading->LoadTexture("아린_사진", "Texture/Portrait/Portrait_PC_Arin_S_Icon.png");
	m_pLoading->LoadTexture("베카_사진", "Texture/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	m_pLoading->LoadTexture("헤스티아_사진", "Texture/Portrait/Portrait_PC_Hestia_S_Icon.png");
	m_pLoading->LoadTexture("메그너스_사진", "Texture/Portrait/Portrait_Pc_Magnus_Icon.png");
	m_pLoading->LoadTexture("리아_사진", "Texture/Portrait/Portrait_PC_Riah_S_Icon.png");
	m_pLoading->LoadTexture("스카디_사진", "Texture/Portrait/Portrait_PC_Skadi_S_Icon.png");
	m_pLoading->LoadTexture("벨벳_사진", "Texture/Portrait/velvet.png");
	m_pLoading->LoadTexture("파이란_사진", "Texture/Portrait/Portrait_PC_Pyran_S_Icon.png");


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

	
	//쉴드 프로그래스바
	m_pLoading->LoadTexture("실드_프론트바", "Texture/PlayerProgressBar/shieldHp.jpg");
	m_pLoading->LoadTexture("실드_백바", "Texture/PlayerProgressBar/shieldBack.jpg");

	// 메인 UI
	m_pLoading->LoadTexture("Main Background", "Texture/Scene/Main BG.png");
	m_pLoading->LoadTexture("Main Button", "Texture/Scene/Main Button.png");
	m_pLoading->LoadTexture("Main Chr Select", "Texture/Scene/Main Character Select.png");
	m_pLoading->LoadTexture("Character Background", "Texture/Scene/Character BG.png");
	m_pLoading->LoadTexture("Character Chr Over", "Texture/Scene/Main Character Over.png");

	m_pLoading->LoadTexture("White", "Texture/UI/White.png");

	// 게임 UI
	m_pLoading->LoadTexture("Game ElapseTime", "Texture/UI/ElapseTime.png");
	m_pLoading->LoadTexture("캐릭터_스테이터스", "Texture/UI/Character Status.png");
	m_pLoading->LoadTexture("캐릭터_체력", "Texture/UI/Character HP.png");
	m_pLoading->LoadTexture("캐릭터_스테미너", "Texture/UI/Character SM.png");
	m_pLoading->LoadTexture("캐릭터_스킬창", "Texture/UI/Character Skill.png");

	//플레이어 고유스킬아이콘
	m_pLoading->LoadTexture("근접_방패", "Texture/SkillIMG/Skill_Ashu_Passive01_Icon.tga");
	m_pLoading->LoadTexture("근접_무적", "Texture/SkillIMG/Skill_Anika_Active01_Icon.tga");
	m_pLoading->LoadTexture("근접_이동공격", "Texture/SkillIMG/Skill_Arin_Passive01_Icon.tga");

	m_pLoading->LoadTexture("마법_이동", "Texture/SkillIMG/Skill_Bati_Mana01_Icon.tga");
	m_pLoading->LoadTexture("마법_파이어볼", "Texture/SkillIMG/Skill_Deemona_Active01_Icon.tga");
	m_pLoading->LoadTexture("마법_메테오", "Texture/SkillIMG/Skill_RedEye_Active01_Icon.tga");

	m_pLoading->LoadTexture("마법_아이스", "Texture/SkillIMG/Skill_HolyGhost_Active01_Icon.tga");
	m_pLoading->LoadTexture("마법_방패", "Texture/SkillIMG/Skill_Elizabeth_Mana01_Icon.tga");

	m_pLoading->LoadTexture("원거리_공격", "Texture/SkillIMG/Skill_Beholder_Active02_Icon.tga");
	m_pLoading->LoadTexture("원거리_레이저", "Texture/SkillIMG/Skill_Miach_Mana01_Icon.tga");
	m_pLoading->LoadTexture("원거리_이동", "Texture/SkillIMG/Skill_RedHarpy_Mana01_Icon.tga");

	//마법공격 파티클(이후 수정가능성 높음)
	m_pLoading->LoadTexture("마법기본공격", "Texture/Particle/MagicCircle.png");
	m_pLoading->LoadTexture("폭발", "Texture/Particle/Explosion.png");
	m_pLoading->LoadTexture("석유", "Texture/Particle/Robotblood.png");

	//플레이어 고유스킬용
	m_pLoading->LoadTexture("수정", "Texture/Effect/cristal.png"); 
	m_pLoading->LoadTexture("화살", "Texture/Effect/arrow4.png");
	m_pLoading->LoadTexture("파이어볼_마법", "Texture/Effect/Fireball.png");
	m_pLoading->LoadTexture("실드_마법", "Texture/Particle/MagicShield.png");
	m_pLoading->LoadTexture("메테오", "Texture/Particle/Meteor.png");
	m_pLoading->LoadTexture("총알", "Texture/Particle/bullet.png");
	m_pLoading->LoadTexture("조준선", "Texture/Particle/aim.png");

	m_pLoading->LoadTexture("Particle Sphere", "Texture/Particle/Sphere.png");
	m_pLoading->LoadTexture("Option Volume", "Texture/Scene/Volume.png");
	m_pLoading->LoadTexture("Magic Bullet", "Texture/Effect/Magic Bullet.png");

	//메테오 파티클 
	m_pLoading->LoadTexture("MeteorAfter", "Texture/Particle/meteorAfter.png");

	//최종보스 스킬 텍스쳐
	m_pLoading->LoadTexture("돌", "Texture/Effect/stone.png");
	m_pLoading->LoadTexture("흙먼지", "Texture/Particle/Dust.png");
	
	//Npc대화창
	m_pLoading->LoadTexture("대화창", "Texture/UI/NPC Dialogue.png");
	m_pLoading->LoadTexture("리무_초상화", "Texture/Portrait/Rimoo.png");
	m_pLoading->LoadTexture("선택지", "Texture/UI/NPC Button.png");

	//몬스터 피격 텍스쳐
	m_pLoading->LoadTexture("피", "Texture/Particle/Blood.png");

	//파이란 스킬 텍스쳐
	m_pLoading->LoadTexture("파이란_스킬2", "Texture/Effect/pyranSkill2.png");

	//중간보스 피흡 텍스쳐
	m_pLoading->LoadTexture("피흡원", "Texture/Effect/BloodCircle.png");
}

void SC_Loading::AddSound()
{
	m_pLoading->LoadSound("Main Theme", "Sound/01. Premonition.mp3", true);
	m_pLoading->LoadSound("FootStep", "Sound/S_Foot02.ogg", true);
	m_pLoading->LoadSound("FootStep2", "Sound/S_Foot03.ogg", true);
	m_pLoading->LoadSound("FootStep3", "Sound/S_Foot04.ogg", true);
	m_pLoading->LoadSound("FootStep4", "Sound/S_Foot05.ogg", true);
	m_pLoading->LoadSound("SwordAttack", "Sound/Sword1.mp3", false);
	m_pLoading->LoadSound("SwordAttack_TWO", "Sound/Sword_Scrape_2.ogg", false);
	m_pLoading->LoadSound("SwordAttack_THREE", "Sound/chainSaw.mp3", false);
	m_pLoading->LoadSound("BowAttack", "Sound/Bow_3.ogg", false);
	


	//인벤토리 오픈사운드
	m_pLoading->LoadSound("인벤_오픈", "Sound/Inven_open.mp3", false);

	//벨벳 사운드
	m_pLoading->LoadSound("벨벳_공격", "Sound/Velvet/Attack.mp3", false);
	m_pLoading->LoadSound("벨벳_스킬", "Sound/Velvet/Skill.mp3", false);
	m_pLoading->LoadSound("벨벳_피격", "Sound/Velvet/hitted.mp3", false);
	m_pLoading->LoadSound("벨벳_죽음", "Sound/Velvet/die.mp3", false);


	//베카 사운드
	m_pLoading->LoadSound("베카_공격", "Sound/Beakah/Beakah_attack.mp3", false);
	m_pLoading->LoadSound("베카_스킬", "Sound/Beakah/Beakah_skill.mp3", false);
	m_pLoading->LoadSound("베카_피격", "Sound/Beakah/Beakah_hitted.mp3", false);
	m_pLoading->LoadSound("베카_죽음", "Sound/Beakah/Beakah_die.mp3", false);

	//리아 사운드
	m_pLoading->LoadSound("리아_공격", "Sound/Riah/Riah_attack.mp3", false);
	m_pLoading->LoadSound("리아_스킬", "Sound/Riah/Riah_skill.mp3", false);
	m_pLoading->LoadSound("리아_피격", "Sound/Riah/Riah_hitted.mp3", false);
	m_pLoading->LoadSound("리아_죽음", "Sound/Riah/Riah_die.mp3", false);


	//메그너스 사운드
	m_pLoading->LoadSound("메그너스_공격", "Sound/Megnus/Megnus_attack.mp3", false);
	m_pLoading->LoadSound("메그너스_스킬", "Sound/Megnus/Megnus_skill.mp3", false);
	m_pLoading->LoadSound("메그너스_피격", "Sound/Megnus/Megnus_hitted.mp3", false);
	m_pLoading->LoadSound("메그너스_죽음", "Sound/Megnus/Megnus_die.mp3", false);
	m_pLoading->LoadSound("메그너스_고유", "Sound/Megnus/Megnus_inheri.mp3", false);
	m_pLoading->LoadSound("메그너스_고유_총", "Sound/Megnus/Megnus_inheri_gun.mp3", false);
	m_pLoading->LoadSound("GunAttack", "Sound/Rifle_Shot2.ogg", false);
	m_pLoading->LoadSound("탑뷰샷", "Sound/Rifle_Shot4.ogg", false);
	m_pLoading->LoadSound("탑뷰탄피", "Sound/tanpi.mp3", false);

	//스카디 사운드
	m_pLoading->LoadSound("스카디_공격", "Sound/Sakadi/Sakadi_attack.mp3", false);
	m_pLoading->LoadSound("스카디_스킬", "Sound/Sakadi/Sakadi_skill.mp3", false);
	m_pLoading->LoadSound("스카디_피격", "Sound/Sakadi/Sakadi_hitted.mp3", false);
	m_pLoading->LoadSound("스카디_죽음", "Sound/Sakadi/Sakadi_die.mp3", false);
	m_pLoading->LoadSound("스카디_고유", "Sound/Sakadi/Sakadi_inheri.mp3", false);


	//아카날 사운드
	m_pLoading->LoadSound("아카날_공격", "Sound/Aknal/Aknal_attack.mp3", false);
	m_pLoading->LoadSound("아카날_스킬", "Sound/Aknal/Aknal_skill.mp3", false);
	m_pLoading->LoadSound("아카날_피격", "Sound/Aknal/Aknal_hitted.mp3", false);
	m_pLoading->LoadSound("아카날_죽음", "Sound/Aknal/Aknal_die.mp3", false);


	//헤스티아 사운드
	m_pLoading->LoadSound("헤스티아_공격", "Sound/Hestia/Hestia_attack.mp3", false);
	m_pLoading->LoadSound("헤스티아_스킬", "Sound/Hestia/Hestia_skill.mp3", false);
	m_pLoading->LoadSound("헤스티아_피격", "Sound/Hestia/Hestia_hitted.mp3", false);
	m_pLoading->LoadSound("헤스티아_죽음", "Sound/Hestia/Hestia_die.mp3", false);
}

void SC_Loading::AddParticle()
{
	//마법공격 파티클(이후 수정가능성 높음)
	m_pLoading->LoadParticle("마법기본공격", "마법기본공격", "./Particle/MagicBasicAttack.ptc");
	m_pLoading->LoadParticle("마법스킬공격", "마법기본공격", "./Particle/MagicSkill.ptc");
	m_pLoading->LoadParticle("폭발", "폭발", "./Particle/Explosion.ptc");
	m_pLoading->LoadParticle("석유", "석유", "./Particle/AssisHit.ptc");

	m_pLoading->LoadParticle("WindStorm", "Particle Sphere", "Particle/WindStorm.ptc");
	m_pLoading->LoadParticle("Meteor", "Meteor", "Particle/meteor.ptc");
	m_pLoading->LoadParticle("MeteorAfter", "MeteorAfter", "Particle/MeteorAfter.ptc");
	m_pLoading->LoadParticle("MegaCristal", "MegaCristal", "Particle/megaCristal.ptc");

	m_pLoading->LoadParticle("Hell Smoke", "Particle Sphere", "Particle/Hell Smoke.ptc");
	m_pLoading->LoadParticle("Pet Spawn", "Particle Sphere", "Particle/Pet Spawn.ptc");

	m_pLoading->LoadParticle("몬스터기본피격", "피", "Particle/Blood Hit.ptc");
	m_pLoading->LoadParticle("흙먼지", "흙먼지", "Particle/Dust.ptc");
}

void SC_Loading::InitUI()
{
	TEXTUREMANAGER->AddTexture("Loading Background", "Texture/Scene/Loading BG.png");
	TEXTUREMANAGER->AddTexture("Loading Bar", "Texture/Scene/Loading Bar.png");

	SOUND->Play("Main Theme", 0.5);

	m_pUI = new UIObject;
	m_pUI->SetTexture(TEXTUREMANAGER->GetTexture("Loading Background"));
	m_pUI->SetPosition(D3DXVECTOR3(0, 0, 0.1));
	m_pUI->SetName("Background");

	UIObject * child = new UIObject;
	child->SetTexture(TEXTUREMANAGER->GetTexture("Loading Bar"));
	child->SetPosition(D3DXVECTOR3(181, 493, 0));
	child->SetName("Bar");
	m_pUI->AddChild(child);
}

void SC_Loading::Update()
{
	m_pUI->Update();

	if (m_pLoading->LoadingDone())
	{
		SCENE->ChangeScene("Main", true);
	}
}

void SC_Loading::Render()
{
	UIObject * bar = m_pUI->Find("Bar");
	bar->SetScale(D3DXVECTOR3(m_pLoading->GaugePercent(), 1, 1));
	m_pUI->Render();
}
