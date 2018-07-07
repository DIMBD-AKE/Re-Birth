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
	//특정 키를 누르면 아이템 클래스의 skill을 실행한다. 
}

void CharacterParant::Move()
{
	Debug();
	Attack();
	//포트레이트
	//m_pUIobj->Update();

	//전후좌우 점프 움직임


	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();
	//if (INPUT->KeyPress(VK_LEFT))	rot.y -= 0.05;
	//if (INPUT->KeyPress(VK_RIGHT))	rot.y += 0.05;

	

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
	D3DXVECTOR3 vPos = *m_pCharacter->GetPosition();
	if (m_eCondition == CHAR_RUN_FRONT)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * m_Status->chr.fSpeed, pos.z - m_vfront.z * m_Status->chr.fSpeed);
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos - m_vfront * m_Status->chr.fSpeed);
		}
		else
		{
			return;
		}
	}
	else if (m_eCondition == CHAR_RUN_BACK)
	{
		float height = m_pSampleMap->GetHeight(pos.x - m_vfront.x * (m_Status->chr.fSpeed-0.2f), pos.z - m_vfront.z * (m_Status->chr.fSpeed-0.2f));
		if (height >= 0)
		{
			pos.y = height;
			m_pCharacter->SetPosition(pos + m_vfront * (m_Status->chr.fSpeed-0.2f));
		}
		else
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
		else
		{

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

		}
	}
	ControllStamina();

	
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
		D3DXVECTOR3 tempPos; 
		tempPos = *m_pCharacter->GetPosition();
		tempPos.y += 3;
		D3DXVECTOR2 pos =  Util::Convert3DTo2D(tempPos);
		TEXT->Add(to_string(m_Status->chr.nCurrentStam), pos.x, pos.y, 30);
		TEXT->Add(to_string(m_Status->chr.nCurrentHP), 300, 300, 30);

	//	CAMERA->SetMode(CAMERA_FREE);
	}
}

void CharacterParant::CheckDirection()
{

}

