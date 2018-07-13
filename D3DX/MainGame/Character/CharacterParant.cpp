#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Item/ItemParent.h"


void CharacterParant::SKill()
{
	//Ư�� Ű�� ������ ������ Ŭ������ skill�� �����Ѵ�. 
}

void CharacterParant::Move()
{
	Debug();
	m_pInventory->GetEquipStat();
	
	//if(m_bIsUnderAttacked) AppearDamage();
	
	



	//�����¿� ���� ������
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();


	

	D3DXMATRIX matAngle;
	D3DXMatrixRotationYawPitchRoll(&matAngle, m_pCharacter->GetRotation()->y, m_pCharacter->GetRotation()->x, m_pCharacter->GetRotation()->z);

	m_vfront = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vfront, &m_vfront, &matAngle);
	
	if (INPUT->KeyDown('J'))
	{
		int a = rand() % 20;
		SetCurrentHP(a);
		m_eCondition = CHAR_HIT;
		ChangeAnimation();
	}


	if (INPUT->KeyPress('A'))
	{
		m_pCharacter->GetRotation()->y -= 0.05f;
	}
	if (INPUT->KeyPress('D'))
	{
		m_pCharacter->GetRotation()->y += 0.05f;
	}

	//�޸��¸��
	if (m_eCondition == CHAR_RUN_FRONT)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * (m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed), pos.z - m_vfront.z * (m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed));
		if (height >= 0)
		{
			pos.y = height;
			if (m_bIsUnderAttacked)
			{
				m_pCharacter->SetPosition(pos - m_vfront * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed) - 0.1f));
			}
			else
			{
				m_pCharacter->SetPosition(pos - m_vfront * (m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed));
			}
		}
		else
		{
			return;
		}
	}
	else if (m_eCondition == CHAR_RUN_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed )-0.2f), pos.z - m_vfront.z * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed )-0.2f));
		if (height >= 0)
		{
			pos.y = height;
			
			if (m_bIsUnderAttacked)
			{
				m_pCharacter->SetPosition(pos + m_vfront * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed) - 0.2f));
			}
			else
			{
				m_pCharacter->SetPosition(pos + m_vfront * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().chr.fSpeed) - 0.2f));
			}

		}
		else if(height == -1)
		{
			return;
		}
	}
	//�뽬��
	if (m_eCondition == CHAR_DASH_FRONT)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x *0.57, pos.z - m_vfront.z *0.57);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos - m_vfront * 0.57);
		}
		else if (height == -1)
		{
			return;
		}
	}
	if (m_eCondition == CHAR_DASH_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x *0.33, pos.z - m_vfront.z *0.33);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos + m_vfront * 0.33);
		}
		else
		{
			return;
		}
	}
	ControllStamina();

	//�ǰ� 0�Ʒ��� �������� �ʵ��� ����
	if (m_Status->chr.nCurrentHP  <= 0)
	{
		m_Status->chr.nCurrentHP = 0;
	}
	
	m_pParticle->World();
	m_pParticle->Update();

	m_pParticle2->World();
	m_pParticle2->Update();


	m_pParticle4->World();
	m_pParticle4->Update();

	//�����̵�
	MGSKill();
	
}

