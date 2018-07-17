#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Item/ItemParent.h"
#include "Character_Shield.h"


void CharacterParant::SKill()
{
	//특정 키를 누르면 아이템 클래스의 skill을 실행한다. 
	//m_pInventory->GetWeapon()->Skill1(,);
}

void CharacterParant::Move()
{
	Debug();
	m_pInventory->GetEquipStat();
	m_fElpTime += TIME->GetElapsedTime();


	//전후좌우 점프 움직임
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();


	

	D3DXMATRIX matAngle;
	D3DXMatrixRotationYawPitchRoll(&matAngle, m_pCharacter->GetRotation()->y, m_pCharacter->GetRotation()->x, m_pCharacter->GetRotation()->z);

	m_vfront = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vfront, &m_vfront, &matAngle);
	


	if (INPUT->KeyPress('A'))
	{
		m_pCharacter->GetRotation()->y -= 0.05f;
	}
	if (INPUT->KeyPress('D'))
	{
		m_pCharacter->GetRotation()->y += 0.05f;
	}

	//달리는모션
	if (m_eCondition == CHAR_RUN_FRONT)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * (m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed), pos.z - m_vfront.z * (m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed));
		if (height >= 0)
		{
			pos.y = height;
			if (m_bIsUnderAttacked)
			{
				m_pCharacter->SetPosition(pos - m_vfront * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed) - 0.1f));
			}
			else
			{
				m_pCharacter->SetPosition(pos - m_vfront * (m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed));
			}
		}
		else
		{
			return;
		}
	}
	else if (m_eCondition == CHAR_RUN_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed )-0.2f), pos.z - m_vfront.z * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed )-0.2f));
		if (height >= 0)
		{
			pos.y = height;
			
			if (m_bIsUnderAttacked)
			{
				m_pCharacter->SetPosition(pos + m_vfront * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed) - 0.2f));
			}
			else
			{
				m_pCharacter->SetPosition(pos + m_vfront * ((m_Status->chr.fSpeed + m_pInventory->GetEquipStat().item.fSpeed) - 0.2f));
			}

		}
		else if(height == -1)
		{
			return;
		}
	}
	//대쉬용
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

	//피가 0아래로 내려가지 않도록 고정
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

}

void CharacterParant::AppearDamage()
{
	D3DXVECTOR3 tempPos;
	
	
	//TODO : 데미지를 벡터에 담아서 [순차적으로] 출력하고 지우고 하는걸 생각해보자. 동시에 데미지가 들어오는데 지금은 하나씩만 띄우고 있음.

	char damageChar[16];

	for (int i = 0; i < m_vecDamage.size();)
	{	
		sprintf_s(damageChar, 16, "%d", m_vecDamage[i].Damage);			//sprintf로 숫자를 문자화

		m_vecDamage[i].time += TIME->GetElapsedTime();		//일랩스타임을 더해줘서 시간제어 시작시간에 계속 더해서 엔드타임이 되면. 이런식으로 조건문 제어

		tempPos = *m_pCharacter->GetPosition();
		
		m_vecDamage[i].x += m_vecDamage[i].time * cosf(m_vecDamage[i].angle * D3DX_PI / 180)*3.0f;
		tempPos.y -= -4.0f + m_vecDamage[i].time * -sinf(m_vecDamage[i].angle * D3DX_PI / 180)*1.5f;
		
		
		auto temp = Convert3DTo2D(tempPos);
		
	
		tempPos.x = temp.x;
		tempPos.x += m_vecDamage[i].x;
		tempPos.y = temp.y;
		tempPos.z = 0;

		if (m_vecDamage[i].time < m_vecDamage[i].endTime) //만약 시작시간이 엔드시간보다 작으면 
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
			i++; //위의 조건이 만족되면 i++해라
		}
		else
		{
			m_vecDamage.erase(m_vecDamage.begin() + i);
		}
	}
}