void CharacterParant::ControllStamina()
{

	if (m_eCondition == CHAR_DASH_FRONT || m_eCondition == CHAR_DASH_BACK)
	{
		m_Status->chr.nCurrentStam -= 1;
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

void CharacterParant::UnderAttacked()
{
	if (INPUT->KeyDown('Z'))
	{
		m_Status->chr.nCurrentHP -= 50;
	}
		if (m_Status->chr.nCurrentHP <= 0 && !m_bIsDead)
		{
			m_bIsDead = true;
			m_eCondition = CHAR_DIE;
			ChangeAnimation();
		}
}

void CharacterParant::SetCurrentHP(int hp)
{
	m_Status->chr.nCurrentHP -= hp;
	
	if (m_Status->chr.nCurrentHP <= 0 && !m_bIsDead)
	{
		m_bIsDead = true;
		m_eCondition = CHAR_DIE;
		ChangeAnimation();
	}
}



void CharacterParant::CalculDamage(float damage)
{
	float totalRate =
		m_Status->chr.fPhyRate +
		m_Status->chr.fMagicRate +
		m_Status->chr.fCheRate;

	float totalDamage = totalRate * m_Status->chr.nDef;

	totalDamage = round(totalDamage);

	SetCurrentHP(totalDamage);
}

void CharacterParant::Attack()
{	
	D3DXVECTOR3 pos = *m_pCharacter->GetPosition();														//플레이어 포지션 받고 
	D3DXVECTOR3 rot = *m_pCharacter->GetRotation();														//플레이어 각도 받고 
	

	for (int i = 0; i < m_pMonsterManager->GetMonsterVector().size(); ++i)
	{											
		if (m_pMonsterManager->GetMonsterVector()[i]->GetIsResPawn())continue;								//리젠할때는 건드리지 않고 
		else
		{
			float radius = m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetBoundSphere().radius;		//몬스터의 바운드 스페어의 반지름 받고 
			D3DXVECTOR3 mosPos = *(m_pMonsterManager->GetMonsterVector()[i]->GetModel()->GetPosition());		//몬스터 포지션 받고 
			float distance = D3DXVec3Length(&(mosPos - pos));												//거리계산으로 몬스터 위치와 플레이어 포지션 뺀 값을 저장하는 변수만들고
			if (distance - radius > m_fRange) continue;														//거리랑 반지름을 뺀 값이 공격 길이보다 크면 처리하지 않고
			else
			{
				D3DXVECTOR3 delta = mosPos - pos;															//델타 변수는 몬스터 포지션과 내 포지션을 뺀 벡터값으로 두고
				if(atan2(delta.x, delta.z)>m_fScale) continue;												//아탄2의 결과 각도보다 fScale값이 크면 그냥 넘기고 
						
				int Atk = m_Status->chr.nAtk;																//플레이어 공격력 담는 변수인데 이건 지금 필요 없고 
				m_pMonsterManager->GetMonsterVector()[i]->SetCurrentHP(100);									//그냥 위의 조건을 다 만족하면 지금 내 앞에 있는 몬스터 체력0으로 만들어버려랏
				//pMonsterManager->GetMonsterVector()[i]->CalculDamage(,);
				//m_pMonsterManager->GetMonsterVector()[i]->
			}
		}
	}
}

CharacterParant::CharacterParant()
{
	m_Status = new STATUS;
	MODELMANAGER->AddModel("아린", "Model/Character/Arin/", "Arin.x", MODELTYPE_X);
	MODELMANAGER->AddModel("아카날", "Model/Character/Aknal/", "Aknal.x", MODELTYPE_X);
	MODELMANAGER->AddModel("헤스티아", "Model/Character/Hestia/", "Hestia.x", MODELTYPE_X);
	MODELMANAGER->AddModel("메그너스", "Model/Character/Meguns/", "Meguns.x", MODELTYPE_X);
	MODELMANAGER->AddModel("리아", "Model/Character/Riah/", "Riah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("스카디", "Model/Character/Skadi/", "Skadi.x", MODELTYPE_X);
	MODELMANAGER->AddModel("베카", "Model/Character/Beakah/", "Beakah.x", MODELTYPE_X);
	MODELMANAGER->AddModel("벨벳", "Model/Character/Velvet/", "Velvet.x", MODELTYPE_X);
	TEXTUREMANAGER->AddTexture("아카날_사진", "Model/Character/Portrait/Portrait_PC_Aknal_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("아린_사진", "Model/Character/Portrait/Portrait_PC_Arin_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("베카_사진", "Model/Character/Portrait/Portrait_PC_BeakAh_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("헤스티아_사진", "Model/Character/Portrait/Portrait_PC_Hestia_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("메그너스_사진", "Model/Character/Portrait/Portrait_Pc_Magnus_Icon.tga");
	TEXTUREMANAGER->AddTexture("리아_사진", "Model/Character/Portrait/Portrait_PC_Riah_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("스카디_사진", "Model/Character/Portrait/Portrait_PC_Skadi_S_Icon.tga");
	TEXTUREMANAGER->AddTexture("벨벳_사진", "Model/Character/Portrait/velvet.png");

}


CharacterParant::~CharacterParant()
{
	SAFE_DELETE(m_pCharacter);
}

void CharacterParant::Init(Map* map, CHARSELECT order, MonsterManager* pMonsterManager)
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
	D3DXVECTOR3 startPos = m_pSampleMap->GetSpawnPlayer();
	startPos.y = 300.0f;
	m_pCharacter->SetPosition(D3DXVECTOR3(startPos.x, m_pSampleMap->GetHeight(startPos.x, startPos.z), startPos.z));

	//인벤토리
	m_pInventory = new Inventory;
	m_pInventory->CreateInventory(5,3);
	m_pInventory->SetStatus(m_Status);

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
	m_fStamina = 10.0f;
	m_fRange = 30.0f;
	m_fScale = 30.0f;


	//포트레이트 UI
	m_pUIobj = new UIObject;



}



void CharacterParant::Render()
{
	//포트레이트 
	//m_pUIobj->Render();
}

void CharacterParant::KeyControl()
{
	//앞으로 달리기
	if (INPUT->KeyDown('W'))
	{
		if (m_eCondition == CHAR_IDLE)
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
	//뒤로 달리기
	if (INPUT->KeyDown('S'))
	{
		if (m_eCondition == CHAR_IDLE)
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
	//앞으로 대쉬
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
	//뒤로 대쉬
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

	//일반공격
	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_ATTACK;
			ChangeAnimation();
		}
	}

	//스킬공격
	if (INPUT->KeyDown('K'))
	{
		if (m_eCondition == CHAR_IDLE || m_eCondition == CHAR_RUN_FRONT || m_eCondition == CHAR_RUN_BACK)
		{
			m_eCondition = CHAR_SKILL;
			ChangeAnimation();
		}
	}

	//공격상태에서 애니메이션 한바퀴 돌린후 대기상태로 돌려줌
	if (m_pCharacter->IsAnimationEnd()&& m_eCondition == CHAR_ATTACK)
	{
  		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	//스킬상태에서 애니메이션 한바퀴 돌린후 대기상태로 돌려줌
	if (m_pCharacter->IsAnimationEnd() && m_eCondition == CHAR_SKILL)
	{
		m_eCondition = CHAR_IDLE;
		ChangeAnimation();
	}
	
	//대쉬일때 애니메이션 스피드 제어
	if (m_bIsDash)
	{
		m_pCharacter->SetAnimationSpeed(5.0f);
	}
	else
	{
		m_pCharacter->SetAnimationSpeed(1.0f);
	}

	//끄앙 주금
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
		break;
	case CHAR_DASH_FRONT:
		m_pCharacter->SetAnimation("RUN");
	
		break;
	case CHAR_DASH_BACK:
		m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_RUN_FRONT:
			m_pCharacter->SetAnimation("RUN");
		break;
	case CHAR_RUN_BACK:
		m_pCharacter->SetAnimation("RUN");
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