void CharacterParant::AppearDamage()
{
	D3DXVECTOR3 tempPos;
	
	
	//TODO : �������� ���Ϳ� ��Ƽ� [����������] ����ϰ� ����� �ϴ°� �����غ���. ���ÿ� �������� �����µ� ������ �ϳ����� ���� ����.

	char damageChar[16];

	for (int i = 0; i < m_vecDamage.size();)
	{	
		sprintf_s(damageChar, 16, "%d", m_vecDamage[i].Damage);			//sprintf�� ���ڸ� ����ȭ

		m_vecDamage[i].time += TIME->GetElapsedTime();		//�Ϸ���Ÿ���� �����༭ �ð����� ���۽ð��� ��� ���ؼ� ����Ÿ���� �Ǹ�. �̷������� ���ǹ� ����

		tempPos = *m_pCharacter->GetPosition();
		
		m_vecDamage[i].x += m_vecDamage[i].time * cosf(m_vecDamage[i].angle * D3DX_PI / 180)*3.0f;
		tempPos.y -= -4.0f + m_vecDamage[i].time * -sinf(m_vecDamage[i].angle * D3DX_PI / 180)*1.5f;
		
		
		auto temp = Convert3DTo2D(tempPos);
		
	
		tempPos.x = temp.x;
		tempPos.x += m_vecDamage[i].x;
		tempPos.y = temp.y;
		tempPos.z = 0;

		if (m_vecDamage[i].time < m_vecDamage[i].endTime) //���� ���۽ð��� ����ð����� ������ 
		{
			m_vecDamage[i].angle++;
			m_vecDamage[i].alpha-= 3.0f;
			for (int j = 0; j < strlen(damageChar); j++)
			{
				if (damageChar[j] == '0')
				{
					m_pUIDamage[0]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[0]->Update();
					m_pUIDamage[0]->Render();
					m_pUIDamage[0]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '1')
				{
					m_pUIDamage[1]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[1]->Update();
					m_pUIDamage[1]->Render();
					m_pUIDamage[1]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '2')
				{
					m_pUIDamage[2]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[2]->Update();
					m_pUIDamage[2]->Render();
					m_pUIDamage[2]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '3')
				{
					m_pUIDamage[3]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[3]->Update();
					m_pUIDamage[3]->Render();
					m_pUIDamage[3]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '4')
				{
					m_pUIDamage[4]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[4]->Update();
					m_pUIDamage[4]->Render();
					m_pUIDamage[4]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '5')
				{
					m_pUIDamage[5]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[5]->Update();
					m_pUIDamage[5]->Render();
					m_pUIDamage[5]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '6')
				{
					m_pUIDamage[6]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[6]->Update();
					m_pUIDamage[6]->Render();
					m_pUIDamage[6]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '7')
				{
					m_pUIDamage[7]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[7]->Update();
					m_pUIDamage[7]->Render();
					m_pUIDamage[7]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '8')
				{
					m_pUIDamage[8]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[8]->Update();
					m_pUIDamage[8]->Render();
					m_pUIDamage[8]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '9')
				{
					m_pUIDamage[9]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
					m_pUIDamage[9]->Update();
					m_pUIDamage[9]->Render();
					m_pUIDamage[9]->SetAlpha(m_vecDamage[i].alpha);
				}
			} 
			i++; //���� ������ �����Ǹ� i++�ض�
		}
		else
		{
			m_vecDamage.erase(m_vecDamage.begin() + i);
		}
	}
}

void CharacterParant::Controller()
{
	//===============���Ű ����=====================//
	if (INPUT->KeyDown('I'))
	{
		m_pInventory->OpenInventory();
	}
	if (INPUT->KeyDown('P'))
	{
		m_pInventory->OpenEquip();
	}	
}

void CharacterParant::Debug()
{
	if (DEBUG)
	{
		//ȭ�鿡 ���� �ؽ�Ʈ��
		D3DXVECTOR3 tempPos1;
		tempPos1 = *m_pCharacter->GetPosition();
		tempPos1.y += 3;
		D3DXVECTOR2 pos1 = Convert3DTo2D(tempPos1);
		TEXT->Add(to_string(m_Status->chr.nCurrentHP), pos1.x, pos1.y, 30);
		TEXT->Add(to_string(m_Status->chr.nMaxHp), pos1.x, pos1.y - 25.0f, 30);

		TEXT->Add(to_string(m_Status->chr.nCurrentStam), pos1.x + 90, pos1.y, 30);
		TEXT->Add(to_string(m_Status->chr.nMaxStam), pos1.x + 90, pos1.y - 25.0f, 30);
		//CAMERA->SetMode(CAMERA_FREE);
	}
}

void CharacterParant::CheckDirection()
{

}

