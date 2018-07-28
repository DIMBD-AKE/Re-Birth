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
	//sprintf_s(test, sizeof(test), "�̱��� �̴����Դϴ�");
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
	//�Ϲ� ����
	m_pLoading->LoadModel("����", "Model/Enemy/Nike/", "Nike.x", MODELTYPE_X);
	m_pLoading->LoadModel("�ʸ���", "Model/Enemy/Nerisa/", "Nerisa.x", MODELTYPE_X);
	m_pLoading->LoadModel("��������", "Model/Enemy/NifilHeim/", "NifilHeim.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ũ��", "Model/Enemy/DarkHell/", "DarkHell.x", MODELTYPE_X);
	m_pLoading->LoadModel("�ƽý�", "Model/Enemy/Assis/", "Assis.x", MODELTYPE_X);
	m_pLoading->LoadModel("�����ں���", "Model/Enemy/Elizabeth/", "Elizabeth.x", MODELTYPE_X);
	//�߰� ����
	m_pLoading->LoadModel("����", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);
	//���� ����
	m_pLoading->LoadModel("��������", "Model/Enemy/FinalBoss/", "LoadWell.x", MODELTYPE_X);
	
	//�÷��̾� 
	m_pLoading->LoadModel("�Ƹ�", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ī��", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	m_pLoading->LoadModel("�콺Ƽ��", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	m_pLoading->LoadModel("�ޱ׳ʽ�", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	m_pLoading->LoadModel("����", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ī��", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ī", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	m_pLoading->LoadModel("����", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	m_pLoading->LoadModel("���̶�", "Model/Character/Pyran/", "Pyran.x", MODELTYPE_X);
	//�ǵ�ĳ����
	m_pLoading->LoadModel("����", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);

	//NPC
	m_pLoading->LoadModel("����", "Model/NPC/Rimoo/", "Rimoo.x", MODELTYPE_X);


	//Pet
	m_pLoading->LoadModel("������", "Model/Pet/Bentley/", "Bentley.x", MODELTYPE_X);
	m_pLoading->LoadModel("�䳢", "Model/Pet/Bunny/", "Bunny.x", MODELTYPE_X);
	m_pLoading->LoadModel("����ȣ", "Model/Pet/Miho/", "Miho.x", MODELTYPE_X);
	m_pLoading->LoadModel("��", "Model/Pet/Miri/", "Miri.x", MODELTYPE_X);
	m_pLoading->LoadModel("�����", "Model/Pet/Nero/", "Nero.x", MODELTYPE_X);
	m_pLoading->LoadModel("��", "Model/Pet/Nir/", "Nir.x", MODELTYPE_X);
	m_pLoading->LoadModel("�Ǵн�", "Model/Pet/Nix/", "Nix.x", MODELTYPE_X);
	m_pLoading->LoadModel("�Ҵ�", "Model/Pet/Panda/", "Panda.x", MODELTYPE_X);
	m_pLoading->LoadModel("����", "Model/Pet/Penny/", "Penny.x", MODELTYPE_X);
}

