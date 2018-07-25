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

	//다이얼로그			위치				사이즈  폰트       속도    색깔
	m_pContext->Init(D3DXVECTOR2(550, 700), 30, "나눔명조", 0.05, 0xFF000000);
	//m_pPlayer = new CharacterParant;

	m_pContext->AddText("안녕하세요?\nNPC에요!");
	m_pContext->AddText("저를 만나셨으니\n스킬을 해금해드릴게요!");
	m_pContext->AddText("V키를 누르면\n 더욱 강력한 스킬을 사용할수 있어요!");
	m_pContext->AddText("포악한 보스를 잡아주세요!\n화이팅!");
	
	m_pContext->SetKey(VK_RBUTTON, 'X', 'C');
}

void Npc::Update()
{
	if (m_pNpc && m_bIsAppear)
	{
		m_pNpc->World();
		CheckCollision();
	
		SkillUnSeal();
		if (m_bIsCollision)
		{
			m_pContext->Update();
			CameraViewChange();
		}


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
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 3.7, 13));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 2, 0));
}


void Npc::Debug()
{
}