void CharacterParant::ControllStamina()
{
	//���׹̳� �����Լ�
	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_Status->chr.nCurrentStam  -= 1;
	}

	if (m_Status->chr.nCurrentStam <= 0)
	{
		m_eCondition = CHAR_IDLE;
		m_bIsDash = false;
		ChangeAnimation();
	}


	if (m_eCondition == CHAR_IDLE)
	{
		if (m_Status->chr.nCurrentStam <= m_Status->chr.nMaxStam)
		{
			m_Status->chr.nCurrentStam += 1;
			if (m_Status->chr.nCurrentStam >= m_Status->chr.nMaxStam)
			{
				m_Status->chr.nCurrentStam = m_Status->chr.nMaxStam;
			}
		}
	}


}

//void CharacterParant::UnderAttacked()
//{
//	if (INPUT->KeyDown('Z'))
//	{
//		m_Status->chr.nCurrentHP -= 50;
//	}
//		if (m_Status->chr.nCurrentHP <= 0 && !m_bIsDead)
//		{
//			m_bIsDead = true;
//			m_eCondition = CHAR_DIE;
//			ChangeAnimation();
//			if (m_eCondition == CHAR_DIE) m_pParticle2->SetPosition(*m_pCharacter->GetPosition());
//		}
//}

void CharacterParant::SetCurrentHP(int hp)
{
	ST_DAMAGETEXT tempDMGTEXT;
	tempDMGTEXT.Damage = hp;
	tempDMGTEXT.time = 0.0f;
	tempDMGTEXT.endTime = 1.0f;
	tempDMGTEXT.angle = rand() % 100;
	tempDMGTEXT.alpha = 255.0f;
	tempDMGTEXT.x = 0.0f;
	m_vecDamage.push_back(tempDMGTEXT);
	
	m_Status->chr.nCurrentHP -= hp;
	

	if (m_Status->chr.nCurrentHP <= 0 && !m_bIsDead)
	{
		m_bIsDead = true;
		m_eCondition = CHAR_DIE;
		ChangeAnimation();
		if(m_eCondition == CHAR_DIE) m_pParticle2->SetPosition(*m_pCharacter->GetPosition());
	}
}



void CharacterParant::CalculDamage(float damage)
{
	//if (!m_bIsInvincible)
	//{
		
		m_eCondition = CHAR_HIT;
		ChangeAnimation();
	

	//	m_bIsInvincible = true;
		m_bIsUnderAttacked = true;
		float totalRate =
			m_Status->chr.fPhyRate +
			m_Status->chr.fMagicRate +
			m_Status->chr.fCheRate;

		float totalDamage = totalRate * m_pInventory->GetEquipStat().chr.nDef;

		totalDamage = damage - totalDamage;

		totalDamage /= 3;

		if (totalDamage <= 1) totalDamage = 1;

		totalDamage = round(totalDamage);

		SetCurrentHP(totalDamage);
	//}
}

