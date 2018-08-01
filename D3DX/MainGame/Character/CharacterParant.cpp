#include "../../stdafx.h"
#include "CharacterParant.h"
#include "Inventory.h"
#include "../Map.h"
#include "../Status.h"
#include "../monster/MonsterManager.h"
#include "../monster/MonsterParent.h"
#include "../Item/ItemParent.h"
#include "Character_Shield.h"
#include "Character_Sword.h"
#include "../DamageUI.h"
#include "../Item/DropManager.h"
#include "Npc.h"
#include "Pet.h"


void CharacterParant::SKill()
{
	if (m_pInventory->GetSkill1(this, m_pMonsterManager))
	{
		if (m_eCharSelect == CHAR_ONE)
		{
			SOUND->Play("SwordAttack");
			SOUND->Play("베카_스킬");
		}
		if (m_eCharSelect == CHAR_TWO)
		{
			SOUND->Play("SwordAttack_TWO");
			SOUND->Play("리아_스킬");
		}
		if (m_eCharSelect == CHAR_THREE)
		{
			SOUND->Play("SwordAttack_THREE");
			SOUND->Play("벨벳_스킬");
		}
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;
			if (m_bIsSubChr)
			{
				m_pShieldChr->SetShieldCondition(SUB_IDLE);
				m_pShieldChr->ChangeSubChrAni();
			}
			m_bIsSkill = true;
			ChangeAnimation();
		}
	}
	
	
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
	
	//TODO:: 마우스 클릭 하면 a*함수를 불러와서 이동하게 제어 하는것 추가 하기
	//if (INPUT->KeyDown(VK_LBUTTON))
	//{
	//	auto nav = m_pSampleMap->GetNavMesh();
	//	auto r = RayAtWorldSpace(g_ptMouse);
	//	float tempdistance;
	//	for (int i = 0; i < nav.size(); i += 3)
	//	{
	//		if (D3DXIntersectTri(&nav[i], &nav[i + 1], &nav[i + 2], &r.orig, &r.dir, NULL, NULL, &tempdistance))
	//		{
	//			//마우스 클릭 위치를 받고 
	//			m_pClickPos = r.orig + (r.dir* tempdistance);
	//		}
	//	}
	//	AStar();
	//}
	//AStarMove();

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
	
	m_pParticle->ApplyWorld();
	m_pParticle->Update();

	m_pParticle2->ApplyWorld();
	m_pParticle2->Update();


	m_pParticle4->ApplyWorld();
	m_pParticle4->Update();

}

void CharacterParant::AppearDamage()
{
	//D3DXVECTOR3 tempPos;
	//
	//
	////TODO : 데미지를 벡터에 담아서 [순차적으로] 출력하고 지우고 하는걸 생각해보자. 동시에 데미지가 들어오는데 지금은 하나씩만 띄우고 있음.

	//char damageChar[16];

	//for (int i = 0; i < m_vecDamage.size();)
	//{	
	//	sprintf_s(damageChar, 16, "%d", m_vecDamage[i].Damage);			//sprintf로 숫자를 문자화

	//	m_vecDamage[i].time += TIME->GetElapsedTime();		//일랩스타임을 더해줘서 시간제어 시작시간에 계속 더해서 엔드타임이 되면. 이런식으로 조건문 제어

	//	tempPos = *m_pCharacter->GetPosition();
	//	
	//	m_vecDamage[i].x += m_vecDamage[i].time * cosf(m_vecDamage[i].angle * D3DX_PI / 180)*3.0f;
	//	tempPos.y -= -4.0f + m_vecDamage[i].time * -sinf(m_vecDamage[i].angle * D3DX_PI / 180)*1.5f;
	//	
	//	
	//	auto temp = Convert3DTo2D(tempPos);
	//	
	//
	//	tempPos.x = temp.x;
	//	tempPos.x += m_vecDamage[i].x;
	//	tempPos.y = temp.y;
	//	tempPos.z = 0;

	//	if (m_vecDamage[i].time < m_vecDamage[i].endTime) //만약 시작시간이 엔드시간보다 작으면 
	//	{
	//		m_vecDamage[i].angle++;
	//		m_vecDamage[i].alpha-= 3.0f;
	//		for (int j = 0; j < strlen(damageChar); j++)
	//		{
	//			if (damageChar[j] == '0')
	//			{
	//				m_pUIDamage[0]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[0]->Update();
	//				m_pUIDamage[0]->Render();
	//				m_pUIDamage[0]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '1')
	//			{
	//				m_pUIDamage[1]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[1]->Update();
	//				m_pUIDamage[1]->Render();
	//				m_pUIDamage[1]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '2')
	//			{
	//				m_pUIDamage[2]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[2]->Update();
	//				m_pUIDamage[2]->Render();
	//				m_pUIDamage[2]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '3')
	//			{
	//				m_pUIDamage[3]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[3]->Update();
	//				m_pUIDamage[3]->Render();
	//				m_pUIDamage[3]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '4')
	//			{
	//				m_pUIDamage[4]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[4]->Update();
	//				m_pUIDamage[4]->Render();
	//				m_pUIDamage[4]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '5')
	//			{
	//				m_pUIDamage[5]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[5]->Update();
	//				m_pUIDamage[5]->Render();
	//				m_pUIDamage[5]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '6')
	//			{
	//				m_pUIDamage[6]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[6]->Update();
	//				m_pUIDamage[6]->Render();
	//				m_pUIDamage[6]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '7')
	//			{
	//				m_pUIDamage[7]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[7]->Update();
	//				m_pUIDamage[7]->Render();
	//				m_pUIDamage[7]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '8')
	//			{
	//				m_pUIDamage[8]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[8]->Update();
	//				m_pUIDamage[8]->Render();
	//				m_pUIDamage[8]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//			else if (damageChar[j] == '9')
	//			{
	//				m_pUIDamage[9]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y , tempPos.z));
	//				m_pUIDamage[9]->Update();
	//				m_pUIDamage[9]->Render();
	//				m_pUIDamage[9]->SetAlpha(m_vecDamage[i].alpha);
	//			}
	//		} 
	//		i++; //위의 조건이 만족되면 i++해라
	//	}
	//	else
	//	{
	//		m_vecDamage.erase(m_vecDamage.begin() + i);
	//	}
	//}
}