void CharacterParant::Controller()
{
	//===============기능키 제어=====================//
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
		//화면에 띄우는 텍스트들
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
	//스테미나 관리함수
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

void CharacterParant::shield()
{
	//TODO::
	//방패캐릭을 소환시켜 플레이어 앞에 유지. 
	//소환시 방패캐릭의 체력이 차감
	//체력 0시 역소환
	//D3DXVECTOR3 tempAngle;
	
	//m_pShieldChr->SetRotation(*m_pCharacter->GetRotation());
	//m_pShieldChr->SetPosition(*m_pCharacter->GetPosition() - m_vfront * 3.0f );


}

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
	if (m_eCondition == CHAR_DIE)
	{
		return;
	}
	if (!m_bIsSubChr)
	{
		if (m_eCondition != CHAR_HIT)
		{
			m_eCondition = CHAR_HIT;
			ChangeAnimation();
		}

		//	m_bIsInvincible = true;
		m_bIsUnderAttacked = true;
		float totalRate =
			m_Status->chr.fPhyRate +
			m_Status->chr.fMagicRate +
			m_Status->chr.fCheRate;

		float totalDamage = totalRate * (m_pInventory->GetEquipStat().item.nDef + m_Status->chr.nDef);

		totalDamage = damage - totalDamage;
		totalDamage /= 3;
		if (totalDamage <= 1) totalDamage = 1;
		totalDamage = round(totalDamage);
		SetCurrentHP(totalDamage);
	}
	else
	{
		float Shield = round(damage);
		m_pShieldChr->SetShieldCurHp(m_pShieldChr->GetShieldCurHp() - Shield);

		if (m_pShieldChr->GetShieldCurHp() <= 0)
		{
			//m_pShieldChr->Die();
			m_bIsSubChr = false;
			m_pShieldChr->SetShieldCurHp(m_pShieldChr->GetShieldMaxHp());
		}
	}

	
}