void CharacterParant::Attack()
{	
	//1. ���� ������ �ε����� ������ ������ �����.
	//2. �Ÿ��� ���� ������ �����.
	//3. �ʱ�ȭ�� 0��° ����� �Ÿ��� ��´�.(0��°���� �׾������ ���� ū�� �ƹ��ų� �ִµ�)�ε����� 0�̴�.
	//4. i = 1���� ���ͻ����ŭ ���鼭 �Ÿ��� ���ϰ� 2���� ���� ������ �񱳸� �Ͽ� �������� ������ �ٽ� �ְ� �ε������� �ٲ۴�.


		D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//�÷��̾� ������ �ް� 
		D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//�÷��̾� ���� �ް� 
		
		int MinIndex = -1;
		int subMinIndex = -1;
		int MINIndex2 = -1;
		float MinDistance = 0.0f;
		float radius;
		D3DXVECTOR3 mosPos;
		float distance;
		float subDistance = 0.0f;

	if (m_eChrType == CHRTYPE_SWORD || m_eChrType == CHRTYPE_GUN)
	{
		//�������� �Ǵ� ���͸� ���ϰ� 
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 
			
			float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
			float distance1 = D3DXVec3Length(&(mosPos - pos));
	
			if (distance1 - radius1 > m_Status->chr.fRange) continue;
			distance = distance1;
			distance = subDistance;

			MinIndex = i;
			break;
		}
		if (MinIndex != -1)//���� �������� �� ���Ͱ� ���������� 
		{
			for (int i = MinIndex+1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
			{
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
				float radius2 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				float distance2 = D3DXVec3Length(&(mosPos - pos));
				if (distance2 - radius2 > m_Status->chr.fRange) continue;
				if (distance > distance2)
				{
					distance = distance2;
					MinIndex = i;
				}
				
			}
			//�ü� 
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			//������
			D3DXVECTOR3 v1 = mosPos - pos;
			D3DXVec3Normalize(&v0, &v1);
			float dot = D3DXVec3Dot(&v0, &v1)/ D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(m_Status->chr.fScale / 2))
			{
				m_pMonsterManager->GetMonsterVector()[MinIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().chr.nAtk);
			}
		}
	}
	else if (m_eChrType == CHRTYPE_MAGIC)
	{
		//�������� �Ǵ� ���͸� ���ϰ� 
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//�����Ҷ��� �ǵ帮�� �ʰ� 

			float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//������ �ٿ�� ������� ������ �ް� 
			D3DXVECTOR3 mosPos1 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//���� ������ �ް� 
			float distance1 = D3DXVec3Length(&(mosPos1 - pos));

			if (distance1 - radius1 > m_Status->chr.fRange) continue;
			distance = distance1;
			//radius = radius1;

			MinIndex = i;
			break;
		}
		if (MinIndex != -1)//���� �������� �� ���Ͱ� ���������� 
		{
			for (int i = MinIndex + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
			{
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//�����Ҷ��� �ǵ帮�� �ʰ� 
				radius = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				D3DXVECTOR3 mosPos2 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());
				float distance2 = D3DXVec3Length(&(mosPos2 - pos));
				if (distance2 - radius > m_Status->chr.fRange) continue;
				if (distance > distance2)
				{
					distance = distance2;
					MinIndex = i;
				}
			}
			m_pMonsterManager->GetMonsterVector()[MinIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().chr.nAtk);
			m_pParticle->SetPosition(D3DXVECTOR3(m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->x,
				m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->y + 2.0f,
				m_pMonsterManager->GetMonsterVector()[MinIndex]->GetModel()->GetPosition()->z));
			m_pParticle->TimeReset();
			
		}
	}
}

void CharacterParant::CountAppearDamage()
{

	if (m_bIsUnderAttacked)
	{
		m_stDamaged.startDamageTime += TIME->GetElapsedTime();
	}

	if (m_stDamaged.startDamageTime < m_stDamaged.endDamageTime && m_bIsUnderAttacked)
	{
		m_pParticle->SetPosition(D3DXVECTOR3(m_pCharacter->GetPosition()->x, m_pCharacter->GetPosition()->y + 1.5f, m_pCharacter->GetPosition()->z));
		m_pParticle->TimeReset();
	}

	if (m_stDamaged.startDamageTime >= 0.3f)
	{
		m_stDamaged.startDamageTime = 0.0f;
		m_bIsUnderAttacked = false;
		//m_bIsInvincible = false;
	}

}

void CharacterParant::SkillIconAlpha()
{
	
}

void CharacterParant::PlayerProgressBar()
{
	float tempF = (float)m_Status->chr.nCurrentHP / m_Status->chr.nMaxHp;
	m_pHPBar->SetScale(D3DXVECTOR3(tempF, 1, 1));
	D3DXVECTOR3 UIPos = D3DXVECTOR3(1350, 520, 0);
	m_pHPBar->SetPosition(UIPos);
	m_pHPBar->Update();


	float tempS = (float)m_Status->chr.nCurrentStam / m_Status->chr.nMaxStam;
	m_pStaminaBar->SetScale(D3DXVECTOR3(tempS, 1, 1));
	D3DXVECTOR3 StaPos = D3DXVECTOR3(1350, 535, 0);
	m_pStaminaBar->SetPosition(StaPos);
	m_pStaminaBar->Update();
	

}

