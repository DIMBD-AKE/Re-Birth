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

	
	//�÷��̾� 
	MODELMANAGER->AddModel("�Ƹ�", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī��", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�콺Ƽ��", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�ޱ׳ʽ�", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("����", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī��", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("����", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	//�ǵ�ĳ����
	MODELMANAGER->AddModel("����", "Model/Character/Lemnon/", "Lemnon.x", MODELTYPE_X);
}

void LoadingSC::AddTexture()
{
	TEXTUREMANAGER->AddTexture("MonBackBar", "./Model/Enemy/UI/���.jpg");
	TEXTUREMANAGER->AddTexture("MonFrontBar", "./Model/Enemy/UI/����Ʈ��.jpg");

	TEXTUREMANAGER->AddTexture("BossBackBar", "./Model/Enemy/UI/�������.jpg");
	TEXTUREMANAGER->AddTexture("BossFrontBar", "./Model/Enemy/UI/��������Ʈ��.jpg");




	//�÷��̾� ����
	TEXTUREMANAGER->AddTexture("��ī��_����", "Texture/Portrait/Portrait_PC_Aknal_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�Ƹ�_����", "Texture/Portrait/Portrait_PC_Arin_S_Icon.png");
	TEXTUREMANAGER->AddTexture("��ī_����", "Texture/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�콺Ƽ��_����", "Texture/Portrait/Portrait_PC_Hestia_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�ޱ׳ʽ�_����", "Texture/Portrait/Portrait_Pc_Magnus_Icon.png");
	TEXTUREMANAGER->AddTexture("����_����", "Texture/Portrait/Portrait_PC_Riah_S_Icon.png");
	TEXTUREMANAGER->AddTexture("��ī��_����", "Texture/Portrait/Portrait_PC_Skadi_S_Icon.png");
	TEXTUREMANAGER->AddTexture("����_����", "Texture/Portrait/velvet.png");

	//�÷��̾� ������ �̹��� 
	TEXTUREMANAGER->AddTexture("����0", "Texture/Damage/0.png");
	TEXTUREMANAGER->AddTexture("����1", "Texture/Damage/1.png");
	TEXTUREMANAGER->AddTexture("����2", "Texture/Damage/2.png");
	TEXTUREMANAGER->AddTexture("����3", "Texture/Damage/3.png");
	TEXTUREMANAGER->AddTexture("����4", "Texture/Damage/4.png");
	TEXTUREMANAGER->AddTexture("����5", "Texture/Damage/5.png");
	TEXTUREMANAGER->AddTexture("����6", "Texture/Damage/6.png");
	TEXTUREMANAGER->AddTexture("����7", "Texture/Damage/7.png");
	TEXTUREMANAGER->AddTexture("����8", "Texture/Damage/8.png");
	TEXTUREMANAGER->AddTexture("����9", "Texture/Damage/9.png");

	TEXTUREMANAGER->AddTexture("����0_r", "Texture/Damage/0_r.png");
	TEXTUREMANAGER->AddTexture("����1_r", "Texture/Damage/1_r.png");
	TEXTUREMANAGER->AddTexture("����2_r", "Texture/Damage/2_r.png");
	TEXTUREMANAGER->AddTexture("����3_r", "Texture/Damage/3_r.png");
	TEXTUREMANAGER->AddTexture("����4_r", "Texture/Damage/4_r.png");
	TEXTUREMANAGER->AddTexture("����5_r", "Texture/Damage/5_r.png");
	TEXTUREMANAGER->AddTexture("����6_r", "Texture/Damage/6_r.png");
	TEXTUREMANAGER->AddTexture("����7_r", "Texture/Damage/7_r.png");
	TEXTUREMANAGER->AddTexture("����8_r", "Texture/Damage/8_r.png");
	TEXTUREMANAGER->AddTexture("����9_r", "Texture/Damage/9_r.png");

	//�÷��̾� ���α׷�����
	TEXTUREMANAGER->AddTexture("�÷��̾�_����Ʈ��", "Texture/PlayerProgressBar/frontBar.jpg");
	TEXTUREMANAGER->AddTexture("�÷��̾�_���", "Texture/PlayerProgressBar/backBar.jpg");

	TEXTUREMANAGER->AddTexture("���׹̳�_����Ʈ��", "Texture/PlayerProgressBar/staminaFrontBar.jpg");
	TEXTUREMANAGER->AddTexture("���׹̳�_���", "Texture/PlayerProgressBar/staminaBackBar.jpg");

	//���� ���α׷�����
	TEXTUREMANAGER->AddTexture("�ǵ�_����Ʈ��", "Texture/PlayerProgressBar/shieldHp.jpg");
	TEXTUREMANAGER->AddTexture("�ǵ�_���", "Texture/PlayerProgressBar/shieldBack.jpg");

	//�ε� �̹���
	TEXTUREMANAGER->AddTexture("�ε��̹���", "Texture/Loading/Load1.png");

}

void LoadingSC::Update()
{
	LoadingImg->SetTexture(TEXTUREMANAGER->GetTexture("�ε��̹���"));
	LoadingImg->Update();
}

void LoadingSC::Render()
{
	LoadingImg->Render();

}