void CharacterParant::Controller()
{
	//===============기능키 제어=====================//
	if (INPUT->KeyDown('I'))
	{
		SOUND->Play("인벤_오픈");
		m_pInventory->OpenInventory();
	}
	if (INPUT->KeyDown('P'))
	{
		SOUND->Play("인벤_오픈");
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
		TEXT->Add(to_string(m_pCharacter->GetPosition()->x), pos1.x + 150, pos1.y - 25.0f, 30);
		TEXT->Add(to_string(m_pCharacter->GetPosition()->y), pos1.x + 150, pos1.y - 40.0f, 30);
		TEXT->Add(to_string(m_pCharacter->GetPosition()->z), pos1.x + 150, pos1.y - 55.0f, 30);
		
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
		m_Status->chr.nCurrentStam  -= 2;
	}

	if (m_Status->chr.nCurrentStam <= 0)
	{
		m_eCondition = CHAR_IDLE;
		m_bIsDash = false;
		ChangeAnimation();
		m_Status->chr.nCurrentStam = 1;
	}


	if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT)
	{
		if (m_Status->chr.nCurrentStam <= m_Status->chr.nMaxStam)
		{
			
			if (m_pPet->IsSpawn())
			{
				m_Status->chr.nCurrentStam += 1;
			}
			else
			{
				m_Status->chr.nCurrentStam += 0.1;
			}


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
	
	m_pDamage->AddDamage(hp);


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
	if (!m_bIsSubChr && !m_bGumGang)
	{
		m_bIsUnderAttacked = true;
		m_fGuard = 0.0f;
		if (m_eCondition != CHAR_HIT && m_eCondition != CHAR_ATTACK && m_eCondition != CHAR_SKILL)
		{
			m_eCondition = CHAR_HIT;
			ChangeAnimation();
		}
	
		if (!m_bIsInvincible)
		{
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
		if (m_bIsInvincible && m_bIsUnderAttacked)
		{
			CAMERA->Shake(0.3, 1);
			if (m_eChrType == CHRTYPE_SWORD || m_eChrType == CHRTYPE_MAGIC)
			{
				ST_EFFECT tempEffect1;
				ZeroMemory(&tempEffect1, sizeof(tempEffect1));
				tempEffect1.time = 1;
				tempEffect1.rot = *m_pCharacter->GetRotation();
				//tempEffect1.autoY = true;
				tempEffect1.height = 3.0f;
				tempEffect1.SetAlpha(255, 255, 0);
				tempEffect1.SetScale(1, 1, 1);
				tempEffect1.tex = TEXTUREMANAGER->GetTexture("실드_마법");


				EffectObject* tempEFOBJ1;
				tempEFOBJ1 = new EffectObject;
				D3DXVECTOR3 testSkillpos1 = *m_pCharacter->GetPosition() - m_vfront * 1.0f;
				tempEFOBJ1->Init(tempEffect1, testSkillpos1);
				m_vecEffect.push_back(tempEFOBJ1);
			}

			//가드 이미지 
			if (m_eChrType == CHRTYPE_SWORD)
			{
				ST_EFFECT tempEffect2;
				ZeroMemory(&tempEffect2, sizeof(tempEffect2));
				tempEffect2.time = 1;
				tempEffect2.rot = *m_pCharacter->GetRotation();

				tempEffect2.height = 3.0f;
				tempEffect2.SetAlpha(255, 255, 0);
				tempEffect2.SetScale(0.25, 0.25, 0.25);
				tempEffect2.tex = TEXTUREMANAGER->GetTexture("가드이미지");
				//tempEffect2.autoY = true;

				EffectObject* tempEFOBJ2;
				tempEFOBJ2 = new EffectObject;
				D3DXVECTOR3 testSkillpos2 = *m_pCharacter->GetPosition();
				testSkillpos2.y += 3.0f;
				tempEFOBJ2->Init(tempEffect2, testSkillpos2);
				m_vecEffect.push_back(tempEFOBJ2);
			}
			if (m_eChrType == CHRTYPE_MAGIC)
			{
				ST_EFFECT tempEffect2;
				ZeroMemory(&tempEffect2, sizeof(tempEffect2));
				tempEffect2.time = 1;
				tempEffect2.rot = *m_pCharacter->GetRotation();

				tempEffect2.height = 3.0f;
				tempEffect2.SetAlpha(255, 255, 0);
				tempEffect2.SetScale(0.25, 0.25, 0.25);
				tempEffect2.tex = TEXTUREMANAGER->GetTexture("미스이미지");
				//tempEffect2.autoY = true;

				EffectObject* tempEFOBJ2;
				tempEFOBJ2 = new EffectObject;
				D3DXVECTOR3 testSkillpos2 = *m_pCharacter->GetPosition();
				testSkillpos2.y += 3.0f;
				tempEFOBJ2->Init(tempEffect2, testSkillpos2);
				m_vecEffect.push_back(tempEFOBJ2);
			}
			if (m_eChrType == CHRTYPE_GUN)
			{
				ST_EFFECT tempEffect2;
				ZeroMemory(&tempEffect2, sizeof(tempEffect2));
				tempEffect2.time = 1;
				tempEffect2.rot = *m_pCharacter->GetRotation();

				tempEffect2.height = 3.0f;
				tempEffect2.SetAlpha(255, 255, 0);
				tempEffect2.SetScale(0.25, 0.25, 0.25);
				tempEffect2.tex = TEXTUREMANAGER->GetTexture("회피이미지");
				//tempEffect2.autoY = true;

				EffectObject* tempEFOBJ2;
				tempEFOBJ2 = new EffectObject;
				D3DXVECTOR3 testSkillpos2 = *m_pCharacter->GetPosition();
				testSkillpos2.y += 3.0f;
				tempEFOBJ2->Init(tempEffect2, testSkillpos2);
				m_vecEffect.push_back(tempEFOBJ2);
			}


		}
	}
	if(m_bIsSubChr)
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


void CharacterParant::CountAppearDamage()
{

	//if (m_bIsUnderAttacked)
	//{
	//	m_stDamaged.startDamageTime += TIME->GetElapsedTime();
	//}

	//if (m_stDamaged.startDamageTime < m_stDamaged.endDamageTime && m_bIsUnderAttacked)
	//{
	//	m_pParticle->SetPosition(D3DXVECTOR3(m_pCharacter->GetPosition()->x, m_pCharacter->GetPosition()->y + 1.5f, m_pCharacter->GetPosition()->z));
	//	m_pParticle->TimeReset();
	//}

	//if (m_stDamaged.startDamageTime >= 0.3f)
	//{
	//	m_stDamaged.startDamageTime = 0.0f;
	//	m_bIsUnderAttacked = false;
	//	//m_bIsInvincible = false;
	//}

}

void CharacterParant::SkillIconAlpha()
{
	
}

void CharacterParant::PlayerProgressBar()
{
	float tempF = (float)m_Status->chr.nCurrentHP / m_Status->chr.nMaxHp;
	m_pHPBar->SetScale(D3DXVECTOR3(tempF, 1, 1));
	D3DXVECTOR3 UIPos = D3DXVECTOR3(205, 685, 0);
	m_pHPBar->SetPosition(UIPos);
	m_pHPBar->Update();
	if (!m_pNpc->GetCollision())
	{
		TEXT->Add(to_string(m_Status->chr.nCurrentHP), 300, 700, 20, "나눔명조", 0xFFFFFFFF);
		TEXT->Add("/", 340, 700, 20, "나눔명조", 0xFFFFFFFF);
		TEXT->Add(to_string(m_Status->chr.nMaxHp), 350, 700, 20, "나눔명조", 0xFFFFFFFF);
	}


	float tempS = (float)m_Status->chr.nCurrentStam / m_Status->chr.nMaxStam;
	m_pStaminaBar->SetScale(D3DXVECTOR3(tempS, 1, 1));
	D3DXVECTOR3 StaPos = D3DXVECTOR3(205, 746, 0);
	m_pStaminaBar->SetPosition(StaPos);
	m_pStaminaBar->Update();
	if (!m_pNpc->GetCollision())
	{
		TEXT->Add(to_string((int)m_Status->chr.nCurrentStam), 310, 760, 20, "나눔명조", 0xFFFFFFFF);
		TEXT->Add("/", 340, 760, 20, "나눔명조", 0xFFFFFFFF);
		TEXT->Add(to_string((int)m_Status->chr.nMaxStam), 350, 760, 20, "나눔명조", 0xFFFFFFFF);
	}
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



void CharacterParant::Reset(Map * map, MonsterManager * pMonsterManager, DropManager* Drop, Pet* p)
{	
	m_pSampleMap = map;
	m_pMonsterManager = pMonsterManager;
	m_pDropManager = Drop;
	m_pPet = p;

	D3DXVECTOR3 startPos = map->GetSpawnPlayer();
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos.x, startPos.z), startPos.z));
}

void CharacterParant::SetTarget()
{
	m_nIndex = -1;
	float minLength = 100;
	m_vecTarget.clear();
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//플레이어 포지션 받고 
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//플레이어 각도 받고 
	
	
	
	
	if (m_eNumTarget == NUM_SINGLE)
	{
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
			D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(MonPos - pos));

			if (length <= m_Status->chr.fRange)
			{	
				// 시선
				D3DXVECTOR3 front;
				D3DXMATRIX matY;
				D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
				D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
				D3DXVECTOR3 v0 = front;
				// 대상방향
				D3DXVECTOR3 v1 = MonPos - pos;
				D3DXVec3Normalize(&v1, &v1);
				float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
				if (dot >= cos(m_Status->chr.fScale / 2))
				{
					if (minLength > length)
					{
						m_nIndex = i;
						minLength = length;
					}
				}
			}
		}
	}
	if (m_eNumTarget == NUM_MULTI)
	{
		for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); i++)
		{
			if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn()) continue;
			D3DXVECTOR3 MonPos = *m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition();
			float length = D3DXVec3Length(&(MonPos - pos));

			if (length <= m_Status->chr.fRange)
			{	// 시선
				D3DXVECTOR3 front;
				D3DXMATRIX matY;
				D3DXMatrixRotationY(&matY, m_pCharacter->GetRotation()->y);
				D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, -1), &matY);
				D3DXVECTOR3 v0 = front;
				// 대상방향
				D3DXVECTOR3 v1 = MonPos - pos;
				D3DXVec3Normalize(&v1, &v1);
				float dot = D3DXVec3Dot(&v0, &v1) / D3DXVec3Length(&v0) * D3DXVec3Length(&v1);
				if (dot >= cos(m_Status->chr.fScale / 2))
				{
					m_vecTarget.push_back(i);
				}
			}
		}
	}
}