void CharacterParant::MGSKill()
{
	if (!m_bIsPotal) m_pParticle3->SetPosition(*m_pCharacter->GetPosition());


	D3DXVECTOR3 Potalpos = *m_pParticle3->GetPosition();
	D3DXVECTOR3	playerTempPos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 Potalrot = *m_pParticle3->GetRotation();

	D3DXMATRIX matPotalAngle;
	D3DXMatrixRotationYawPitchRoll(&matPotalAngle, m_pParticle3->GetRotation()->y, m_pParticle3->GetRotation()->x, m_pParticle3->GetRotation()->z);

	m_vPotalfront = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vPotalfront, &m_vPotalfront, &matPotalAngle);
	//�̵���ƼŬ Ű���� ���� 
	if (INPUT->KeyPress(VK_LEFT))
	{
		m_pParticle3->GetRotation()->y -= 0.05f;
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		m_pParticle3->GetRotation()->y += 0.05f;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		float Potalheight = m_pSampleMap->GetHeight(Potalpos.x - m_vPotalfront.x *0.3, Potalpos.z - m_vPotalfront.z *0.3);
		if (Potalheight >= 0)
		{
			Potalpos.y = Potalheight;
			if (D3DXVec3Length(&(playerTempPos - Potalpos)) <= 14.0f)
			{
				m_pParticle3->SetPosition(Potalpos + m_vPotalfront * 0.3);
			}
		}
		else if (Potalheight == - 1)
		{
			return;
		}
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		float Potalheight = m_pSampleMap->GetHeight(Potalpos.x - m_vPotalfront.x *0.3, Potalpos.z - m_vPotalfront.z *0.3);
		if (Potalheight >= 0)
		{
			Potalpos.y = Potalheight;
			if (D3DXVec3Length(&(playerTempPos- Potalpos)) <= 7.0f)
			{
				m_pParticle3->SetPosition(Potalpos - m_vPotalfront * 0.3);
			}
		}
		else if(Potalheight == -1)
		{
			return;
		}
	}

	if (m_bIsPotal)
	{
		m_pParticle3->World();
		m_pParticle3->Update();

		auto nav = m_pSampleMap->GetNavMesh();
		auto r = RayAtWorldSpace(g_ptMouse);
		float tempdistance;
		for (int i = 0; i < nav.size(); i+=3)
		{
			if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
			{
				if (D3DXVec3Length(&(playerTempPos - Potalpos)) < 14.0f)
				{
					m_pParticle3->SetPosition(r.orig + r.dir* tempdistance);
				}
			}
		}
	}
}




