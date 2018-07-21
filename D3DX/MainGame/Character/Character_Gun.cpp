#include "../../stdafx.h"
#include "Character_Gun.h"
#include "../Map.h"
#include "Inventory.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../DamageUI.h"


Character_Gun::Character_Gun()
{
}


Character_Gun::~Character_Gun()
{
}


void Character_Gun::Init(CHRTYPE type, CHARSELECT order, DropManager* Drop)
{
	m_eChrType = CHRTYPE_GUN;
	if (order == CHAR_ONE)
	{
		//�ѳ�ĳ
		m_pCharacter = MODELMANAGER->GetModel("�ޱ׳ʽ�", MODELTYPE_X);
		m_eNumTarget = NUM_SINGLE;
		m_eCharSelect = CHAR_ONE;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 1.7f;
		m_Status->chr.fCheRate = 70.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 20;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 50;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 50;
		m_Status->chr.fRange = 20.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order, Drop);


		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 550, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(33, 598, 0));


		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("�ޱ׳ʽ�_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));
	
	}
	else if (order == CHAR_TWO)
	{
		//Ȱ��ĳ
		m_pCharacter = MODELMANAGER->GetModel("��ī��", MODELTYPE_X);
		m_eNumTarget = NUM_SINGLE;
		m_eCharSelect = CHAR_TWO;
		m_Status->chr.fAgi = 50.0f;
		m_Status->chr.fAtkSpeed = 2.2f;
		m_Status->chr.fCheRate = 70.0f;
		m_Status->chr.fHit = 70.0f;
		m_Status->chr.fMagicRate = 25.0f;
		m_Status->chr.fPhyRate = 25.0f;
		m_Status->chr.fSpeed = 0.32f;
		m_Status->chr.nAtk = 22;
		m_Status->chr.nCurrentHP = 100;
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 25.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order, Drop);

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 550, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(33, 598, 0));

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	
	}
}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		Controller();
	
		KeyControl();
		Move();


		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pInheritateIco->Update();
		Effect();

		PlayerProgressBar();
		//CountAppearDamage();
		m_pDamage->Update(*m_pCharacter->GetPosition());
	}
}

void Character_Gun::Render()
{
	if (m_pCharacter)
	{
		m_pCharacter->Render();
		//CharacterParant::Render();
		m_pInventory->Render();

		//��Ʈ����Ʈ 
	
		m_pDamage->Render();
		//AppearDamage();


		CharacterParant::Render();
		m_pUIobj->Render();
		m_pInheritateIco->Render();
		m_pHPBar->Render();
		m_pStaminaBar->Render();
	}
}

void Character_Gun::KeyControl()
{
	//������ �޸���
	if (INPUT->KeyDown('W'))
	{
		SOUND->Play("FootStep4");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_FRONT;
		
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;
		
			ChangeAnimation();
		}
	}
	//�ڷ� �޸���
	if (INPUT->KeyDown('S'))
	{
		SOUND->Play("FootStep4");
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_BACK;
			
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;
			
			ChangeAnimation();
		}
	}
	//������ �뽬
	if (INPUT->KeyDown('Q'))
	{
		SOUND->Play("FootStep3");
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_DASH_FRONT;
		
			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('Q'))
	{
		SOUND->Stop("FootStep3");
		if (m_eCondition == CHAR_DASH_FRONT)
		{
			m_eCondition = CHAR_RUN_FRONT;
		
			m_bIsDash = false;
			ChangeAnimation();
		}
	}
	//�ڷ� �뽬
	if (INPUT->KeyDown('E'))
	{
		SOUND->Play("FootStep3");
		SOUND->Stop("FootStep4");
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_DASH_BACK;
			
			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('E'))
	{
		SOUND->Stop("FootStep3");
		if (m_eCondition == CHAR_DASH_BACK)
		{
			m_eCondition = CHAR_RUN_BACK;
			
			m_bIsDash = false;
			ChangeAnimation();
		}
	}

	//�Ϲݰ���
	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("GunAttack");
			SOUND->Play("�ޱ׳ʽ�_����");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("��ī��_����");
			SOUND->Play("BowAttack");
		}
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
		
			m_bIsAttack = true;
			SetTarget();
			m_nDamageCount = 0;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp(VK_SPACE))
	{
		m_bIsAttack = false;
	}


	//��ų����
	if (INPUT->KeyDown('K'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;
			
			m_bIsSkill = true;
			ChangeAnimation();
		}
	}


	//������ų
	if (INPUT->KeyDown('T'))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("�ޱ׳ʽ�_����_��");
			SOUND->Play("�ޱ׳ʽ�_����");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("��ī��_����");
			SOUND->Play("BowAttack");
		}
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_INHERENT;
			MultiAttack();
			ChangeAnimation();
		}
	}
	if (INPUT->KeyUp('T'))
	{
		m_nDamageCount = 0;
	}

	
	//�ִϸ��̼� �ѹ��� ������ ��������
	if (m_pCharacter->IsAnimationEnd())
	{
		switch (m_eCondition)
		{
		case CHAR_SKILL:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_ATTACK:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_HIT:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_INHERENT:
			m_eCondition = CHAR_IDLE;
			break;
		case CHAR_DIE:
			m_eCondition = CHAR_NONE;
			m_bIsDead = false;
			break;
		}
		ChangeAnimation();
	}

	//�ǰ� ���߿� ���� �����ϰ� �����
	if (m_eCondition == CHAR_HIT)
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			if (!SOUND->IsPlaySound("�ޱ׳ʽ�_�ǰ�")) SOUND->Play("�ޱ׳ʽ�_�ǰ�");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			if (!SOUND->IsPlaySound("��ī��_�ǰ�")) SOUND->Play("��ī��_�ǰ�");
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			m_eCondition = CHAR_ATTACK;
			m_bIsAttack = true;
			//Attack();
			ChangeAnimation();
		}
	}

	//�뽬�϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}

	//���ݻ����϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_ATTACK)
	{
		m_pCharacter->SetAnimationSpeed(1.0f * (m_Status->chr.fAtkSpeed + m_pInventory->GetEquipStat().chr.fAtkSpeed));
	}

	if (m_eCondition == CHAR_ATTACK)
	{
		Attack();
	}

	if (m_eCondition == CHAR_IDLE)
	{
		if (SOUND->IsPlaySound("FootStep4")) SOUND->Stop("FootStep4");
		if (SOUND->IsPlaySound("FootStep3")) SOUND->Stop("FootStep3");
	}
}