void CharacterParant::Attack()
{	
	//1. 제일 가까운놈 인덱스를 저장할 변수를 만든다.
	//2. 거리를 담을 변수를 만든다.
	//3. 초기화에 0번째 놈과의 거리를 담는다.(0번째놈이 죽었을경우 대충 큰값 아무거나 넣는데)인덱스는 0이다.
	//4. i = 1부터 벡터사이즈만큼 돌면서 거리를 구하고 2번에 만든 변수와 비교를 하여 작은놈의 값으로 다시 넣고 인덱스값을 바꾼다.

		D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//플레이어 포지션 받고 
		D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//플레이어 각도 받고 
		
		//int MinIndex = -1;
		m_nIndex = -1;
		int subMinIndex = -1;
		int MINIndex2 = -1;
		float MinDistance = 0.0f;
		float radius;
		D3DXVECTOR3 mosPos;
		float distance;
		float subDistance = 0.0f;


		


	if (m_eChrType == CHRTYPE_SWORD || m_eChrType == CHRTYPE_GUN)
	{
		//기준점이 되는 몬스터를 구하고 
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//리젠할때는 건드리지 않고 
			
			float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//몬스터의 바운드 스페어의 반지름 받고 
			mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
			float distance1 = D3DXVec3Length(&(mosPos - pos));
	
			if (distance1 - radius1 > m_Status->chr.fRange) continue;
			distance = distance1;
			distance = subDistance;

			m_nIndex = i;
			break;
		}
		if (m_nIndex != -1)//만약 기준점이 된 몬스터가 구해졌으면 
		{
			for (int i = m_nIndex +1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
			{
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//리젠할때는 건드리지 않고 
				float radius2 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				float distance2 = D3DXVec3Length(&(mosPos - pos));
				if (distance2 - radius2 > m_Status->chr.fRange) continue;
				if (distance > distance2)
				{
					distance = distance2;
					m_nIndex = i;
				}
				
			}
			//시선 
			D3DXVECTOR3 front;
			D3DXMATRIX matY;
			D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
			D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
			D3DXVECTOR3 v0 = front;
			//대상방향
			D3DXVECTOR3 v1 = mosPos - pos;
			D3DXVec3Normalize(&v0, &v1);
			float dot = D3DXVec3Dot(&v0, &v1)/ D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
			if (dot >= cos(m_Status->chr.fScale / 2))
			{
				//if (m_nIndex == -1) return;
				if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

				m_fPrevTime = m_fElpTime;

				m_nDamageCount++;

				if (m_nDamageCount <= 3)
				{
					ST_EFFECT tempEffect;
					ZeroMemory(&tempEffect, sizeof(tempEffect));

					tempEffect.time = FRand(0.1, 0.4);
					tempEffect.isRY = true;
					tempEffect.isRX = true;
					tempEffect.height = 3.0f;
					tempEffect.SetAlpha(255, 255, 0);
					tempEffect.SetScale(1, 0.8, 0.8);
					tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/TestSkill.png");
					EffectObject* tempEFOBJ;
					tempEFOBJ = new EffectObject;

					D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition();
					testSkillpos.y += 1.0f;
					testSkillpos.x += FRand(-0.5, 0.5);
					tempEFOBJ->Init(tempEffect, testSkillpos);

					m_vecEffect.push_back(tempEFOBJ);
					m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().item.nAtk);
				}
			}
		}
	}
	else if (m_eChrType == CHRTYPE_MAGIC)
	{
		//기준점이 되는 몬스터를 구하고 
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//리젠할때는 건드리지 않고 

			float radius1 = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//몬스터의 바운드 스페어의 반지름 받고 
			D3DXVECTOR3 mosPos1 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
			float distance1 = D3DXVec3Length(&(mosPos1 - pos));

			if (distance1 - radius1 > m_Status->chr.fRange) continue;
			distance = distance1;
			//radius = radius1;

			m_nIndex = i;
			break;
		}
		if (m_nIndex != -1)//만약 기준점이 된 몬스터가 구해졌으면 
		{
			for (int i = m_nIndex + 1; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
			{
				if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;	//리젠할때는 건드리지 않고 
				radius = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;
				D3DXVECTOR3 mosPos2 = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());
				float distance2 = D3DXVec3Length(&(mosPos2 - pos));
				if (distance2 - radius > m_Status->chr.fRange) continue;
				if (distance > distance2)
				{
					distance = distance2;
					m_nIndex = i;
				}
			}
			m_pMonsterManager->GetMonsterVector()[m_nIndex]->CalculDamage(m_Status->chr.nAtk + m_pInventory->GetEquipStat().chr.nAtk);
			m_pParticle->SetPosition(D3DXVECTOR3(m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition()->x,
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition()->y + 2.0f,
				m_pMonsterManager->GetMonsterVector()[m_nIndex]->GetModel()->GetPosition()->z));
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
	
	/*if(m_bIsSubChr)
	{
		float tempC = (float)m_nShieldCurHp / m_nShieldMaxHp;


		m_pShieldHp->SetScale(D3DXVECTOR3(tempC, 1, 1));

		D3DXVECTOR3 ShieldPos = *m_pShieldChr->GetPosition();
		ShieldPos.y += 5.0f;

		auto temp = Convert3DTo2D(ShieldPos);

		ShieldPos.x = temp.x;
		ShieldPos.y = temp.y;
		ShieldPos.z = 0;
		m_pShieldHp->SetPosition(ShieldPos);
		m_pShieldHp->Update();
	}
*/
}

