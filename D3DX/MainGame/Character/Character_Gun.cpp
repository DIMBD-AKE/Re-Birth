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


void Character_Gun::Init(CHRTYPE type, CHARSELECT order)
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
		m_Status->chr.nCurrentStam = 100;
		m_Status->chr.nDef = 26;
		m_Status->chr.nMaxHp = 100;
		m_Status->chr.nMaxStam = 100;
		m_Status->chr.fRange = 20.0f;
		m_Status->chr.fScale = 3.2f;
		CharacterParant::Init(type, order);


		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_�̵�"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_������"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));



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
		CharacterParant::Init(type, order);

		m_pSkillBar->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_��ųâ"));
		m_pSkillBar->SetPosition(D3DXVECTOR3(588, 695, 0));

		m_pInheritateIco->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_����"));
		m_pInheritateIco->SetPosition(D3DXVECTOR3(609, 733, 0));

		m_pInheritateIco2->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_�̵�"));
		m_pInheritateIco2->SetPosition(D3DXVECTOR3(722, 733, 0));

		m_pInheritateIco3->SetTexture(TEXTUREMANAGER->GetTexture("���Ÿ�_������"));
		m_pInheritateIco3->SetPosition(D3DXVECTOR3(839, 733, 0));

		m_pChrStat->SetTexture(TEXTUREMANAGER->GetTexture("ĳ����_�������ͽ�"));
		m_pChrStat->SetPosition(D3DXVECTOR3(0, 668, 0));

		m_pUIobj->SetTexture(TEXTUREMANAGER->GetTexture("��ī��_����"));
		m_pUIobj->SetScale(D3DXVECTOR3(0.45, 0.45, 0.45));
		m_pUIobj->SetPosition(D3DXVECTOR3(12, 679, 0));

	
	}

	m_pAimLine->SetTexture(TEXTUREMANAGER->GetTexture("���ؼ�"));

}

void Character_Gun::Update()
{
	if (m_pCharacter)
	{
		Controller();
	
		KeyControl();
		Move();
		setCameraView();
		GunClick();
		m_pInventory->Update();
		m_pCharacter->World();
		m_pUIobj->Update();
		m_pChrStat->Update();
		m_pInheritateIco->Update();
		m_pInheritateIco2->Update();
		m_pInheritateIco3->Update();
		m_pSkillBar->Update();
		Effect();

		PlayerProgressBar();
		//CountAppearDamage();
		m_pDamage->Update(*m_pCharacter->GetPosition());


		if (m_bIsGunView)
		{
			GunClick();
			GunShot();
		}
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
		m_pSkillBar->Render();
		m_pInheritateIco->Render();
		m_pInheritateIco2->Render();
		m_pInheritateIco3->Render();
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
		case CHAR_INHERENT1:
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


	//������ų======================================
	if (INPUT->KeyDown('R'))
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
			m_eCondition = CHAR_INHERENT1;
			MultiAttack();
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('R'))
	{
		m_nDamageCount = 0;
	}

	if (INPUT->KeyDown('F'))
	{
		m_bIsGunView = true;
	}
	else if (INPUT->KeyUp('F'))
	{
		m_bIsGunView = false;
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
	m_vecTarget.clear();
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

	m_nDamageCount++;

	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
	{
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
		float length = D3DXVec3Length(&(MonPos - pos));

		if (length <= m_Status->chr.fRange)
		{	// �ü�
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			// ������
			D3DXVECTOR3 v1 = MonPos - pos;
			D3DXVec3Normalize(&v1, &v1);
			float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(m_Status->chr.fScale / 2))
			{
				m_vecTarget.push_back(i);
			}
		}
	}


	for (int j = 0; j < m_vecTarget.size(); j++)
	{
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->GetModel()->GetPosition();
		D3DXVECTOR3 TempDir;
		TempDir = MonPos - pos;
		D3DXVec3Normalize(&TempDir, &TempDir);

		float Length = D3DXVec3Length(&(MonPos - pos));

		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));

		tempEffect.time = FRand(0.4, 0.7);
		//tempEffect.isRY = true;
		//tempEffect.isRX = true;
		//tempEffect.isRZ = true;
		tempEffect.dir = TempDir;
		tempEffect.SetSpeed(0.2, 0.2, 0.2);
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(0.5, 0.5, 0);
		tempEffect.isSphere = true;
		tempEffect.tex = TEXTUREMANAGER->GetTexture("�Ѿ�");
	

	
		EffectObject* tempEFOBJ;
		tempEFOBJ = new EffectObject;

		D3DXVECTOR3 testSkillpos = *m_pCharacter->GetPosition();
		testSkillpos.y += 2.0f;
		testSkillpos.x += FRand(-2.0, 2.0);
		testSkillpos.z += FRand(-1.3, 1.3);
		//testSkillpos += TempDir * (Length * 0.3f);
		tempEFOBJ->Init(tempEffect, testSkillpos);

		m_vecEffect.push_back(tempEFOBJ);
		m_pMonsterManager->GetMonsterVector()[m_vecTarget[j]]->CalculDamage(1);
	}
}

void Character_Gun::setCameraView()
{

	if (!m_bIsGunView)
	{
		CAMERA->SetCamOffset(D3DXVECTOR3(0, 3, 20));
		CAMERA->SetTargetOffset(D3DXVECTOR3(0, 4, 0));
		CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());
	}
	else
	{
		CAMERA->SetCamOffset(D3DXVECTOR3(0, 10, 20));
		CAMERA->SetTargetOffset(D3DXVECTOR3(0, 10, 0));
		CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());
	}
}

void Character_Gun::GunClick()
{
	auto nav = m_pSampleMap->GetNavMesh();
	auto r = RayAtWorldSpace(g_ptMouse);
	float tempdistance;
	for (int i = 0; i < nav.size(); i += 3)
	{
		if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
		{
			m_vGun = r.orig + (r.dir* tempdistance);
		}
	}
}

void Character_Gun::GunShot()
{
	m_nIndex = -1;
	D3DXVECTOR3 pos = m_vGun;



	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
	{
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
		D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
		float length = D3DXVec3Length(&(MonPos - pos));

		if (length <= 5.0f)
		{	
			m_nIndex = i;
			
		}
	}
	if (m_nIndex < 0)
	{
		return;
	}
	else
	{
		CAMERA->Shake(0.08, 0.3);

		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));

		tempEffect.time = FRand(0.4, 0.7);
		//tempEffect.isRY = true;
		//tempEffect.isRX = true;
		//tempEffect.isRZ = true;
		//tempEffect.SetSpeed(0.2, 0.2, 0.2);
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(0.5, 0.5, 0);
		tempEffect.isSphere = true;
		tempEffect.tex = TEXTUREMANAGER->GetTexture("�Ѿ�");



		EffectObject* tempEFOBJ;
		tempEFOBJ = new EffectObject;

		D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
		testSkillpos.y += FRand(-2.0, 3.0);
		testSkillpos.x += FRand(-2.0, 2.0);
		testSkillpos.z += FRand(-1.3, 1.3);
		//testSkillpos += TempDir * (Length * 0.3f);
		tempEFOBJ->Init(tempEffect, testSkillpos);

		m_vecEffect.push_back(tempEFOBJ);
		m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(1);
	}
}