CharacterParant::CharacterParant()
{
	m_Status = new STATUS;
	MODELMANAGER->AddModel("�Ƹ�", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī��", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�콺Ƽ��", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("�ޱ׳ʽ�", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("����", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī��", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	MODELMANAGER->AddModel("��ī", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("����", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	


	TEXTUREMANAGER->AddTexture("��ī��_����", "Texture/Portrait/Portrait_PC_Aknal_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�Ƹ�_����", "Texture/Portrait/Portrait_PC_Arin_S_Icon.png");
	TEXTUREMANAGER->AddTexture("��ī_����", "Texture/Portrait/Portrait_PC_BeakAh_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�콺Ƽ��_����", "Texture/Portrait/Portrait_PC_Hestia_S_Icon.png");
	TEXTUREMANAGER->AddTexture("�ޱ׳ʽ�_����", "Texture/Portrait/Portrait_Pc_Magnus_Icon.png");
	TEXTUREMANAGER->AddTexture("����_����", "Texture/Portrait/Portrait_PC_Riah_S_Icon.png");
	TEXTUREMANAGER->AddTexture("��ī��_����", "Texture/Portrait/Portrait_PC_Skadi_S_Icon.png");
	TEXTUREMANAGER->AddTexture("����_����", "Texture/Portrait/velvet.png");

	

	//���ݽ� ��ƼŬ
	PARTICLE->AddParticle("ATTACK",
		TEXTUREMANAGER->AddTexture("��ƼŬ1", "Texture/Particle/Sphere.png"),
		"Particle/underAttacked.ptc");
	//�÷��̾� �׾����� ��ƼŬ
	PARTICLE->AddParticle("Die",
		TEXTUREMANAGER->AddTexture("��ƼŬ2", "Texture/Particle/Sphere.png"),
		"Particle/PlayerDie.ptc");

	//���� ���뽺ų�� ��ƼŬ
	PARTICLE->AddParticle("Potal",
		TEXTUREMANAGER->AddTexture("����Ż", "Texture/Particle/Sphere.png"),
		"Particle/Test.ptc");
	//�ڷ���Ʈ �ڸ��� ������ ��ƼŬ
	PARTICLE->AddParticle("teleport",
		TEXTUREMANAGER->AddTexture("����Ż2", "Texture/Particle/Sphere.png"),
		"Particle/Teleport.ptc");


	//������ �̹��� 
	TEXTUREMANAGER->AddTexture("����0", "Texture/Damage/0.png");
	TEXTUREMANAGER->AddTexture("����1", "Texture/Damage/1.png");
	TEXTUREMANAGER->AddTexture("����2", "Texture/Damage/2.png");
	TEXTUREMANAGER->AddTexture("����3", "Texture/Damage/3.png");
	TEXTUREMANAGER->AddTexture("����4", "Texture/Damage/4.png");
	TEXTUREMANAGER->AddTexture("����5", "Texture/Damage/5.png");
	TEXTUREMANAGER->AddTexture("����6", "Texture/Damage/6.png");
	TEXTUREMANAGER->AddTexture("����7", "Texture/Damage/7.png");
	TEXTUREMANAGER->AddTexture("����8", "Texture/Damage/8.png");
	TEXTUREMANAGER->AddTexture("����9", "Texture/Damage/9.png");

	TEXTUREMANAGER->AddTexture("����0_r", "Texture/Damage/0_r.png");
	TEXTUREMANAGER->AddTexture("����1_r", "Texture/Damage/1_r.png");
	TEXTUREMANAGER->AddTexture("����2_r", "Texture/Damage/2_r.png");
	TEXTUREMANAGER->AddTexture("����3_r", "Texture/Damage/3_r.png");
	TEXTUREMANAGER->AddTexture("����4_r", "Texture/Damage/4_r.png");
	TEXTUREMANAGER->AddTexture("����5_r", "Texture/Damage/5_r.png");
	TEXTUREMANAGER->AddTexture("����6_r", "Texture/Damage/6_r.png");
	TEXTUREMANAGER->AddTexture("����7_r", "Texture/Damage/7_r.png");
	TEXTUREMANAGER->AddTexture("����8_r", "Texture/Damage/8_r.png");
	TEXTUREMANAGER->AddTexture("����9_r", "Texture/Damage/9_r.png");

	//���α׷�����
	TEXTUREMANAGER->AddTexture("�÷��̾�_����Ʈ��", "Texture/PlayerProgressBar/frontBar.jpg");
	TEXTUREMANAGER->AddTexture("�÷��̾�_���", "Texture/PlayerProgressBar/backBar.jpg");

	TEXTUREMANAGER->AddTexture("���׹̳�_����Ʈ��", "Texture/PlayerProgressBar/staminaFrontBar.jpg");
	TEXTUREMANAGER->AddTexture("���׹̳�_���", "Texture/PlayerProgressBar/staminaBackBar.jpg");
}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pParticle);
	SAFE_DELETE(m_pParticle2);
	SAFE_DELETE(m_pParticle3);
	SAFE_DELETE(m_pParticle4);

	SAFE_RELEASE(m_pUIobj);
	SAFE_RELEASE(m_pHPBar);
	SAFE_RELEASE(m_pStaminaBar);
	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(m_pUIDamage[i]);
	}
	
	m_pMonsterManager = NULL;
	SAFE_DELETE(m_pInventory);
	
}