void Character_Gun::Attack()
{
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	m_nDamageCount++;
	
		if (m_eCharSelect == CHAR_ONE)
		{
			if (m_nIndex < 0) return;
			if (m_nDamageCount <= 3)
			{
				D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(2, 2, 2);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.5, 0.5);
				testSkillpos += TempDir * (Length * 0.3f);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			}
		}
		else if (m_eCharSelect == CHAR_TWO)
		{
			if (m_nIndex < 0) return;
			if (m_nDamageCount <= 3)
			{
				D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				ST_EFFECT tempEffect;
				ZeroMemory(&tempEffect, sizeof(tempEffect));

				tempEffect.time = FRand(0.1, 0.4);
				tempEffect.isRY = true;
				tempEffect.isRX = true;
				tempEffect.height = 3.0f;
				tempEffect.SetAlpha(255, 255, 0);
				tempEffect.SetScale(2, 2, 2);
				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
				EffectObject* tempEFOBJ;
				tempEFOBJ = new EffectObject;

				D3DXVECTOR3 TempDir;
				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				D3DXVec3Normalize(&TempDir, &TempDir);

				float Length = D3DXVec3Length(&(MonPos - pos));

				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
				testSkillpos.y += 1.0f;
				testSkillpos.x += FRand(-0.5, 0.5);
				testSkillpos.z += FRand(-0.5, 0.5);
				testSkillpos += TempDir * (Length * 0.3f);
				tempEFOBJ->Init(tempEffect, testSkillpos);

				m_vecEffect.push_back(tempEFOBJ);
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
			}
		}

}