void CharacterParant::CutScene()
{
	if (m_isCutScene)
	{
		D3DXVECTOR3 tempPos1;
		tempPos1 = *m_pCharacter->GetPosition();
		tempPos1.y += 3;
		D3DXVECTOR2 pos1 = Convert3DTo2D(tempPos1);
		TEXT->Add(to_string(m_Status->chr.nCurrentHP), pos1.x, pos1.y, 30);
		TEXT->Add(to_string(m_Status->chr.nMaxHp), pos1.x, pos1.y - 25.0f, 30);

		TEXT->Add(to_string(m_Status->chr.nCurrentStam), pos1.x + 90, pos1.y, 30);
		TEXT->Add(to_string(m_Status->chr.nMaxStam), pos1.x + 90, pos1.y - 25.0f, 30);
	}
}

void CharacterParant::SetModelAlpha()
{
	if (m_pNpc->GetCollision() || m_bIsUnderAttacked)
	{
		m_pCharacter->SetShaderAlpha(0.5f);
	}
	else
	m_pCharacter->SetShaderAlpha(1.0f);
	
	/*if (m_bIsUnderAttacked)
	{
		m_pCharacter->SetShaderAlpha(0.5f);
	}
	else 
	m_pCharacter->SetShaderAlpha(1.0f);*/

}

