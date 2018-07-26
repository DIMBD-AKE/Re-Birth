#include "../../stdafx.h"
#include "Npc.h"
#include "../Map.h"
#include "CharacterParant.h"



Npc::Npc()
{
	m_bIsAppear = false;
}


Npc::~Npc()
{
	SAFE_DELETE(m_pNpc);
}

void Npc::Init(D3DXVECTOR3 pos)
{

	m_pNpc = MODELMANAGER->GetModel("리무", MODELTYPE_X);
	m_pNpc->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	m_pNpc->SetRotation(D3DXVECTOR3(0, 3.2, 0));
	m_pNpc->SetPosition(pos);
	

	m_bIsCollision = false;
	m_bIsAppear = true;
	m_bTalk = false;

	ST_SIZEBOX box;
	box.highX = 30.0f;
	box.highY = 180.0f;
	box.highZ = 30.0f;
	box.lowX = -30.0f;
	box.lowY = 10.0f;
	box.lowZ = -30.0f;

	m_pNpc->CreateBound(box);
	m_pNpc->SetBoundSphere(m_pNpc->GetOrigBoundSphere().center, 100.0f);

	m_pContext = new Dialogue;

	if(m_pPortrait == NULL)m_pPortrait = new UIObject;
	m_pPortrait->SetTexture(TEXTUREMANAGER->GetTexture("리무_초상화"));
	m_pPortrait->SetPosition(D3DXVECTOR3(-50, 15, 0.1));
	m_pPortrait->SetScale(D3DXVECTOR3(1.5, 1.5, 1.5));


	//다이얼로그			위치				사이즈  폰트       속도    색깔
	m_pContext->Init(D3DXVECTOR2(550, 650), 40, "UhBee Yiseul", 0.05, 0xFF000000);
	//m_pPlayer = new CharacterParant;

	m_pContext->AddText("흐..흥!\n딱히 만나고 싶어서 나온건 아니니까!");
	m_pContext->AddText("따..딱히 너를 위해\n스킬을 해금해주는건 아니니까!");
	m_pContext->AddText("V키를 누르면\n 아오시발 못치겠다");
	m_pContext->AddText("오글오글\n화이팅!");
	m_pContext->SetKey(VK_RBUTTON, 'X', 'C');
}

void Npc::Update()
{
	if (m_pNpc && m_bIsAppear)
	{
		m_pNpc->World();
		CheckCollision();
		m_pPortrait->Update();
		SkillUnSeal();
		if (m_bIsCollision)
		{
			m_pContext->Update();
			CameraViewChange();
		}

		if(m_bIsCollision)TEXT->Add("리무", 150, 595, 30);
		if (m_pContext->GetIndex() == 3)
		{
			if (INPUT->KeyDown(VK_LBUTTON))
			{
				m_bIsCollision = false;
			}
		}
	}
}

void Npc::Render()
{
	if (m_pNpc && m_bIsAppear)m_pNpc->Render();
	if (m_bIsCollision)m_pPortrait->Render();
}

void Npc::CheckCollision()
{
	if (IntersectSphere(m_pNpc->GetBoundSphere(), m_pPlayer->GetCharacter()->GetBoundSphere()))
	{
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			m_bIsCollision = true;
			m_bTalk = true;
			Talk();
		}
	}
	else
	{
		m_bIsCollision = false;
	}
}

void Npc::Talk()
{
	if (m_bTalk) m_pContext->SetIndex(m_pContext->GetIndex());
}


void Npc::SkillUnSeal()
{
	if (m_bTalk) m_pPlayer->SetSkillUnSealed(true);
}

void Npc::PlusAttack()
{
}

void Npc::CameraViewChange()
{
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 2.2, 15));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 2, 0));
}


void Npc::Debug()
{
}