void Character_Gun::MultiAttack()
{
//	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//�÷��̾� ������ �ް� 
//	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//�÷��̾� ���� �ް� 
//
//	m_vecTarget.clear();
//	m_nIndex = -1;
////	m_nIndex2 = -1;
////	m_nIndex3 = -1;
//	int subMinIndex = -1;
//
//	int MINIndex2 = -1;
//	float MinDistance = 0.0f;
//	float radius;
//	D3DXVECTOR3 mosPos;
//	float distance;
//	float subDistance = 0.0f;
//	float subDistance2 = 0.0f;
//
//
//	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//	{
//		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 
//
//		float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
//		mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
//		float distance1 = D3DXVec3Length(&(mosPos - pos));
//
//		if (distance1 - radius1 > m_Status->chr.fRange) continue;
//		distance = distance1;
//		subDistance = distance;
//		subDistance2 = distance;
//
//		m_nIndex = i;
////		m_nIndex2 = i;
////		m_nIndex3 = i;
//		break;
//	}
//	if (m_nIndex != -1)//���� �������� �� ���Ͱ� ���������� 
//	{
//		for (int i = m_nIndex + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//		{
//			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
//			float radius2 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
//			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
//			float distance2 = D3DXVec3Length(&(mosPos - pos));
//			if (distance2 - radius2 > m_Status->chr.fRange) continue;
//			if (distance >= distance2)
//			{
//				distance = distance2;
//				m_nIndex = i;
//			}
//		}
//		m_vecTarget.push_back(m_nIndex);
//		//�ι�° �����༮�� �߰�
//		for (int i = m_nIndex2 + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//		{
//			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
//			if (i == m_nIndex) continue;//���� ������ �ּҰŸ��� ���� ���͸� �糢�� 
//			float radius3 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
//			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
//			float distance3 = D3DXVec3Length(&(mosPos - pos));
//			if (distance3 - radius3 > m_Status->chr.fRange) continue;
//			if (subDistance >= distance3)
//			{
//				subDistance = distance3;
//				m_nIndex2 = i;
//			}
//		}
//		m_vecTarget.push_back(m_nIndex2);
//
//		//����° ����� �༮�� �߰�
//		for (int i = m_nIndex3 + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
//		{
//			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
//			if (i == m_nIndex) continue;//���� ������ �ּҰŸ��� ���� ���͸� �糢�� 
//			if (i == m_nIndex2) continue;//���� ������ �ּҰŸ��� ���� ���͸� �糢�� 
//			float radius4 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
//			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
//			float distance4 = D3DXVec3Length(&(mosPos - pos));
//			if (distance4 - radius4 > m_Status->chr.fRange) continue;
//			if (subDistance2 >= distance4)
//			{
//				subDistance2 = distance4;
//				m_nIndex3 = i;
//			}
//		}
//		m_vecTarget.push_back(m_nIndex3);
//	}
//
//	if (m_nIndex < 0) return;
//	D3DXVECTOR3 front;
//	D3DXMATRIX matY;
//	D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
//	D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
//	D3DXVECTOR3 v0 = front;
//	//������
//	D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//	//D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
//	D3DXVECTOR3 v1 = MonPos - pos;
//	D3DXVec3Normalize(&v0, &v1);
//	float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
//	if (dot >= cos(m_Status->chr.fScale / 2))
//	{
//		//if (m_nIndex == -1) return;
//		if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;
//
//		m_fPrevTime = m_fElpTime;
//
//		m_nDamageCount++;
//		if (m_eCharSelect == CHAR_ONE)
//		{
//			if (m_nDamageCount <= 3)
//			{
//				ST_EFFECT tempEffect;
//				ZeroMemory(&tempEffect, sizeof(tempEffect));
//
//				tempEffect.time = FRand(0.1, 0.4);
//				tempEffect.isRY = true;
//				tempEffect.isRX = true;
//				tempEffect.height = 3.0f;
//				tempEffect.SetAlpha(255, 255, 0);
//				tempEffect.SetScale(2, 2, 2);
//				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
//				EffectObject* tempEFOBJ;
//				tempEFOBJ = new EffectObject;
//
//				D3DXVECTOR3 TempDir;
//				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				D3DXVec3Normalize(&TempDir, &TempDir);
//
//				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				testSkillpos.y += 1.0f;
//				testSkillpos.x += FRand(-0.5, 0.5);
//				testSkillpos.z += FRand(-0.5, 0.5);
//				testSkillpos += TempDir * 4.0f;
//				tempEFOBJ->Init(tempEffect, testSkillpos);
//
//				m_vecEffect.push_back(tempEFOBJ);
//
//				for (int i = 0; i < m_vecTarget.size(); i++)
//				{
//					if (m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetIsResPawn())return;
//					m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(100);
//				}
//			}
//		}
//		else if (m_eCharSelect == CHAR_TWO)
//		{
//			if (m_nDamageCount <= 3)
//			{
//				ST_EFFECT tempEffect;
//				ZeroMemory(&tempEffect, sizeof(tempEffect));
//
//				tempEffect.time = FRand(0.1, 0.4);
//				tempEffect.isRY = true;
//				tempEffect.isRX = true;
//				tempEffect.height = 3.0f;
//				tempEffect.SetAlpha(255, 255, 0);
//				tempEffect.SetScale(2, 2, 2);
//				tempEffect.tex = TEXTUREMANAGER->AddTexture("Gun", "Texture/Effect/gun.png");
//				EffectObject* tempEFOBJ;
//				tempEFOBJ = new EffectObject;
//
//				D3DXVECTOR3 TempDir;
//				TempDir = *m_pCharacter->GetPosition() - *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				D3DXVec3Normalize(&TempDir, &TempDir);
//
//				D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
//				testSkillpos.y += 1.0f;
//				testSkillpos.x += FRand(-0.5, 0.5);
//				testSkillpos.z += FRand(-0.5, 0.5);
//				testSkillpos += TempDir * 4.0f;
//				tempEFOBJ->Init(tempEffect, testSkillpos);
//
//				m_vecEffect.push_back(tempEFOBJ);
//
//				for (int i = 0; i < m_vecTarget.size(); i++)
//				{
//					if (m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->GetIsResPawn())return;
//					m_pMonsterManager->GetMonsterVector()[m_vecTarget[i]]->CalculDamage(100);
//				}
//			}
//
//		}
//	}
}