void CharacterParant::MGSKill()
{
	//if (!m_bIsPotal) m_pParticle3->SetPosition(*m_pCharacter->GetPosition());


	//D3DXVECTOR3 Potalpos = *m_pParticle3->GetPosition();
	//D3DXVECTOR3	playerTempPos = *m_pCharacter->GetPosition();
	//D3DXVECTOR3 Potalrot = *m_pParticle3->GetRotation();

	//D3DXMATRIX matPotalAngle;
	//D3DXMatrixRotationYawPitchRoll(&matPotalAngle, m_pParticle3->GetRotation()->y, m_pParticle3->GetRotation()->x, m_pParticle3->GetRotation()->z);

	//m_vPotalfront = D3DXVECTOR3(0, 0, 1);
	//D3DXVec3TransformNormal(&m_vPotalfront, &m_vPotalfront, &matPotalAngle);
	////이동파티클 키보드 제어 
	//if (INPUT->KeyPress(VK_LEFT))
	//{
	//	m_pParticle3->GetRotation()->y -= 0.05f;
	//}
	//if (INPUT->KeyPress(VK_RIGHT))
	//{
	//	m_pParticle3->GetRotation()->y += 0.05f;
	//}
	//if (INPUT->KeyPress(VK_UP))
	//{
	//	float Potalheight = m_pSampleMap->GetHeight(Potalpos.x - m_vPotalfront.x *0.3, Potalpos.z - m_vPotalfront.z *0.3);
	//	if (Potalheight >= 0)
	//	{
	//		Potalpos.y = Potalheight;
	//		if (D3DXVec3Length(&(playerTempPos - Potalpos)) <= 14.0f)
	//		{
	//			m_pParticle3->SetPosition(Potalpos + m_vPotalfront * 0.3);
	//		}
	//	}
	//	else if (Potalheight == - 1)
	//	{
	//		return;
	//	}
	//}
	//if (INPUT->KeyPress(VK_DOWN))
	//{
	//	float Potalheight = m_pSampleMap->GetHeight(Potalpos.x - m_vPotalfront.x *0.3, Potalpos.z - m_vPotalfront.z *0.3);
	//	if (Potalheight >= 0)
	//	{
	//		Potalpos.y = Potalheight;
	//		if (D3DXVec3Length(&(playerTempPos- Potalpos)) <= 7.0f)
	//		{
	//			m_pParticle3->SetPosition(Potalpos - m_vPotalfront * 0.3);
	//		}
	//	}
	//	else if(Potalheight == -1)
	//	{
	//		return;
	//	}
	//}

	//if (m_bIsPotal)
	//{
	//	m_pParticle3->World();
	//	m_pParticle3->Update();

	//	auto nav = m_pSampleMap->GetNavMesh();
	//	auto r = RayAtWorldSpace(g_ptMouse);
	//	float tempdistance;
	//	for (int i = 0; i < nav.size(); i+=3)
	//	{
	//		if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
	//		{
	//			if (D3DXVec3Length(&(playerTempPos - Potalpos)) < 14.0f)
	//			{
	//				m_pParticle3->SetPosition(r.orig + r.dir* tempdistance);
	//			}
	//		}
	//	}
	//}
}

void CharacterParant::Effect()
{
	for (int i = 0; i < m_vecEffect.size();)
	{
		if (!m_vecEffect[i]->IsFinish())
		{
			m_vecEffect[i]->Update();
			i++;
		}
		else
		{
			SAFE_DELETE(m_vecEffect[i]);
			m_vecEffect.erase(m_vecEffect.begin() + i);
		}
	}
}

void CharacterParant::StoreEffect(int index)
{
	if (m_nIndex == -1) return;
	if (m_fElpTime < m_fPrevTime + m_fEffectInterval) return;

	m_fPrevTime = m_fElpTime;

		ST_EFFECT tempEffect;
		ZeroMemory(&tempEffect, sizeof(tempEffect));

		tempEffect.time = FRand(0.1, 0.4);
		tempEffect.isRY = true;
		tempEffect.isRX = true;
		tempEffect.height = 3.0f;
		tempEffect.SetAlpha(255, 255, 0);
		tempEffect.SetScale(1, 0.8, 0.8);
		tempEffect.tex = TEXTUREMANAGER->AddTexture("testSkill", "Texture/Effect/TestSkill.png");
		EffectObject* tempEFOBJ;
		tempEFOBJ = new EffectObject;

		D3DXVECTOR3 testSkillpos = *m_pMonsterManager->GetMonsterVector()[index]->GetModel()->GetPosition();
		testSkillpos.y += 1.0f;
		testSkillpos.x += FRand(-0.5, 0.5);
		tempEFOBJ->Init(tempEffect, testSkillpos);

		m_vecEffect.push_back(tempEFOBJ);
}

void CharacterParant::StoreAttack(int index)
{

}


