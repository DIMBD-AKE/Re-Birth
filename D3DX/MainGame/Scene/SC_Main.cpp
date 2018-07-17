#include "../../stdafx.h"
#include "SC_Main.h"



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

	if (pSender->GetName().compare("Start") == 0)
	{
		SCENE->ChangeScene("Test", true);
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
	m_pContext->Init(D3DXVECTOR2(550, 300), 30, "나눔명조", 0.1, 0xFFFFFFFF);
	
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
				child->SetName("아카날");
				child->SetTexture(TEXTUREMANAGER->GetTexture("아카날_사진"));
				m_pContext->AddText("아카날 - 마법사\n남자인지 여자인지 모르겠다.");
			}
			if (index == 1)
			{
				child->SetName("아린");
				child->SetTexture(TEXTUREMANAGER->GetTexture("아린_사진"));
				m_pContext->AddText("아린 - 검사\n이미 존재하지 않는 캐릭터다...");
			}
			if (index == 2)
			{
				child->SetName("베카");
				child->SetTexture(TEXTUREMANAGER->GetTexture("베카_사진"));
				m_pContext->AddText("베카 - 검사\n크으...\n뽕에 취한다.");
			}
			if (index == 3)
			{
				child->SetName("헤스티아");
				child->SetTexture(TEXTUREMANAGER->GetTexture("헤스티아_사진"));
				m_pContext->AddText("헤스티아 - 마법사\n설명이 없다");
			}
			if (index == 4)
			{
				child->SetName("메그너스");
				child->SetTexture(TEXTUREMANAGER->GetTexture("메그너스_사진"));
				m_pContext->AddText("메그너스 - 총\n유일한 남캐다.\n맘에 안들지만 넘어가도록 하자.");
			}
			if (index == 5)
			{
				child->SetName("리아");
				child->SetTexture(TEXTUREMANAGER->GetTexture("리아_사진"));
				m_pContext->AddText("리아 - 검사\n안경을 쓰고있다.");
			}
			if (index == 6)
			{
				child->SetName("스카디");
				child->SetTexture(TEXTUREMANAGER->GetTexture("스카디_사진"));
				m_pContext->AddText("스카디 - 궁수\n활이 멋지다.");
			}
			if (index == 7)
			{
				child->SetName("벨벳");
				child->SetTexture(TEXTUREMANAGER->GetTexture("벨벳_사진"));
				m_pContext->AddText("벨벳 - 근접\n뚝배기가 사라질것같다.\n뭔가 마음에 든다.");
			}
			
			m_pPortrait->AddChild(child);
		}
	}
}

void SC_Main::Update()
{
	m_pUI->Update();
	m_pPortrait->Update();

	if (m_eState == MS_PORTRAIT && m_sSelect.size() > 0)
	{
		m_pSelect->SetPosition(m_pPortrait->Find(m_sSelect)->GetPosition());
		m_pSelect->Update();
		m_pContext->Update();
		m_pStart->Update();
		TEXT->Add("게임시작", 720, 675, 30, "나눔명조", 0xFFFFFFFF);
	}

	m_pChrOver->Update();

	if (m_eState == MS_TITLE)
	{
		D3DXVECTOR2 mouse = D3DXVECTOR2(MOUSE_POS.x, MOUSE_POS.y);
		m_fElapse += 0.05;
		int alpha = sin(m_fElapse) * 30 + 220;
		m_pUI->Find("Character Select")->SetAlpha(alpha);
		TEXT->Add("시작", 724, 382, 40, "나눔명조", D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}

	if (m_pModel)
		m_pModel->World();
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
	if (m_sSelect.compare("아카날") == 0) return 0;
	if (m_sSelect.compare("아린") == 0) return 1;
	if (m_sSelect.compare("베카") == 0) return 2;
	if (m_sSelect.compare("헤스티아") == 0) return 3;
	if (m_sSelect.compare("메그너스") == 0) return 4;
	if (m_sSelect.compare("리아") == 0) return 5;
	if (m_sSelect.compare("스카디") == 0) return 6;
	if (m_sSelect.compare("벨벳") == 0) return 7;
	return -1;
}
