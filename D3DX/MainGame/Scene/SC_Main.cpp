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
	SCENE->ChangeScene("Test");
}

void SC_Main::Release()
{
	SAFE_RELEASE(m_pUI);
}

void SC_Main::Init()
{
	m_pUI = new UIObject;
	m_pUI->SetPosition(D3DXVECTOR3(0, 0, 1));
	m_pUI->SetTexture(TEXTUREMANAGER->AddTexture("Main Background", "Texture/Main/Background.png"));
	m_pUI->SetName("Background");
	
	UIObject * child = new UIObject;
	child->SetPosition(D3DXVECTOR3(580, 351, 0));
	child->SetTexture(TEXTUREMANAGER->AddTexture("Main Button", "Texture/Main/Button.png"));
	child->SetName("Start");
	child->SetFunction(this);
	m_pUI->AddChild(child);
}

void SC_Main::Update()
{
	m_pUI->Update();

	TEXT->Add("½ÃÀÛ", 580, 351, 24, "", 0xFFFFFFFF);
}

void SC_Main::Render()
{
	m_pUI->Render();
}