CharacterParant::CharacterParant()
{
	m_Status = new STATUS;
	//공격시 파티클
	PARTICLE->AddParticle("ATTACK",
		TEXTUREMANAGER->AddTexture("파티클1", "Texture/Particle/Sphere.png"),
		"Particle/underAttacked.ptc");
	//플레이어 죽었을때 파티클
	PARTICLE->AddParticle("Die",
		TEXTUREMANAGER->AddTexture("파티클2", "Texture/Particle/Sphere.png"),
		"Particle/PlayerDie.ptc");

	//법사 전용스킬용 파티클
	PARTICLE->AddParticle("Potal",
		TEXTUREMANAGER->AddTexture("포오탈", "Texture/Particle/Sphere.png"),
		"Particle/Test.ptc");
	//텔레포트 자리에 나오는 파티클
	PARTICLE->AddParticle("teleport",
		TEXTUREMANAGER->AddTexture("포오탈2", "Texture/Particle/Sphere.png"),
		"Particle/Teleport.ptc");
}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
	SAFE_DELETE(m_pShieldChr);
	SAFE_DELETE(m_pParticle);
	SAFE_DELETE(m_pParticle2);
	SAFE_DELETE(m_pParticle3);
	SAFE_DELETE(m_pParticle4);

	SAFE_RELEASE(m_pUIobj);
	SAFE_RELEASE(m_pHPBar);
	SAFE_RELEASE(m_pStaminaBar);
	SAFE_RELEASE(m_pShieldHp);
	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(m_pUIDamage[i]);
	}
	
	m_pMonsterManager = NULL; 
	m_pSampleMap = NULL;
	SAFE_DELETE(m_pInventory);
	
}

void CharacterParant::Init(Map* map, CHRTYPE type, CHARSELECT order, MonsterManager* pMonsterManager)
{
	m_pSampleMap = map;
	m_pMonsterManager = pMonsterManager;
	
	//TODO : 바운딩 박스 만들기 (캐릭터 크기마다 일일히 입력해주자
	ST_SIZEBOX box;
	box.highX = 50.0f;
	box.highY = 180.0f;
	box.highZ = 50.0f;
	box.lowX = -50.0f;
	box.lowY = 10.0f;
	box.lowZ = -50.0f;



	m_pCharacter->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	D3DXVECTOR3 startPos = map->GetSpawnPlayer();
	startPos.y = 300.0f;
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos.x, startPos.z), startPos.z));

	//인벤토리
	if (m_pInventory == NULL)
	{
		m_pInventory = new Inventory;
		m_pInventory->CreateInventory(5, 3, this);
	}

	//TODO : 바운딩 박스 만들기 (캐릭터 크기마다 일일히 입력해주자
	m_pCharacter->CreateBound(box);
	m_pCharacter->SetBoundSphere(m_pCharacter->GetOrigBoundSphere().center, 100.0f);

	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 5, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 5, 0));
	CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());


	
	
	m_temp = 0;
	m_nCalAction = 0;

	//기본 상태세팅
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
	m_bIsSubChr = false;

	m_fStamina = 10.0f;
	m_nDamage = 0;
	m_fDamageCount = 0.0;
	m_fDamageAngle = 0.0f;
	m_fElpTime = 0.0f;
	m_fPrevTime = 0.0f;
	m_nDamageCount = 0;

	m_fEffectInterval = 0.1f;

	m_stDamaged.startDamageTime = 0.0f;
	m_stDamaged.endDamageTime = 1.0f;

	m_nAppear = 0;

	//포트레이트 UI
	if(m_pUIobj == NULL) m_pUIobj = new UIObject;
	
	
	//프로그래스바
	if (m_pHPBar == NULL)
	{
		m_pHPBar = new UIObject;
		m_pHPBar->SetTexture(TEXTUREMANAGER->GetTexture("플레이어_프론트바"));
		D3DXVECTOR3 UIPos = D3DXVECTOR3(1350, 520, 0);
		m_pHPBar->SetPosition(UIPos);
		UIObject* backBar = new UIObject;
		backBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
		backBar->SetTexture(TEXTUREMANAGER->GetTexture("플레이어_백바"));
		m_pHPBar->AddChild(backBar);
	}


	if (m_pStaminaBar == NULL)
	{
		m_pStaminaBar = new UIObject;
		m_pStaminaBar->SetTexture(TEXTUREMANAGER->GetTexture("스테미나_프론트바"));
		D3DXVECTOR3 StaPos = D3DXVECTOR3(1350, 535, 0);
		m_pStaminaBar->SetPosition(startPos);
		UIObject* staBackBar = new UIObject;
		staBackBar->SetPosition(D3DXVECTOR3(0, 0, 0.1));
		staBackBar->SetTexture(TEXTUREMANAGER->GetTexture("스테미나_백바"));
		m_pStaminaBar->AddChild(staBackBar);
	}

	
	//데미지 UI
	for (int i = 0; i < 10; i++)
	{
		if(m_pUIDamage[i] == NULL) m_pUIDamage[i] = new UIObject;
	}

	m_pUIDamage[0]->SetTexture(TEXTUREMANAGER->GetTexture("숫자0"));
	m_pUIDamage[1]->SetTexture(TEXTUREMANAGER->GetTexture("숫자1"));
	m_pUIDamage[2]->SetTexture(TEXTUREMANAGER->GetTexture("숫자2"));
	m_pUIDamage[3]->SetTexture(TEXTUREMANAGER->GetTexture("숫자3"));
	m_pUIDamage[4]->SetTexture(TEXTUREMANAGER->GetTexture("숫자4"));
	m_pUIDamage[5]->SetTexture(TEXTUREMANAGER->GetTexture("숫자5"));
	m_pUIDamage[6]->SetTexture(TEXTUREMANAGER->GetTexture("숫자6"));
	m_pUIDamage[7]->SetTexture(TEXTUREMANAGER->GetTexture("숫자7"));
	m_pUIDamage[8]->SetTexture(TEXTUREMANAGER->GetTexture("숫자8"));
	m_pUIDamage[9]->SetTexture(TEXTUREMANAGER->GetTexture("숫자9"));
	

	m_pParticle = PARTICLE->GetParticle("ATTACK");
	m_pParticle2 = PARTICLE->GetParticle("Die");
	m_pParticle3 = PARTICLE->GetParticle("Potal");
	m_pParticle4 = PARTICLE->GetParticle("teleport");

	m_pParticle3->SetPosition(D3DXVECTOR3(m_pCharacter->GetPosition()->x, m_pCharacter->GetPosition()->y, m_pCharacter->GetPosition()->z + 5.0f));


	m_pShieldChr = NULL;
}



