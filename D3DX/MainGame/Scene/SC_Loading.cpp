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
	//�߰�����
	m_pLoading->LoadModel("���׷�", "Model/Enemy/Lagro/", "Lagro.x", MODELTYPE_X);
	//��������
	m_pLoading->LoadModel("����", "Model/Enemy/Boss/", "BOSS.x", MODELTYPE_X);

	
	//�÷��̾� 
	m_pLoading->LoadModel("�Ƹ�", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ī��", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	m_pLoading->LoadModel("�콺Ƽ��", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	m_pLoading->LoadModel("�ޱ׳ʽ�", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	m_pLoading->LoadModel("����", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ī��", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	m_pLoading->LoadModel("��ī", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	m_pLoading->LoadModel("����", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	//�ǵ�ĳ����
	m_pLoading->LoadModel("����", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);
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

	

	//�÷��̾� ���α׷�����
	m_pLoading->LoadTexture("�÷��̾�_����Ʈ��", "Texture/PlayerProgressBar/frontBar.jpg");
	m_pLoading->LoadTexture("�÷��̾�_���", "Texture/PlayerProgressBar/backBar.jpg");

	m_pLoading->LoadTexture("���׹̳�_����Ʈ��", "Texture/PlayerProgressBar/staminaFrontBar.jpg");
	m_pLoading->LoadTexture("���׹̳�_���", "Texture/PlayerProgressBar/staminaBackBar.jpg");

	//���� ���α׷�����
	m_pLoading->LoadTexture("�ǵ�_����Ʈ��", "Texture/PlayerProgressBar/shieldHp.jpg");
	m_pLoading->LoadTexture("�ǵ�_���", "Texture/PlayerProgressBar/shieldBack.jpg");

	// ���� UI
	m_pLoading->LoadTexture("Main Background", "Texture/Scene/Main BG.png");
	m_pLoading->LoadTexture("Main Button", "Texture/Scene/Main Button.png");
	m_pLoading->LoadTexture("Main Chr Select", "Texture/Scene/Main Character Select.png");
	m_pLoading->LoadTexture("Character Background", "Texture/Scene/Character BG.png");
	m_pLoading->LoadTexture("Character Chr Over", "Texture/Scene/Main Character Over.png");

	// ���� UI
	m_pLoading->LoadTexture("Game ElapseTime", "Texture/UI/ElapseTime.png");
	m_pLoading->LoadTexture("ĳ����_�������ͽ�", "Texture/UI/Character Status.png");
	m_pLoading->LoadTexture("ĳ����_ü��", "Texture/UI/Character HP.png");
	m_pLoading->LoadTexture("ĳ����_���׹̳�", "Texture/UI/Character SM.png");

	//�÷��̾� ������ų
	m_pLoading->LoadTexture("����_����", "Texture/SkillIMG/Skill_Ashu_Passive01_Icon.tga");
	m_pLoading->LoadTexture("����_�̵�", "Texture/SkillIMG/Skill_Bati_Mana01_Icon.tga");
	m_pLoading->LoadTexture("���Ÿ�_����", "Texture/SkillIMG/Skill_Beholder_Active02_Icon.tga");
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
	m_pLoading->LoadSound("GunAttack", "Sound/Rifle_Shot2.ogg", false);

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
