#include "../../stdafx.h"
#include "SC_Main.h"
#include "../Character/CharacterParant.h"
#include "../Character/Character_Gun.h"
#include "../Character/Character_Magic.h"
#include "../Character/Character_Sword.h"


SC_Main::SC_Main()
{
}


SC_Main::~SC_Main()
{
}

void SC_Main::OnClick(UIObject * pSender)
{
	if (pSender->GetName().compare("Character Select") == 0)
		m_eState = MS_PORTRAIT;

	if (pSender->GetName().compare("Start") == 0 && m_sSelect.compare("�Ƹ�"))
	{
		/*SCENE->ChangeScene("Test", true);
		return;*/

		SOUND->Stop("Main Theme");
		SCENE->ChangeScene("Game", false);
		CharacterParant * character = NULL;
		if (m_sSelect.compare("��ī��") == 0)
		{
			character = new Character_Magic;
			character->Init(CHRTYPE_MAGIC, CHAR_ONE);
		}
		if (m_sSelect.compare("�콺Ƽ��") == 0)
		{
			character = new Character_Magic;
			character->Init(CHRTYPE_MAGIC, CHAR_TWO);
		}
		if (m_sSelect.compare("��ī") == 0)
		{
			character = new Character_Sword;
			character->Init(CHRTYPE_SWORD, CHAR_ONE);
		}
		if (m_sSelect.compare("����") == 0)
		{
			character = new Character_Sword;
			character->Init(CHRTYPE_SWORD, CHAR_TWO);
		}
		if (m_sSelect.compare("����") == 0)
		{
			character = new Character_Sword;
			character->Init(CHRTYPE_SWORD, CHAR_THREE);
		}
		if (m_sSelect.compare("�ޱ׳ʽ�") == 0)
		{
			character = new Character_Gun;
			character->Init(CHRTYPE_GUN, CHAR_ONE);
		}
		if (m_sSelect.compare("��ī��") == 0)
		{
			character = new Character_Gun;
			character->Init(CHRTYPE_GUN, CHAR_TWO);
		}
		SCENE->GetCurrentScene()->SetData(0, character);
		int stage = 1;
		SCENE->GetCurrentScene()->SetData(1, &stage);
		SCENE->GetCurrentScene()->Init();
	}

	if (pSender->GetName().compare("Character Select") && 
		pSender->GetName().compare("Background") &&
		pSender->GetName().compare("Start"))
	{
		m_sSelect = pSender->GetName();
		MakeModel();
	}
}

void SC_Main::OnOver(UIObject * pSender)
{
	if (pSender->GetName().compare("Character Select") &&
		pSender->GetName().compare("Background") && 
		pSender->GetName().compare("Start"))
	{
		m_pChrOver->SetPosition(pSender->GetPosition() - D3DXVECTOR3(6, 6, 0));
		m_pChrOver->SetScale(pSender->GetScale());
		m_pSelect->SetScale(pSender->GetScale());
		m_isPortrait = true;
	}
}

void SC_Main::OnExit(UIObject * pSender)
{
	if (pSender->GetName().compare("Character Select") && 
		pSender->GetName().compare("Background") &&
		pSender->GetName().compare("Start"))
		m_isPortrait = false;
}

void SC_Main::Release()
{
	SAFE_RELEASE(m_pUI);
	SAFE_RELEASE(m_pPortrait);
	SAFE_RELEASE(m_pSelect);
	SAFE_RELEASE(m_pChrOver);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pContext);
}

