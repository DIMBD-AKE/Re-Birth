#include "../../stdafx.h"
#include "Npc.h"
#include "../Map.h"
#include "CharacterParant.h"



Npc::Npc()
{
}


Npc::~Npc()
{
	SAFE_DELETE(m_pNpc);
}

void Npc::Init(D3DXVECTOR3 pos, Map* map)
{

	m_pNpc = MODELMANAGER->GetModel("리무", MODELTYPE_X);
	m_pNpc->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	m_pNpc->SetRotation(D3DXVECTOR3(0, 3.2, 0));
	m_pNpc->SetPosition(pos);
	m_pMap = map;

	m_bIsCollision = false;
	m_bIsAppear = false;


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
	m_pContext->Init(D3DXVECTOR2(550, 280), 30, "나눔명조", 0.05, 0xFFFFFFFF);
	//m_pPlayer = new CharacterParant;


}

void Npc::Update()
{
	if (m_pNpc)
	{
		m_pNpc->World();
		CheckCollision();
		Talk();
		m_pContext->Update();
		//m_pNpc->Update();
	}

}

void Npc::Render()
{
	if (m_pNpc)m_pNpc->Render();
}

void Npc::CheckCollision()
{
	if (IntersectSphere(m_pNpc->GetBoundSphere(), m_pPlayer->GetCharacter()->GetBoundSphere()))
	{
		m_bIsCollision = true;
	}
	else
	{
		m_bIsCollision = false;
	}

}

void Npc::Talk()
{
	if (m_bIsCollision)
	{
		m_pContext->AddText("하이?\n\n하이??????");
	}


}

void Npc::Debug()
{
}