void CharacterParant::SetPlayerStatus()
{
	for (int i = 0; i < STAT_END; i++)
	{
		m_bCharStatus[i].ElpTime += TIME->GetElapsedTime();
	}


	if (m_bCharStatus[STAT_FIRE].ElpTime < m_bCharStatus[STAT_FIRE].ApplyTime)
	{
		CalculDamage(1);
	}
	
	
	if (m_bCharStatus[STAT_ICE].ElpTime < m_bCharStatus[STAT_ICE].ApplyTime)
	{
		if (!m_bIceStat)
		{
			m_bIceStat = true;
			m_Status->chr.fSpeed -= 0.2f;
		}
	}
	else m_bIceStat = false;


	if (m_bCharStatus[STAT_STUN].ElpTime < m_bCharStatus[STAT_STUN].ApplyTime)
	{
		if (!m_bIsStun)
		{
			m_bIsStun = true;
		}
	}
	else m_bIsStun = false;
}

void CharacterParant::SkillToolTip(D3DXVECTOR3 pos)
{
	//TEXT->Add(m_pInheritateIco->GetName(),  );

	//// 설명
	//char * desc = _strdup(pItem->GetDesc().c_str());
	//char * tok;
	//char * context;
	//tok = strtok_s(desc, "/", &context);
	//TEXT->Add(tok, pos.x + vItemPos.x, pos.y + (wh.y - 95) * m_fSlotResize, 30 * m_fSlotResize,
	//	"나눔스퀘어 Regular", 0xFFFFFFFF);
	//tok = strtok_s(NULL, "/", &context);
	//if (tok)
	//	TEXT->Add(tok, pos.x + vItemPos.x, pos.y + (wh.y - 50) * m_fSlotResize, 30 * m_fSlotResize,
	//		"나눔스퀘어 Regular", 0xFFFFFFFF);
}