void CharacterParant::Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager)
{
	m_pSampleMap = map;
	m_pMonsterManager = pMonsterManager;
	
	//TODO : �ٿ�� �ڽ� ����� (ĳ���� ũ�⸶�� ������ �Է�������
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;



	m_pCharacter->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	startPos.y = 300.0f;
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos.x, startPos.z), startPos.z));

	//�κ��丮
	m_pInventory = new Inventory;
	m_pInventory->CreateInventory(5,3, this);


	//TODO : �ٿ�� �ڽ� ����� (ĳ���� ũ�⸶�� ������ �Է�������
	m_pCharacter->CreateBound(box);
	m_pCharacter->SetBoundSphere(m_pCharacter->GetOrigBoundSphere().center, 100.0f);

	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());


	
	
	m_temp = 0;
	m_nCalAction = 0;

	//�⺻ ���¼���
	m_eCondition = CHAR_IDLE;
	ChangeAnimation();
	
	m_bIsFront = false;
	m_bIsDash = false;
	m_bIsDead = false;
	m_bIsAttack = false;
	m_bIsUnderAttacked = false;
	m_bIsSkill = false;
	m_bIsInvincible = false;
	m_bIsPotal = false;

	m_fStamina = 10.0f;
	m_nDamage = 0;
	m_fDamageCount = 0.0;
	m_fDamageAngle = 0.0f;

	m_stDamaged.startDamageTime = 0.0f;
	m_stDamaged.endDamageTime = 1.0f;


	//��Ʈ����Ʈ UI
	m_pUIobj = new UIObject;
	//���α׷�����
	m_pHPBar = new UIObject;
	m_pStaminaBar = new UIObject;

	m_pHPBar->SetTexture(TEXTUREMANAGER->GetTexture("�÷��̾�_����Ʈ��"));
	D3DXVECTOR3 UIPos = D3DXVECTOR3(1350, 520, 0);
	m_pHPBar->SetPosition(UIPos);
	UIObject* backBar = new UIObject;
	backBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
	backBar->SetTexture(TEXTUREMANAGER->GetTexture("�÷��̾�_���"));
	m_pHPBar->AddChild(backBar);

	m_pStaminaBar->SetTexture(TEXTUREMANAGER->GetTexture("���׹̳�_����Ʈ��"));
	D3DXVECTOR3 StaPos = D3DXVECTOR3(1350, 535, 0);
	m_pStaminaBar->SetPosition(startPos);
	UIObject* staBackBar = new UIObject;
	staBackBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
	staBackBar->SetTexture(TEXTUREMANAGER->GetTexture("���׹̳�_���"));
	m_pStaminaBar->AddChild(staBackBar);

	//������ UI
	for (int i = 0; i < 10; i++)
	{
		m_pUIDamage[i] = new UIObject;
	}

	m_pUIDamage[0]->SetTexture(TEXTUREMANAGER->GetTexture("����0"));
	m_pUIDamage[1]->SetTexture(TEXTUREMANAGER->GetTexture("����1"));
	m_pUIDamage[2]->SetTexture(TEXTUREMANAGER->GetTexture("����2"));
	m_pUIDamage[3]->SetTexture(TEXTUREMANAGER->GetTexture("����3"));
	m_pUIDamage[4]->SetTexture(TEXTUREMANAGER->GetTexture("����4"));
	m_pUIDamage[5]->SetTexture(TEXTUREMANAGER->GetTexture("����5"));
	m_pUIDamage[6]->SetTexture(TEXTUREMANAGER->GetTexture("����6"));
	m_pUIDamage[7]->SetTexture(TEXTUREMANAGER->GetTexture("����7"));
	m_pUIDamage[8]->SetTexture(TEXTUREMANAGER->GetTexture("����8"));
	m_pUIDamage[9]->SetTexture(TEXTUREMANAGER->GetTexture("����9"));
	

	m_pParticle = PARTICLE->GetParticle("ATTACK");
	m_pParticle2 = PARTICLE->GetParticle("Die");
	m_pParticle3 = PARTICLE->GetParticle("Potal");
	m_pParticle4 = PARTICLE->GetParticle("teleport");

	m_pParticle3->SetPosition(D3DXVECTOR3(m_pCharacter->GetPosition()->x, m_pCharacter->GetPosition()->y, m_pCharacter->GetPosition()->z + 5.0f));
}



