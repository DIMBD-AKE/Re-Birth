#include "../../stdafx.h"
#include "Npc.h"
#include "../Map.h"
#include "CharacterParant.h"
#include "Pet.h"


Npc::Npc()
{
	m_bIsAppear = false;
	m_isOnce = false;
	m_eSelectReward = NPC_NONE;
}


Npc::~Npc()
{
	SAFE_DELETE(m_pNpc);
	SAFE_RELEASE(m_pPortrait);
	SAFE_RELEASE(m_pSelect);
	SAFE_DELETE(m_pContext);
}

void Npc::OnEntrance(UIObject * pSender)
{
	pSender->SetColor(D3DXVECTOR3(255, 255, 255));

	if (pSender->GetName().compare("스킬") == 0)
		m_eOverReward = NPC_SKILL;

	if (pSender->GetName().compare("펫") == 0)
		m_eOverReward = NPC_PET;
}

void Npc::OnExit(UIObject * pSender)
{
	pSender->SetColor(D3DXVECTOR3(200, 200, 200));
	m_eOverReward = NPC_NONE;
}

void Npc::OnClick(UIObject * pSender)
{
	if (m_pContext->GetIndex() != 3 || !m_pContext->CurrentEnd())
		return;

	if (pSender->GetName().compare("스킬") == 0)
	{
		SkillUnSeal();
		m_eSelectReward = NPC_SKILL;
		m_pContext->ChangeText(4, "칫.. 재미없게 스킬이네..\n전부 쌘건 아닌데~!");
		m_pEndContext->ChangeText(0, "스킬 받았잖아!\n이제 줄거 없어!");
		m_pContext->SetIndex(4);
		m_pContext->SetKeyLock(false);
	}

	if (pSender->GetName().compare("펫") == 0)
	{
		PetUnlock();
		m_eSelectReward = NPC_PET;
		m_pContext->ChangeText(4, "펫.. 귀엽고 좋지..!\n(나처럼...)");
		m_pEndContext->ChangeText(0, "귀엽지?    \n아..아니!   나 말고 펫말이야!");
		m_pContext->SetIndex(4);
		m_pContext->SetKeyLock(false);
	}
}

void Npc::Init(D3DXVECTOR3 pos)
{
	if (m_isOnce)
		return;

	SAFE_DELETE(m_pNpc);
	m_pNpc = MODELMANAGER->GetModel("리무", MODELTYPE_X);
	m_pNpc->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	m_pNpc->SetRotation(D3DXVECTOR3(0, 3.2, 0));
	m_pNpc->SetPosition(pos);
	
	m_bIsCollision = false;
	m_bIsAppear = true;
	m_bReward = false;

	ST_SIZEBOX box;
	box.highX = 30.0f;
	box.highY = 180.0f;
	box.highZ = 30.0f;
	box.lowX = -30.0f;
	box.lowY = 10.0f;
	box.lowZ = -30.0f;

	m_pNpc->CreateBound(box);
	m_pNpc->SetBoundSphere(m_pNpc->GetOrigBoundSphere().center, 100.0f);


	m_pPortrait = new UIObject;
	m_pPortrait->SetTexture(TEXTUREMANAGER->GetTexture("리무_초상화"));
	m_pPortrait->SetPosition(D3DXVECTOR3(0, 120, 0.1));
	m_pPortrait->SetScale(D3DXVECTOR3(1.5, 1.5, 1.5));

	m_pSelect = new UIObject;
	m_pSelect->SetTexture(TEXTUREMANAGER->GetTexture("선택지"));
	m_pSelect->SetPosition(D3DXVECTOR3(1520 / 2, 805 / 2 - 200, 0));
	m_pSelect->SetAnchor(UIAC_C);
	m_pSelect->SetName("스킬");
	m_pSelect->SetColor(D3DXVECTOR3(200, 200, 200));
	m_pSelect->SetFunction(this);

	UIObject * child = new UIObject;
	child->SetTexture(TEXTUREMANAGER->GetTexture("선택지"));
	child->SetPosition(D3DXVECTOR3(537 / 2, 170, 0));
	child->SetAnchor(UIAC_C);
	child->SetName("펫");
	child->SetFunction(this);
	child->SetColor(D3DXVECTOR3(200, 200, 200));
	m_pSelect->AddChild(child);

	//다이얼로그			위치				사이즈  폰트       속도    색깔
	m_pContext = new Dialogue;
	m_pContext->Init(D3DXVECTOR2(550, 630), 40, "UhBee Yiseul", 0.05, 0xFFFFFFFF);
	m_pContext->SetKey(VK_LBUTTON, VK_RBUTTON, 'C');

	m_pContext->AddText("흐..흥!\n딱히 만나고 싶어서 나온건 아니야!");
	m_pContext->AddText("5% 의 확률로 나오게 되있을 뿐이라구!");
	m_pContext->AddText("...");
	m_pContext->AddText("빨리 원하는거나 고르고 사라져!");
	m_pContext->AddText("선택");
	m_pContext->AddText("어쨋든! 자..잘해봐!\n응원하는게 아니라...       몰라 그냥 빨리가!\n(부끄러우니까..)");
	m_pContext->AddText("====츤데레 by 드림센세===");

	m_pEndContext = new Dialogue;
	m_pEndContext->Init(D3DXVECTOR2(550, 630), 40, "UhBee Yiseul", 0.05, 0xFFFFFFFF);
	m_pEndContext->SetKey(VK_LBUTTON, VK_RBUTTON, 'C');

	m_pEndContext->AddText("선택");
	m_pEndContext->AddText("");
}

