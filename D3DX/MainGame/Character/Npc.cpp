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

	if (pSender->GetName().compare("��ų") == 0)
		m_eOverReward = NPC_SKILL;

	if (pSender->GetName().compare("��") == 0)
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

	if (pSender->GetName().compare("��ų") == 0)
	{
		SkillUnSeal();
		m_eSelectReward = NPC_SKILL;
		m_pContext->ChangeText(4, "ĩ.. ��̾��� ��ų�̳�..\n���� �ڰ� �ƴѵ�~!");
		m_pEndContext->ChangeText(0, "��ų �޾��ݾ�!\n���� �ٰ� ����!");
		m_pContext->SetIndex(4);
		m_pContext->SetKeyLock(false);
	}

	if (pSender->GetName().compare("��") == 0)
	{
		PetUnlock();
		m_eSelectReward = NPC_PET;
		m_pContext->ChangeText(4, "��.. �Ϳ��� ����..!\n(��ó��...)");
		m_pEndContext->ChangeText(0, "�Ϳ���?    \n��..�ƴ�!   �� ���� �긻�̾�!");
		m_pContext->SetIndex(4);
		m_pContext->SetKeyLock(false);
	}
}

void Npc::Init(D3DXVECTOR3 pos)
{
	if (m_isOnce)
		return;

	SAFE_DELETE(m_pNpc);
	m_pNpc = MODELMANAGER->GetModel("����", MODELTYPE_X);
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
	m_pPortrait->SetTexture(TEXTUREMANAGER->GetTexture("����_�ʻ�ȭ"));
	m_pPortrait->SetPosition(D3DXVECTOR3(0, 120, 0.1));
	m_pPortrait->SetScale(D3DXVECTOR3(1.5, 1.5, 1.5));

	m_pSelect = new UIObject;
	m_pSelect->SetTexture(TEXTUREMANAGER->GetTexture("������"));
	m_pSelect->SetPosition(D3DXVECTOR3(1520 / 2, 805 / 2 - 200, 0));
	m_pSelect->SetAnchor(UIAC_C);
	m_pSelect->SetName("��ų");
	m_pSelect->SetColor(D3DXVECTOR3(200, 200, 200));
	m_pSelect->SetFunction(this);

	UIObject * child = new UIObject;
	child->SetTexture(TEXTUREMANAGER->GetTexture("������"));
	child->SetPosition(D3DXVECTOR3(537 / 2, 170, 0));
	child->SetAnchor(UIAC_C);
	child->SetName("��");
	child->SetFunction(this);
	child->SetColor(D3DXVECTOR3(200, 200, 200));
	m_pSelect->AddChild(child);

	//���̾�α�			��ġ				������  ��Ʈ       �ӵ�    ����
	m_pContext = new Dialogue;
	m_pContext->Init(D3DXVECTOR2(550, 630), 40, "UhBee Yiseul", 0.05, 0xFFFFFFFF);
	m_pContext->SetKey(VK_LBUTTON, VK_RBUTTON, 'C');

	m_pContext->AddText("��..��!\n���� ������ �; ���°� �ƴϾ�!");
	m_pContext->AddText("5% �� Ȯ���� ������ ������ ���̶�!");
	m_pContext->AddText("...");
	m_pContext->AddText("���� ���ϴ°ų� ���� �����!");
	m_pContext->AddText("����");
	m_pContext->AddText("��¶��! ��..���غ�!\n�����ϴ°� �ƴ϶�...       ���� �׳� ������!\n(�β�����ϱ�..)");
	m_pContext->AddText("====������ by �帲����===");

	m_pEndContext = new Dialogue;
	m_pEndContext->Init(D3DXVECTOR2(550, 630), 40, "UhBee Yiseul", 0.05, 0xFFFFFFFF);
	m_pEndContext->SetKey(VK_LBUTTON, VK_RBUTTON, 'C');

	m_pEndContext->AddText("����");
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
						TEXT->Add("������ �ѹ濡 ���ư��� ��û�� �ñر⸦ ��´�.", 560, 180, 32, "UhBee Yiseul", 0xFFFFFFFF);
					else
						TEXT->Add("������ �ѹ濡 ���ư��� ��û�� �ñر⸦ ��´�.", 560, 180, 32, "UhBee Yiseul", 0xC8FFFFFF);
					if (m_eOverReward == NPC_PET)
						TEXT->Add("���� ȸ���� �����۱��� �ֿ��ִ� �Ϳ��� ���� ��´�.", 560, 315, 32, "UhBee Yiseul", 0xFFFFFFFF);
					else
						TEXT->Add("���� ȸ���� �����۱��� �ֿ��ִ� �Ϳ��� ���� ��´�.", 560, 315, 32, "UhBee Yiseul", 0xC8FFFFFF);
				}
			}
			else
				m_pEndContext->Update();
			CameraViewChange();
		}

		if(m_bIsCollision)TEXT->Add("����", 160, 575, 40, "UhBee Yiseul", 0xFFFFFFFF);

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