void CharacterParant::SetCameraNormalView()
{
	if (*m_npStage !=3)
	{
		CAMERA->SetCamOffset(D3DXVECTOR3(0, 3, 20));
		CAMERA->SetTargetOffset(D3DXVECTOR3(0, 4, 0));
		CAMERA->SetTarget(m_pCharacter->GetPosition(), m_pCharacter->GetRotation());
	}	
}

void CharacterParant::Guard()
{
	if (m_eCondition == CHAR_GUARD)
	{
		m_bIsInvincible = true;
	}
}

void CharacterParant::Restore()
{

	if (m_pPet->IsSpawn())
	{

		if (INPUT->KeyPress('C'))
		{
			if (m_Status->chr.nCurrentHP < m_Status->chr.nMaxHp)
			{
				m_Status->chr.nCurrentHP += 1;
			}

			if (m_Status->chr.nCurrentHP >= m_Status->chr.nMaxHp)
			{
				m_Status->chr.nCurrentHP = m_Status->chr.nMaxHp;
			}
		}

	}



}

void CharacterParant::SummonPet(PETTYPE pet)
{
	if (m_bPetUnSealed)
	{
		m_pPet->Init(m_pCharacter->GetPosition(), m_pSampleMap, pet);
	}
}

void CharacterParant::AStar()
{
	m_vecFindPath.clear();

	vector<ST_PLAYER_NODE*> closeList;
	vector<ST_PLAYER_NODE*> openList;
	int lastIndex = 0;

	// 네브메시를 노드로 변환
	vector<ST_PLAYER_NODE> vecNode;
	auto vecNavMesh = m_pSampleMap->GetNavMesh();
	for (int i = 0; i < vecNavMesh.size(); i += 3)
	{
		ST_PLAYER_NODE temp;
		ZeroMemory(&temp, sizeof(ST_PLAYER_NODE));
		temp.c.v0 = vecNavMesh[i];
		temp.c.v1 = vecNavMesh[i + 1];
		temp.c.v2 = vecNavMesh[i + 2];
		temp.c.center = (temp.c.v0 + temp.c.v1 + temp.c.v2) / 3.0f;
		vecNode.push_back(temp);
	}

	D3DXVECTOR3 targetCenter;
	bool findTargetCenter = false, findCurrentCell = false;;
	for (int i = 0; i < vecNode.size(); i++)
	{
		// 타겟 셀 중심점
		if (D3DXIntersectTri(&vecNode[i].c.v0, &vecNode[i].c.v1, &vecNode[i].c.v2,
			&(m_pClickPos + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL) && !findTargetCenter)
		{
			targetCenter = (vecNode[i].c.v0 + vecNode[i].c.v1 + vecNode[i].c.v2) / 3.0f;
			findTargetCenter = true;
		}

		// 현재 셀 클로즈 추가
		if (D3DXIntersectTri(&vecNode[i].c.v0, &vecNode[i].c.v1, &vecNode[i].c.v2,
			&(*m_pCharacter->GetPosition() + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL) && !findCurrentCell)
		{
			vecNode[i].isList = true;
			closeList.push_back(&vecNode[i]);
			findCurrentCell = true;
		}

		if (findTargetCenter && findCurrentCell)
			break;
	}

	while (true)
	{
		// 오픈리스트 추가
		if (closeList.size() > 0)
		{
			float cg = closeList[lastIndex]->G;
			ST_PLAYER_CELL cc = closeList[lastIndex]->c;

			// 이웃 셀 위치 계산
			float nl0 = D3DXVec3Length(&(cc.center - (cc.v0 + cc.v1) / 2.0f)) + 0.1;
			float nl1 = D3DXVec3Length(&(cc.center - (cc.v1 + cc.v2) / 2.0f)) + 0.1;
			float nl2 = D3DXVec3Length(&(cc.center - (cc.v2 + cc.v0) / 2.0f)) + 0.1;
			D3DXVECTOR3 n[3], nc;
			D3DXVec3Normalize(&n[0], &(cc.center - cc.v2)); n[0] *= nl0; n[0] += cc.center;
			D3DXVec3Normalize(&n[1], &(cc.center - cc.v0)); n[1] *= nl1; n[1] += cc.center;
			D3DXVec3Normalize(&n[2], &(cc.center - cc.v1)); n[2] *= nl2; n[2] += cc.center;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < vecNode.size(); j++)
				{
					if (D3DXIntersectTri(&vecNode[j].c.v0, &vecNode[j].c.v1, &vecNode[j].c.v2,
						&(n[i] + D3DXVECTOR3(0, 300, 0)), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
					{
						float g = D3DXVec3Length(&(cc.center - vecNode[j].c.center));
						if (!vecNode[j].isList)
						{
							vecNode[j].isList = true;
							vecNode[j].G = cg + g;
							vecNode[j].pParent = closeList[lastIndex];
							openList.push_back(&vecNode[j]);
						}
						else if (cg + g < vecNode[j].G)
						{
							vecNode[j].G = cg + g;
							vecNode[j].pParent = closeList[lastIndex];
						}
					}
				}
			}
		}

		// 오픈리스트 값 계산
		for (int i = 0; i < openList.size(); i++)
		{
			openList[i]->H = D3DXVec3Length(&(openList[i]->c.center - m_pClickPos));
			openList[i]->F = openList[i]->G + openList[i]->H;
		}

		// 클로즈리스트 추가
		if (openList.size() > 0)
		{
			int index = 0;
			int lowest = openList[0]->F;
			for (int i = 0; i < openList.size(); i++)
			{
				if (openList[i]->F < lowest)
				{
					lowest = openList[i]->F;
					index = i;
				}
			}
			closeList.push_back(openList[index]);
			openList.erase(openList.begin() + index);
			lastIndex++;

			if (D3DXVec3Length(&(closeList[lastIndex]->c.center - targetCenter)) < 1)
			{
				ST_PLAYER_NODE * temp = closeList[lastIndex];
				while (temp != NULL)
				{
					m_vecFindPath.push_back(*temp);
					temp = temp->pParent;
				}
				reverse(m_vecFindPath.begin(), m_vecFindPath.end());
				OptimizePath();
				break;
			}
		}
		else
			break;
	}
}

void CharacterParant::OptimizePath()
{
	// 패스 사이드 작업
	auto tempPath = m_vecFindPath;
	m_vecFindPath.clear();
	for (int i = 0; i < tempPath.size() - 1; i++)
	{
		D3DXVECTOR3 s[3];
		s[0] = (tempPath[i].c.v0 + tempPath[i].c.v1) / 2;
		s[1] = (tempPath[i].c.v1 + tempPath[i].c.v2) / 2;
		s[2] = (tempPath[i].c.v2 + tempPath[i].c.v0) / 2;
		int sideIndex = 0;
		for (int j = 0; j < 3; j++)
		{
			if (D3DXVec3Length(&(s[j] - tempPath[i + 1].c.center)) <
				D3DXVec3Length(&(s[sideIndex] - tempPath[i + 1].c.center)))
				sideIndex = j;
		}
		ST_PLAYER_NODE center;
		center.c.center = s[sideIndex];
		m_vecFindPath.push_back(center);
	}
	ST_PLAYER_NODE target;
	target.c = m_stTargetCell;
	m_vecFindPath.push_back(target);
}

void CharacterParant::AStarMove()
{
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();

	if (!m_vecFindPath.empty())
	{
		D3DXVECTOR3 next = m_vecFindPath.front().c.center;
		//bool equalCell = TargetEqualCell();

		float targetRotY;
		/*if (equalCell)
			targetRotY = GetAngle(pos.x, pos.z, m_pClickPos.x, m_pClickPos.z) - D3DX_PI / 2;
		else*/
			targetRotY = GetAngle(pos.x, pos.z, next.x, next.z) - D3DX_PI / 2;

		D3DXVECTOR3 rot = *m_pCharacter->GetRotation();
		if (targetRotY - rot.y > D3DX_PI / 2)
			rot.y += D3DX_PI * 2;
		if (targetRotY - rot.y < -D3DX_PI / 2)
			rot.y -= D3DX_PI * 2;
		rot.y += 0.1 * (targetRotY - rot.y);
		m_pCharacter->SetRotation(rot);

		D3DXVECTOR3 front;
		/*if (equalCell)
			D3DXVec3Normalize(&front, &(m_pClickPos - pos));
		else*/
			D3DXVec3Normalize(&front, &(next - pos));

		if (D3DXVec3Length(&(*m_pCharacter->GetPosition() - m_pClickPos)) > m_fStopDist)
			m_pCharacter->SetPosition(*m_pCharacter->GetPosition() + front * m_Status->chr.fSpeed);
		else
		{
			m_vecFindPath.clear();
			return;
		}

		if (D3DXVec3Length(&(*m_pCharacter->GetPosition() - next)) < 1)
			m_vecFindPath.erase(m_vecFindPath.begin());
	}

	pos = *m_pCharacter->GetPosition();
	float y = m_pSampleMap->GetHeight(pos.x, pos.z);
	if (y > 0)
		m_pCharacter->SetPosition(D3DXVECTOR3(pos.x, y, pos.z));
}

bool CharacterParant::TargetEqualCell()
{
	auto vecNavMesh = m_pSampleMap->GetNavMesh();
	ST_PET_CELL temp;
	for (int i = 0; i < vecNavMesh.size(); i += 3)
	{
		D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
		if (D3DXIntersectTri(&vecNavMesh[i], &vecNavMesh[i + 1], &vecNavMesh[i + 2],
			&D3DXVECTOR3(pos.x, 300, pos.z), &D3DXVECTOR3(0, -1, 0), NULL, NULL, NULL))
		{
			temp.v0 = vecNavMesh[i];
			temp.v1 = vecNavMesh[i + 1];
			temp.v2 = vecNavMesh[i + 2];
			temp.center = (temp.v0 + temp.v1 + temp.v2) / 3.0f;
			break;
		}
	}
	if (D3DXVec3Length(&(temp.center - m_stTargetCell.center)) < 1)
		return true;
	else
		return false;
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
	SAFE_DELETE(m_pParticle5);
	SAFE_DELETE(m_pVelvetFinal);
	for (int i = 0; i < 15; i++)
	{
		SAFE_DELETE(m_pRiahFinal[i]);
	}
	SAFE_RELEASE(m_pUIobj);
	SAFE_RELEASE(m_pHPBar);
	SAFE_RELEASE(m_pStaminaBar);
	SAFE_RELEASE(m_pShieldHp);
	SAFE_RELEASE(m_pChrStat);
	SAFE_RELEASE(m_pInheritateIco);
	SAFE_RELEASE(m_pInheritateIco2);
	SAFE_RELEASE(m_pInheritateIco3);
	SAFE_RELEASE(m_pSkillBar);
	SAFE_RELEASE(m_SkillToolTip);
	SAFE_RELEASE(m_pCombo);

	for (auto e : m_vecEffect)
	{
		SAFE_DELETE(e);
	}
	m_pMonsterManager = NULL; 
	m_pSampleMap = NULL;
	SAFE_DELETE(m_pInventory);
	
}

void CharacterParant::Init(CHRTYPE type, CHARSELECT order)
{	

	m_eChrType = type;
	m_eCharSelect = order;
	


	m_pCharacter->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));
	m_pCharacter->SetRotation(D3DXVECTOR3(0,3.2,0));
	//m_pCharacter->SetShaderRimColor(D3DXVECTOR3(255, 0, 0));
	//m_pCharacter->SetShaderColorOffset(0.5f);
	//m_pCharacter->SetShaderRimPower(1.0f);
	ST_SIZEBOX box;
	box.highX = 30.0f;
	box.highY = 180.0f;
	box.highZ = 30.0f;
	box.lowX = -30.0f;
	box.lowY = 10.0f;
	box.lowZ = -30.0f;


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
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 3, 20));
	CAMERA->SetTargetOffset(D3DXVECTOR3(0, 4, 0));
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
	m_isCutScene = false;
	m_bisMgShield = false;
	m_bIsMeteo = false;
	m_bIsMeteoClick = false;
	m_bIsGunView = false;
	m_bIsMegaCristal = false;
	m_bIsMegaCirstalClick = false;
	m_bSkillUnSealed = false;
	m_bIceStat = false;
	m_bIsStun = false;
	m_bPetUnSealed = false;
	m_bGumGang = false;

	m_fStamina = 10.0f;
	m_nDamage = 0;
	m_fDamageCount = 0.0;
	m_fDamageAngle = 0.0f;
	m_fElpTime = 0.0f;
	m_fPrevTime = 0.0f;
	m_nDamageCount = 0;
	m_fModelAlpha = 0.0f;
	m_fDot = 0.0f;
	m_fFireCount = 1.0f;
	m_fGuard = 0.0f;

	m_fEffectInterval = 0.1f;

	m_stDamaged.startDamageTime = 0.0f;
	m_stDamaged.endDamageTime = 1.0f;

	m_nAppear = 0;

	//포트레이트 UI
	if(m_pUIobj == NULL) m_pUIobj = new UIObject;

	//스테이터스
	if (m_pChrStat == NULL) m_pChrStat = new UIObject;

	//고유스킬 아이콘
	if(m_pInheritateIco == NULL) m_pInheritateIco = new UIObject;
	if (m_pInheritateIco2 == NULL) m_pInheritateIco2 = new UIObject;
	if (m_pInheritateIco3 == NULL) m_pInheritateIco3 = new UIObject;

	//스킬바 이미지
	if (m_pSkillBar == NULL) m_pSkillBar = new UIObject;

	if (m_pAimLine == NULL) m_pAimLine = new UIObject;

	//대화창 이미지
	if (m_pTalkBar == NULL) m_pTalkBar = new UIObject;
	
	if (m_SkillToolTip == NULL) m_SkillToolTip = new UIObject;

	if (m_pCombo == NULL) m_pCombo = new UIObject;


	//데미지 
	m_pDamage = new DamageUI;
	m_pDamage->Setup(true);
	
	//프로그래스바
	if (m_pHPBar == NULL)
	{
		m_pHPBar = new UIObject;
		m_pHPBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_체력"));
		D3DXVECTOR3 UIPos = D3DXVECTOR3(1350, 520, 0);
		m_pHPBar->SetPosition(UIPos);
	}


	if (m_pStaminaBar == NULL)
	{
		m_pStaminaBar = new UIObject;
		m_pStaminaBar->SetTexture(TEXTUREMANAGER->GetTexture("캐릭터_스테미너"));
		D3DXVECTOR3 StaPos = D3DXVECTOR3(1350, 535, 0);
		m_pStaminaBar->SetPosition(StaPos);
	}

	m_pParticle = PARTICLE->GetParticle("ATTACK"); //피격시 출혈파티클
	m_pParticle2 = PARTICLE->GetParticle("Die");  //죽을때 나오는 파티클
	m_pParticle3 = PARTICLE->GetParticle("Potal"); //텔레포트 위치 나타내는 파티클
	m_pParticle4 = PARTICLE->GetParticle("teleport"); //텔레포트 끝나고 아래에서 피어오르는 파티클
	m_pParticle5 = PARTICLE->GetParticle("Potal"); //메가크리스탈 파티클
	m_pVelvetFinal = PARTICLE->GetParticle("벨벳_궁극기");
	for (int i = 0; i < 15; i++)
	{
		m_pRiahFinal[i] = PARTICLE->GetParticle("리아_궁극기");
	}
	m_pParticle3->SetPosition(D3DXVECTOR3(m_pCharacter->GetPosition()->x, m_pCharacter->GetPosition()->y, m_pCharacter->GetPosition()->z + 5.0f));
	m_pTalkBar->SetTexture(TEXTUREMANAGER->GetTexture("대화창"));
	m_pTalkBar->SetPosition(D3DXVECTOR3(0, 545, 0));

	m_pShieldChr = NULL;

	

}