void Npc::Update()
{
	if (m_isOnce) return;
	if (m_pNpc && m_bIsAppear)
	{
		m_pNpc->World();
		CheckCollision();
		m_pPortrait->Update();
		m_pSelect->Update();
		if (m_bIsCollision)
		{
			if (!m_bReward)
			{
				m_pContext->Update();
				if (m_pContext->GetIndex() == 3)
					m_pContext->SetKeyLock(true);
				if (m_pContext->GetIndex() == 3 && m_pContext->CurrentEnd())
				{
					if (m_eOverReward == NPC_SKILL)
						TEXT->Add("보스가 한방에 날아가는 엄청난 궁극기를 얻는다.", 560, 180, 32, "UhBee Yiseul", 0xFFFFFFFF);
					else
						TEXT->Add("보스가 한방에 날아가는 엄청난 궁극기를 얻는다.", 560, 180, 32, "UhBee Yiseul", 0xC8FFFFFF);
					if (m_eOverReward == NPC_PET)
						TEXT->Add("스텟 회복에 아이템까지 주워주는 귀여운 펫을 얻는다.", 560, 315, 32, "UhBee Yiseul", 0xFFFFFFFF);
					else
						TEXT->Add("스텟 회복에 아이템까지 주워주는 귀여운 펫을 얻는다.", 560, 315, 32, "UhBee Yiseul", 0xC8FFFFFF);
				}
			}
			else
				m_pEndContext->Update();
			CameraViewChange();
		}

		if(m_bIsCollision)TEXT->Add("리무", 160, 575, 40, "UhBee Yiseul", 0xFFFFFFFF);

		if (!m_bReward)
		{
			if (m_pContext->GetIndex() == m_pContext->GetPage() - 1)
			{
				if (INPUT->KeyDown(VK_LBUTTON))
				{
					if (m_eSelectReward != NPC_NONE)
						m_bReward = true;
					m_bIsCollision = false;
				}
			}
		}
		else
		{
			if (m_pEndContext->GetIndex() == m_pEndContext->GetPage() - 1)
			{
				if (INPUT->KeyDown(VK_LBUTTON))
					m_bIsCollision = false;
			}
		}
	}
}

void Npc::Render()
{
	if (m_isOnce) return;
	if (m_pNpc && m_bIsAppear)m_pNpc->Render();
	if (m_bIsCollision)
	{
		m_pPortrait->Render();
		if (m_pContext->GetIndex() == 3 && m_pContext->CurrentEnd())
		{
			m_pSelect->Render();
		}
	}
}

void Npc::CheckCollision()
{
	if (IntersectSphere(m_pNpc->GetBoundSphere(), m_pPlayer->GetCharacter()->GetBoundSphere()))
	{
		if (!m_bIsCollision)
		{
			if (INPUT->KeyDown('E'))
			{
				m_bIsCollision = true;
				m_pContext->SetIndex(0);
				m_pEndContext->SetIndex(0);
			}
		}
	}
	else
	{
		if (m_eSelectReward != NPC_NONE)
			m_bReward = true;
		m_bIsCollision = false;
		m_pContext->SetKeyLock(false);
	}
}

void Npc::SkillUnSeal()
{
	if (m_bIsCollision) 
		m_pPlayer->SetSkillUnSealed(true);
}

void Npc::PetUnlock()
{
	if (m_bIsCollision)
	{
		m_pPlayer->SetPetUnsealed(true);
		PETTYPE petType = (PETTYPE)(rand() % PETTYPE_END);
		m_pPlayer->SummonPet(petType);
	}
}

void Npc::PlusAttack()
{
}

void Npc::CameraViewChange()
{
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 2.2, 15));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 2, 0));
}