void SC_Main::Init()
{
	SOUND->Play("Main Theme", 0.2);

	m_eState = MS_TITLE;
	m_isPortrait = false;
	m_sSelect = "";
	m_pModel = NULL;

	m_pUI = new UIObject;
	m_pUI->SetPosition(D3DXVECTOR3(0, 0, 1));
	m_pUI->SetTexture(TEXTUREMANAGER->AddTexture("Main Background", "Texture/Scene/Main BG.png"));
	m_pUI->SetName("Background");
	
	UIObject * child = new UIObject;
	child->SetPosition(D3DXVECTOR3(580, 351, 0));
	child->SetTexture(TEXTUREMANAGER->AddTexture("Main Button", "Texture/Scene/Main Button.png"));
	child->SetName("Character Select");
	child->SetFunction(this);
	m_pUI->AddChild(child);

	m_pStart = new UIObject;
	m_pStart->SetPosition(D3DXVECTOR3(630, 650, 0));
	m_pStart->SetTexture(TEXTUREMANAGER->GetTexture("Main Button"));
	m_pStart->SetScale(D3DXVECTOR3(0.8, 0.8, 1));
	m_pStart->SetName("Start");
	m_pStart->SetFunction(this);

	m_pSelect = new UIObject;
	m_pSelect->SetName("Select");
	m_pSelect->SetTexture(TEXTUREMANAGER->AddTexture("Main Chr Select", "Texture/Scene/Main Character Select.png"));

	m_pPortrait = new UIObject;
	m_pPortrait->SetName("Root");
	m_pPortrait->SetTexture(TEXTUREMANAGER->AddTexture("Character Background", "Texture/Scene/Character BG.png"));

	m_pChrOver = new UIObject;
	m_pChrOver->SetName("Over");
	m_pChrOver->SetTexture(TEXTUREMANAGER->AddTexture("Character Chr Over", "Texture/Scene/Main Character Over.png"));

	child = new UIObject;
	child->SetFunction(this);
	m_pPortrait->AddChild(child);

	m_pContext = new Dialogue;
	m_pContext->Init(D3DXVECTOR2(550, 280), 30, "��������", 0.05, 0xFFFFFFFF);
	
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			int index = y * 2 + x;
			D3DXVECTOR3 pos = D3DXVECTOR3(70, 140, 0);
			pos.x += x * 150;
			pos.y += y * 150;

			child = new UIObject;
			child->SetPosition(pos);
			child->SetFunction(this);
			child->SetScale(D3DXVECTOR3(0.5, 0.5, 1));

			if (index == 0)
			{
				child->SetName("��ī��");
				child->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
				m_pContext->AddText("��ī�� - ������\n\n�Ϸ��� ���ڰ����� ���� ���ڴ�.");
			}
			if (index == 1)
			{
				child->SetName("�Ƹ�");
				child->SetTexture(TEXTUREMANAGER->GetTexture("�Ƹ�_����"));
				m_pContext->AddText("�Ƹ� - �˻�\n\n�ʹݿ� ����������\n�ִϸ��̼��� ��ġ�̵����ؼ�\n�̹� �������� �ʴ� ĳ���ʹ�...");
			}
			if (index == 2)
			{
				child->SetName("��ī");
				child->SetTexture(TEXTUREMANAGER->GetTexture("��ī_����"));
				m_pContext->AddText("��ī - �˻�\n\nũ��...\n�Ϳ� ���Ѵ�.");
			}
			if (index == 3)
			{
				child->SetName("�콺Ƽ��");
				child->SetTexture(TEXTUREMANAGER->GetTexture("�콺Ƽ��_����"));
				m_pContext->AddText("�콺Ƽ�� - ������\n\n���ڸ� �����ִ�");
			}
			if (index == 4)
			{
				child->SetName("�ޱ׳ʽ�");
				child->SetTexture(TEXTUREMANAGER->GetTexture("�ޱ׳ʽ�_����"));
				m_pContext->AddText("�ޱ׳ʽ� - ��\n\n��ĳ �� ��ü��\n���� �ȵ����� ��Ÿ�� ��������\n�Ѿ���� ����.");
			}
			if (index == 5)
			{
				child->SetName("����");
				child->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
				m_pContext->AddText("���� - �˻�\n\n�Ȱ��� �����ִ�.\n�׽�Ʈ������ �� ���̴°� ����.");
			}
			if (index == 6)
			{
				child->SetName("��ī��");
				child->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
				m_pContext->AddText("��ī�� - �ü�\n\nũ��...\n�ڸ����� ���� ������ ��������.");
			}
			if (index == 7)
			{
				child->SetName("����");
				child->SetTexture(TEXTUREMANAGER->GetTexture("����_����"));
				m_pContext->AddText("���� - ����\n\n���� �𸣰� ������ ��� ĳ���ʹ�.\n�׳� �׷��ٴ°��̴�.");
			}
			
			m_pPortrait->AddChild(child);
		}
	}
}

void SC_Main::Update()
{
	m_pUI->Update();

	if (m_eState == MS_PORTRAIT)
		m_pPortrait->Update();

	if (m_eState == MS_PORTRAIT && m_sSelect.size() > 0)
	{
		m_pSelect->SetPosition(m_pPortrait->Find(m_sSelect)->GetPosition());
		m_pSelect->Update();
		m_pContext->Update();
		m_pStart->Update();
		TEXT->Add("���ӽ���", 720, 675, 30, "��������", 0xFFFFFFFF);
	}

	m_pChrOver->Update();

	if (m_eState == MS_TITLE)
	{
		D3DXVECTOR2 mouse = D3DXVECTOR2(MOUSE_POS.x, MOUSE_POS.y);
		m_fElapse += 0.05;
		int alpha = sin(m_fElapse) * 30 + 220;
		m_pUI->Find("Character Select")->SetAlpha(alpha);
		TEXT->Add("����", 724, 382, 40, "��������", D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}

	if (INPUT->KeyDown(VK_BACK))
		m_eState = MS_TITLE;

	if (m_pModel)
	{
		if (INPUT->KeyPress('A')) m_pModel->GetRotation()->y -= 0.1;
		if (INPUT->KeyPress('D')) m_pModel->GetRotation()->y += 0.1;
		m_pModel->World();
	}
}

void SC_Main::Render()
{
	if (m_eState == MS_TITLE)
		m_pUI->Render();

	if (m_eState == MS_PORTRAIT)
	{
		m_pPortrait->Render();

		if (m_sSelect.size() > 0)
			m_pSelect->Render();

		if (m_isPortrait)
			m_pChrOver->Render();

		m_pStart->Render();

		if (m_pModel)
		{
			if (m_pModel->IsAnimationEnd())
				m_pModel->SetAnimation("IDLE");
			m_pModel->Render();
		}
	}
}

void SC_Main::MakeModel()
{
	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetTarget(&m_vPos, &m_vPos);
	CAMERA->SetTargetOffset(D3DXVECTOR3(-5, 3, 0));

	SAFE_DELETE(m_pModel);
	m_pModel = MODELMANAGER->GetModel(m_sSelect, MODELTYPE_X);
	m_pModel->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_pModel->SetAnimation("BattleReady");
	m_pModel->SetScale(D3DXVECTOR3(0.025, 0.025, 0.025));
	m_pContext->SetIndex(GetIndex());
}

int SC_Main::GetIndex()
{
	if (m_sSelect.compare("��ī��") == 0) return 0;
	if (m_sSelect.compare("�Ƹ�") == 0) return 1;
	if (m_sSelect.compare("��ī") == 0) return 2;
	if (m_sSelect.compare("�콺Ƽ��") == 0) return 3;
	if (m_sSelect.compare("�ޱ׳ʽ�") == 0) return 4;
	if (m_sSelect.compare("����") == 0) return 5;
	if (m_sSelect.compare("��ī��") == 0) return 6;
	if (m_sSelect.compare("����") == 0) return 7;
	return -1;
}