void CharacterParant::Update()
{
	if (m_bIsPotal)
	{
		m_pParticle3->Update();
	}

	if (m_bIsUnderAttacked)
	{
		m_fGuard += TIME->GetElapsedTime();
		//if (m_eChrType == CHRTYPE_GUN || m_eChrType == CHRTYPE_MAGIC || m_eChrType == CHRTYPE_SWORD)
	//	{
			if (m_fGuard > 1.0)
			{
				m_bIsUnderAttacked = false;
				m_bIsInvincible = false;
			}
	//	}
	/*	if (m_eChrType == CHRTYPE_FIST)
		{
			if (m_fGuard > 5.0)
			{
				m_bIsUnderAttacked = false;
				m_bIsInvincible = false;
			}
		}*/

	}
	Restore();
	Guard();


	if (m_bPetUnSealed)
	{
		m_pPet->Update();
	}

	SetModelAlpha();
}	



void CharacterParant::Render()
{
	m_pParticle->Render();
	m_pParticle2->Render();
	if (m_bIsPotal) m_pParticle3->Render();
	if (m_bIsMeteo) m_pParticle3->Render();
	if (m_bIsMegaCristal) m_pParticle3->Render();
	m_pParticle4->Render();

	for (int i = 0; i < m_vecEffect.size(); i++)
	{
		m_vecEffect[i]->Render();
	}

	if (!m_pNpc->GetCollision())m_pChrStat->Render();

	D3DXVECTOR3 temp = *m_pCharacter->GetPosition();
	temp.y += 0.4f;

	m_pDamage->Render(temp);

	if (m_bPetUnSealed)
	{
		m_pPet->Render();
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
		//	m_bIsUnderAttacked = false;
		//	m_pCharacter->SetShaderAlpha(1.0f);
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
	case CHAR_SKILL2:
			m_pCharacter->SetAnimation("SKILL2");
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
	case CHAR_INHERENT1:
		m_pCharacter->SetAnimation("ATTACK");
		break;
	case CHAR_INHERENT2:
		m_pCharacter->SetAnimation("ATTACK");
		break;
	case CHAR_INHERENT3:
		m_pCharacter->SetAnimation("ATTACK");
		break;
	case CHAR_TALK:
		m_pCharacter->SetBlendAnimation("IDLE");
	//	m_pCharacter->SetShaderAlpha(0.5f);
		break;
	case CHAR_GUARD:
		m_pCharacter->SetAnimation("GUARD");
		break;
	case CHAR_NONE :
		break;
	}
}