void CharacterParant::Render()
{
	//포트레이트 
	//m_pUIobj->Render();
	m_pParticle->Render();
	m_pParticle2->Render();
	if (m_bIsPotal) m_pParticle3->Render();
	m_pParticle4->Render();

	for (int i = 0; i < m_vecEffect.size(); i++)
	{
		m_vecEffect[i]->Render();
	}


}

void CharacterParant::KeyControl()
{
	////앞으로 달리기
	//if (INPUT->KeyDown('W'))
	//{
	//	SOUND->Play("FootStep");
	//	if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
	//	{
	//		m_eCondition = CHAR_RUN_FRONT;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_RUN);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		ChangeAnimation();
	//	}
	//}
	//else if (INPUT->KeyUp('W'))
	//{
	//	SOUND->Stop("FootStep");
	//	if (m_eCondition == CHAR_RUN_FRONT)
	//	{
	//		m_eCondition = CHAR_IDLE;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_IDLE);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		ChangeAnimation();
	//	}
	//}
	////뒤로 달리기
	//if (INPUT->KeyDown('S'))
	//{
	//	SOUND->Play("FootStep");
	//	if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_HIT)
	//	{
	//		m_eCondition = CHAR_RUN_BACK;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_RUN);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		ChangeAnimation();
	//	}
	//}
	//else if (INPUT->KeyUp('S'))
	//{
	//	SOUND->Stop("FootStep");
	//	if (m_eCondition == CHAR_RUN_BACK)
	//	{
	//		m_eCondition = CHAR_IDLE;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_IDLE);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		ChangeAnimation();
	//	}
	//}
	////앞으로 대쉬
	//if (INPUT->KeyDown('Q'))
	//{
	//	if (m_eCondition == CHAR_RUN_FRONT)
	//	{
	//		m_eCondition = CHAR_DASH_FRONT;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_RUN);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		m_bIsDash = true;
	//		ChangeAnimation();
	//	}
	//}
	//else if (INPUT->KeyUp('Q'))
	//{
	//	if (m_eCondition == CHAR_DASH_FRONT)
	//	{
	//		m_eCondition = CHAR_RUN_FRONT;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_RUN);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		m_bIsDash = false;
	//		ChangeAnimation();
	//	}
	//}
	////뒤로 대쉬
	//if (INPUT->KeyDown('E'))
	//{
	//	if (m_eCondition == CHAR_RUN_BACK)
	//	{
	//		m_eCondition = CHAR_DASH_BACK;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_RUN);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		m_bIsDash = true;
	//		ChangeAnimation();
	//	}
	//}
	//else if (INPUT->KeyUp('E'))
	//{
	//	if (m_eCondition == CHAR_DASH_BACK)
	//	{
	//		m_eCondition = CHAR_RUN_BACK;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_RUN);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		m_bIsDash = false;
	//		ChangeAnimation();
	//	}
	//}

	////일반공격
	//if (INPUT->KeyDown(VK_SPACE))
	//{
	//	SOUND->Play("SwordAttack");
	//	if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
	//	{
	//		m_eCondition = CHAR_ATTACK;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_IDLE);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		m_bIsAttack = true;
	//		Attack();
	//		ChangeAnimation();
	//	}
	//}
	//else if (INPUT->KeyUp(VK_SPACE))
	//{
	//	m_bIsAttack = false;
	//}

	////스킬공격
	//if (INPUT->KeyDown('K'))
	//{
	//	if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
	//	{
	//		m_eCondition = CHAR_SKILL;
	//		if (m_bIsSubChr)
	//		{
	//			m_pShieldChr->SetShieldCondition(SUB_IDLE);
	//			m_pShieldChr->ChangeSubChrAni();
	//		}
	//		m_bIsSkill = true;
	//		ChangeAnimation();
	//	}
	//}

	////순간이동 제어
	//if (INPUT->KeyDown('T'))
	//{
	//	m_bIsPotal = true;
	//}
	//else if (INPUT->KeyUp('T'))
	//{
	//	m_bIsPotal = false;
	//	m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x+1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
	//	m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
	//	m_pParticle4->TimeReset();
	//}

	////서브캐릭터 제어
	//if (INPUT->KeyDown('N'))
	//{
	//	m_bIsSubChr = true;
	//}

	//if (m_bIsPotal)
	//{
	//	if (INPUT->KeyDown(VK_LBUTTON))
	//	{
	//		m_bIsPotal = false;
	//		m_pCharacter->SetPosition(D3DXVECTOR3(m_pParticle3->GetPosition()->x + 1.0f, m_pParticle3->GetPosition()->y, m_pParticle3->GetPosition()->z - 1.0f));
	//		m_pParticle4->SetPosition(*m_pCharacter->GetPosition());
	//		m_pParticle4->TimeReset();
	//	}
	//}

	////애니메이션 한바퀴 돌고나서 상태제어
	//if (m_pCharacter->IsAnimationEnd())
	//{
	//	switch (m_eCondition)
	//	{
	//	case CHAR_SKILL:
	//		m_eCondition = CHAR_IDLE;
	//		break;
	//	case CHAR_ATTACK:
	//		m_eCondition = CHAR_IDLE;
	//		break;
	//	case CHAR_HIT:
	//		m_eCondition = CHAR_IDLE;
	//		break;
	//	}
	//	ChangeAnimation();
	//}


	////피격 도중에 공격 가능하게 만들기
	//if(m_eCondition == CHAR_HIT)
	//{
	//	if (INPUT->KeyDown(VK_SPACE))
	//	{
	//		m_eCondition = CHAR_ATTACK;
	//		m_bIsAttack = true;
	//		Attack();
	//		ChangeAnimation();
	//	}
	//}
	//
	////대쉬일때 애니메이션 스피드 제어
	//if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	//{
	//	m_pCharacter->SetAnimationSpeed(5.0f);
	//}

	////공격상태일때 애니메이션 스피드 제어
	//if (m_eCondition == CHAR_ATTACK)
	//{
	//	m_pCharacter->SetAnimationSpeed(1.0f * (m_Status->chr.fAtkSpeed+m_pInventory->GetEquipStat().chr.fAtkSpeed));
	//}

	////끄앙 주금
	//if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_DIE)
	//{
	//	m_eCondition = CHAR_NONE;
	//	m_bIsDead = false;
	//}
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