void CharacterParant::Render()
{
	//��Ʈ����Ʈ 
	//m_pUIobj->Render();
	m_pParticle->Render();
	m_pParticle2->Render();
	if (m_bIsPotal) m_pParticle3->Render();
	m_pParticle4->Render();
}

void CharacterParant::KeyControl()
{
	//������ �޸���
	if (INPUT->KeyDown('W'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_FRONT;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('W'))
	{
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_IDLE;
			ChangeAnimation();
		}
	}
	//�ڷ� �޸���
	if (INPUT->KeyDown('S'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
		{
			m_eCondition = CHAR_RUN_BACK;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('S'))
	{
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_IDLE;
			ChangeAnimation();
		}
	}
	//������ �뽬
	if (INPUT->KeyDown('Q'))
	{
		if (m_eCondition == CHAR_RUN_FRONT)
		{
			m_eCondition = CHAR_DASH_FRONT;
			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('Q'))
	{
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
		if (m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_DASH_BACK;
			m_bIsDash = true;
			ChangeAnimation();
		}
	}
	else if (INPUT->KeyUp('E'))
	{
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
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
			m_bIsAttack = true;
			Attack();
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

	//�����̵� ����
	if (INPUT->KeyDown('T'))
	{
		m_bIsPotal = true;
	}
	else if (INPUT->KeyUp('T'))
	{
		m_bIsPotal = false;
		m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x+1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
		m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
		m_pParticle4->TimeReset();
	}

	if (m_bIsPotal)
	{
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			m_bIsPotal = false;
			m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x + 1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
			m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
			m_pParticle4->TimeReset();
		}
	}

	//���ݻ��¿��� �ִϸ��̼� �ѹ��� ������ �����·� ������
	if (m_pCharacter->IsAnimationEnd()&& m_eCondition == CHAR_ATTACK)
	{
  		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	//��ų���¿��� �ִϸ��̼� �ѹ��� ������ �����·� ������
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_SKILL)
	{
		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}

	//�ǰݻ��¿��� �ִϸ��̼� �ѹ��� ������ �����·� ������
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_HIT)
	{
		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	
	//�뽬�϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}

	//���ݻ����϶� �ִϸ��̼� ���ǵ� ����
	if (m_eCondition == CHAR_ATTACK)
	{
		m_pCharacter->SetAnimationSpeed(1.0f * (m_Status->chr.fAtkSpeed+m_pInventory->GetEquipStat().chr.fAtkSpeed));
	}

	//���� �ֱ�
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_DIE)
	{
		m_eCondition = CHAR_NONE;
		m_bIsDead = false;
	}


}

void CharacterParant::ChangeAnimation()
{
	switch (m_eCondition)
	{
	case CHAR_IDLE:
			m_pCharacter->SetBlendAnimation("IDLE");
			m_pCharacter->SetBlendTime(0.27f);
			m_pCharacter->SetAnimationSpeed(1.0f);
		break;
	case CHAR_DASH_FRONT:
		m_pCharacter->SetAnimation("RUN");
	
		break;
	case CHAR_DASH_BACK:
		m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_RUN_FRONT:
			m_pCharacter->SetAnimation("RUN");
			m_pCharacter->SetAnimationSpeed(1.0f);
		break;
	case CHAR_RUN_BACK:
		m_pCharacter->SetAnimation("RUN");
		m_pCharacter->SetAnimationSpeed(1.0f);
		break;
	case CHAR_SKILL:
			m_pCharacter->SetAnimation("SKILL");
		break;
	case CHAR_ATTACK:
			m_pCharacter->SetAnimation("ATTACK");
		break;
	case CHAR_DIE:
		m_pCharacter->SetAnimation("DIE");
		break;
	case CHAR_HIT:
			m_pCharacter->SetAnimation("HIT");
		break;
	case CHAR_BATTLEREADY:
			m_pCharacter->SetAnimation("BATTLEREADY");
		break;
	case CHAR_NONE :
		break;
	}
}