void SC_Loading::AddTexture()
{
	//m_pLoading->LoadTexture()
	//���� HP��
	m_pLoading->LoadTexture("MonBackBar", "./Model/Enemy/UI/���.jpg");
	m_pLoading->LoadTexture("MonFrontBar", "./Model/Enemy/UI/����Ʈ��.jpg");

	m_pLoading->LoadTexture("BossBackBar", "./Model/Enemy/UI/�������.jpg");
	m_pLoading->LoadTexture("BossFrontBar", "./Model/Enemy/UI/��������Ʈ��.jpg");

	//���� ������ �̹���
	m_pLoading->LoadTexture("���ͼ���0", "Texture/Damage/0_r.png");
	m_pLoading->LoadTexture("���ͼ���1", "Texture/Damage/1_r.png");
	m_pLoading->LoadTexture("���ͼ���2", "Texture/Damage/2_r.png");
	m_pLoading->LoadTexture("���ͼ���3", "Texture/Damage/3_r.png");
	m_pLoading->LoadTexture("���ͼ���4", "Texture/Damage/4_r.png");
	m_pLoading->LoadTexture("���ͼ���5", "Texture/Damage/5_r.png");
	m_pLoading->LoadTexture("���ͼ���6", "Texture/Damage/6_r.png");
	m_pLoading->LoadTexture("���ͼ���7", "Texture/Damage/7_r.png");
	m_pLoading->LoadTexture("���ͼ���8", "Texture/Damage/8_r.png");
	m_pLoading->LoadTexture("���ͼ���9", "Texture/Damage/9_r.png");



	//�÷��̾� ����
	m_pLoading->LoadTexture("��ī��_����", "Texture/Portrait/Portrait_PC_Aknal_S_Icon.png");
	m_pLoading->LoadTexture("�Ƹ�_����", "Texture/Portrait/Portrait_PC_Arin_S_Icon.png");
	m_pLoading->LoadTexture("��ī_����", "Texture/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	m_pLoading->LoadTexture("�콺Ƽ��_����", "Texture/Portrait/Portrait_PC_Hestia_S_Icon.png");
	m_pLoading->LoadTexture("�ޱ׳ʽ�_����", "Texture/Portrait/Portrait_Pc_Magnus_Icon.png");
	m_pLoading->LoadTexture("����_����", "Texture/Portrait/Portrait_PC_Riah_S_Icon.png");
	m_pLoading->LoadTexture("��ī��_����", "Texture/Portrait/Portrait_PC_Skadi_S_Icon.png");
	m_pLoading->LoadTexture("����_����", "Texture/Portrait/velvet.png");
	m_pLoading->LoadTexture("���̶�_����", "Texture/Portrait/Portrait_PC_Pyran_S_Icon.png");


	//�÷��̾� ������ �̹��� 
	m_pLoading->LoadTexture("����0", "Texture/Damage/0.png");
	m_pLoading->LoadTexture("����1", "Texture/Damage/1.png");
	m_pLoading->LoadTexture("����2", "Texture/Damage/2.png");
	m_pLoading->LoadTexture("����3", "Texture/Damage/3.png");
	m_pLoading->LoadTexture("����4", "Texture/Damage/4.png");
	m_pLoading->LoadTexture("����5", "Texture/Damage/5.png");
	m_pLoading->LoadTexture("����6", "Texture/Damage/6.png");
	m_pLoading->LoadTexture("����7", "Texture/Damage/7.png");
	m_pLoading->LoadTexture("����8", "Texture/Damage/8.png");
	m_pLoading->LoadTexture("����9", "Texture/Damage/9.png");

	
	//���� ���α׷�����
	m_pLoading->LoadTexture("�ǵ�_����Ʈ��", "Texture/PlayerProgressBar/shieldHp.jpg");
	m_pLoading->LoadTexture("�ǵ�_���", "Texture/PlayerProgressBar/shieldBack.jpg");

	// ���� UI
	m_pLoading->LoadTexture("Main Background", "Texture/Scene/Main BG.png");
	m_pLoading->LoadTexture("Main Button", "Texture/Scene/Main Button.png");
	m_pLoading->LoadTexture("Main Chr Select", "Texture/Scene/Main Character Select.png");
	m_pLoading->LoadTexture("Character Background", "Texture/Scene/Character BG.png");
	m_pLoading->LoadTexture("Character Chr Over", "Texture/Scene/Main Character Over.png");

	m_pLoading->LoadTexture("White", "Texture/UI/White.png");

	// ���� UI
	m_pLoading->LoadTexture("Game ElapseTime", "Texture/UI/ElapseTime.png");
	m_pLoading->LoadTexture("ĳ����_�������ͽ�", "Texture/UI/Character Status.png");
	m_pLoading->LoadTexture("ĳ����_ü��", "Texture/UI/Character HP.png");
	m_pLoading->LoadTexture("ĳ����_���׹̳�", "Texture/UI/Character SM.png");
	m_pLoading->LoadTexture("ĳ����_��ųâ", "Texture/UI/Character Skill.png");

	//�÷��̾� ������ų������
	m_pLoading->LoadTexture("����_����", "Texture/SkillIMG/Skill_Ashu_Passive01_Icon.tga");
	m_pLoading->LoadTexture("����_����", "Texture/SkillIMG/Skill_Anika_Active01_Icon.tga");
	m_pLoading->LoadTexture("����_�̵�����", "Texture/SkillIMG/Skill_Arin_Passive01_Icon.tga");

	m_pLoading->LoadTexture("����_�̵�", "Texture/SkillIMG/Skill_Bati_Mana01_Icon.tga");
	m_pLoading->LoadTexture("����_���̾", "Texture/SkillIMG/Skill_Deemona_Active01_Icon.tga");
	m_pLoading->LoadTexture("����_���׿�", "Texture/SkillIMG/Skill_RedEye_Active01_Icon.tga");

	m_pLoading->LoadTexture("����_���̽�", "Texture/SkillIMG/Skill_HolyGhost_Active01_Icon.tga");
	m_pLoading->LoadTexture("����_����", "Texture/SkillIMG/Skill_Elizabeth_Mana01_Icon.tga");

	m_pLoading->LoadTexture("���Ÿ�_����", "Texture/SkillIMG/Skill_Beholder_Active02_Icon.tga");
	m_pLoading->LoadTexture("���Ÿ�_������", "Texture/SkillIMG/Skill_Miach_Mana01_Icon.tga");
	m_pLoading->LoadTexture("���Ÿ�_�̵�", "Texture/SkillIMG/Skill_RedHarpy_Mana01_Icon.tga");

	//�������� ��ƼŬ(���� �������ɼ� ����)
	m_pLoading->LoadTexture("�����⺻����", "Texture/Particle/MagicCircle.png");
	m_pLoading->LoadTexture("����", "Texture/Particle/Explosion.png");
	m_pLoading->LoadTexture("����", "Texture/Particle/Robotblood.png");

	//�÷��̾� ������ų��
	m_pLoading->LoadTexture("����", "Texture/Effect/cristal.png"); 
	m_pLoading->LoadTexture("ȭ��", "Texture/Effect/arrow4.png");
	m_pLoading->LoadTexture("���̾_����", "Texture/Effect/Fireball.png");
	m_pLoading->LoadTexture("�ǵ�_����", "Texture/Particle/MagicShield.png");
	m_pLoading->LoadTexture("���׿�", "Texture/Particle/Meteor.png");
	m_pLoading->LoadTexture("�Ѿ�", "Texture/Particle/bullet.png");
	m_pLoading->LoadTexture("���ؼ�", "Texture/Particle/aim.png");

	m_pLoading->LoadTexture("Particle Sphere", "Texture/Particle/Sphere.png");
	m_pLoading->LoadTexture("Option Volume", "Texture/Scene/Volume.png");
	m_pLoading->LoadTexture("Magic Bullet", "Texture/Effect/Magic Bullet.png");

	//���׿� ��ƼŬ 
	m_pLoading->LoadTexture("MeteorAfter", "Texture/Particle/meteorAfter.png");

	//�������� ��ų �ؽ���
	m_pLoading->LoadTexture("��", "Texture/Effect/stone.png");
	m_pLoading->LoadTexture("�����", "Texture/Particle/Dust.png");
	
	//Npc��ȭâ
	m_pLoading->LoadTexture("��ȭâ", "Texture/UI/NPC Dialogue.png");
	m_pLoading->LoadTexture("����_�ʻ�ȭ", "Texture/Portrait/Rimoo.png");
	m_pLoading->LoadTexture("������", "Texture/UI/NPC Button.png");

	//���� �ǰ� �ؽ���
	m_pLoading->LoadTexture("��", "Texture/Particle/Blood.png");

	//���̶� ��ų �ؽ���
	m_pLoading->LoadTexture("���̶�_��ų2", "Texture/Effect/pyranSkill2.png");

	//�߰����� ���� �ؽ���
	m_pLoading->LoadTexture("�����", "Texture/Effect/BloodCircle.png");
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
	


	//�κ��丮 ���»���
	m_pLoading->LoadSound("�κ�_����", "Sound/Inven_open.mp3", false);

	//���� ����
	m_pLoading->LoadSound("����_����", "Sound/Velvet/Attack.mp3", false);
	m_pLoading->LoadSound("����_��ų", "Sound/Velvet/Skill.mp3", false);
	m_pLoading->LoadSound("����_�ǰ�", "Sound/Velvet/hitted.mp3", false);
	m_pLoading->LoadSound("����_����", "Sound/Velvet/die.mp3", false);


	//��ī ����
	m_pLoading->LoadSound("��ī_����", "Sound/Beakah/Beakah_attack.mp3", false);
	m_pLoading->LoadSound("��ī_��ų", "Sound/Beakah/Beakah_skill.mp3", false);
	m_pLoading->LoadSound("��ī_�ǰ�", "Sound/Beakah/Beakah_hitted.mp3", false);
	m_pLoading->LoadSound("��ī_����", "Sound/Beakah/Beakah_die.mp3", false);

	//���� ����
	m_pLoading->LoadSound("����_����", "Sound/Riah/Riah_attack.mp3", false);
	m_pLoading->LoadSound("����_��ų", "Sound/Riah/Riah_skill.mp3", false);
	m_pLoading->LoadSound("����_�ǰ�", "Sound/Riah/Riah_hitted.mp3", false);
	m_pLoading->LoadSound("����_����", "Sound/Riah/Riah_die.mp3", false);


	//�ޱ׳ʽ� ����
	m_pLoading->LoadSound("�ޱ׳ʽ�_����", "Sound/Megnus/Megnus_attack.mp3", false);
	m_pLoading->LoadSound("�ޱ׳ʽ�_��ų", "Sound/Megnus/Megnus_skill.mp3", false);
	m_pLoading->LoadSound("�ޱ׳ʽ�_�ǰ�", "Sound/Megnus/Megnus_hitted.mp3", false);
	m_pLoading->LoadSound("�ޱ׳ʽ�_����", "Sound/Megnus/Megnus_die.mp3", false);
	m_pLoading->LoadSound("�ޱ׳ʽ�_����", "Sound/Megnus/Megnus_inheri.mp3", false);
	m_pLoading->LoadSound("�ޱ׳ʽ�_����_��", "Sound/Megnus/Megnus_inheri_gun.mp3", false);
	m_pLoading->LoadSound("GunAttack", "Sound/Rifle_Shot2.ogg", false);
	m_pLoading->LoadSound("ž�伦", "Sound/Rifle_Shot4.ogg", false);
	m_pLoading->LoadSound("ž��ź��", "Sound/tanpi.mp3", false);

	//��ī�� ����
	m_pLoading->LoadSound("��ī��_����", "Sound/Sakadi/Sakadi_attack.mp3", false);
	m_pLoading->LoadSound("��ī��_��ų", "Sound/Sakadi/Sakadi_skill.mp3", false);
	m_pLoading->LoadSound("��ī��_�ǰ�", "Sound/Sakadi/Sakadi_hitted.mp3", false);
	m_pLoading->LoadSound("��ī��_����", "Sound/Sakadi/Sakadi_die.mp3", false);
	m_pLoading->LoadSound("��ī��_����", "Sound/Sakadi/Sakadi_inheri.mp3", false);


	//��ī�� ����
	m_pLoading->LoadSound("��ī��_����", "Sound/Aknal/Aknal_attack.mp3", false);
	m_pLoading->LoadSound("��ī��_��ų", "Sound/Aknal/Aknal_skill.mp3", false);
	m_pLoading->LoadSound("��ī��_�ǰ�", "Sound/Aknal/Aknal_hitted.mp3", false);
	m_pLoading->LoadSound("��ī��_����", "Sound/Aknal/Aknal_die.mp3", false);


	//�콺Ƽ�� ����
	m_pLoading->LoadSound("�콺Ƽ��_����", "Sound/Hestia/Hestia_attack.mp3", false);
	m_pLoading->LoadSound("�콺Ƽ��_��ų", "Sound/Hestia/Hestia_skill.mp3", false);
	m_pLoading->LoadSound("�콺Ƽ��_�ǰ�", "Sound/Hestia/Hestia_hitted.mp3", false);
	m_pLoading->LoadSound("�콺Ƽ��_����", "Sound/Hestia/Hestia_die.mp3", false);
}

void SC_Loading::AddParticle()
{
	//�������� ��ƼŬ(���� �������ɼ� ����)
	m_pLoading->LoadParticle("�����⺻����", "�����⺻����", "./Particle/MagicBasicAttack.ptc");
	m_pLoading->LoadParticle("������ų����", "�����⺻����", "./Particle/MagicSkill.ptc");
	m_pLoading->LoadParticle("����", "����", "./Particle/Explosion.ptc");
	m_pLoading->LoadParticle("����", "����", "./Particle/AssisHit.ptc");

	m_pLoading->LoadParticle("WindStorm", "Particle Sphere", "Particle/WindStorm.ptc");
	m_pLoading->LoadParticle("Meteor", "Meteor", "Particle/meteor.ptc");
	m_pLoading->LoadParticle("MeteorAfter", "MeteorAfter", "Particle/MeteorAfter.ptc");
	m_pLoading->LoadParticle("MegaCristal", "MegaCristal", "Particle/megaCristal.ptc");

	m_pLoading->LoadParticle("Hell Smoke", "Particle Sphere", "Particle/Hell Smoke.ptc");
	m_pLoading->LoadParticle("Pet Spawn", "Particle Sphere", "Particle/Pet Spawn.ptc");

	m_pLoading->LoadParticle("���ͱ⺻�ǰ�", "��", "Particle/Blood Hit.ptc");
	m_pLoading->LoadParticle("�����", "�����", "Particle/Dust.ptc");
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
