#include "../stdafx.h"
#include "DamageUI.h"



DamageUI::DamageUI()
{
}


DamageUI::~DamageUI()
{
}

void DamageUI::Setup(bool IsPlayer)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pUIDamage[i] == NULL) m_pUIDamage[i] = new UIObject;
	}

	if (IsPlayer)
	{
		
		for (int i = 0; i < 10; i++)
		{
			string tempStr = "숫자";
			char tempChar[10];
			sprintf_s(tempChar, sizeof(tempChar), "%d", i);

			tempStr += tempChar;
			m_pUIDamage[i]->SetTexture(TEXTUREMANAGER->GetTexture(tempStr));
		}
		//m_pUIDamage[0]->SetTexture(TEXTUREMANAGER->GetTexture("숫자0"));
		//m_pUIDamage[1]->SetTexture(TEXTUREMANAGER->GetTexture("숫자1"));
		//m_pUIDamage[2]->SetTexture(TEXTUREMANAGER->GetTexture("숫자2"));
		//m_pUIDamage[3]->SetTexture(TEXTUREMANAGER->GetTexture("숫자3"));
		//m_pUIDamage[4]->SetTexture(TEXTUREMANAGER->GetTexture("숫자4"));
		//m_pUIDamage[5]->SetTexture(TEXTUREMANAGER->GetTexture("숫자5"));
		//m_pUIDamage[6]->SetTexture(TEXTUREMANAGER->GetTexture("숫자6"));
		//m_pUIDamage[7]->SetTexture(TEXTUREMANAGER->GetTexture("숫자7"));
		//m_pUIDamage[8]->SetTexture(TEXTUREMANAGER->GetTexture("숫자8"));
		//m_pUIDamage[9]->SetTexture(TEXTUREMANAGER->GetTexture("숫자9"));
	}

}

void DamageUI::Update(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 tempPos;


	//TODO : 데미지를 벡터에 담아서 [순차적으로] 출력하고 지우고 하는걸 생각해보자. 동시에 데미지가 들어오는데 지금은 하나씩만 띄우고 있음.

	char damageChar[16];

	for (int i = 0; i < m_vecDamage.size();)
	{
		sprintf_s(damageChar, 16, "%d", m_vecDamage[i].Damage);			//sprintf로 숫자를 문자화

		m_vecDamage[i].time += TIME->GetElapsedTime();		//일랩스타임을 더해줘서 시간제어 시작시간에 계속 더해서 엔드타임이 되면. 이런식으로 조건문 제어

		tempPos = pos;

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
			m_vecDamage[i].alpha -= 3.0f;
			for (int j = 0; j < strlen(damageChar); j++)
			{
				if (damageChar[j] == '0')
				{
					m_pUIDamage[0]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[0]->Update();
					m_pUIDamage[0]->Render();
					m_pUIDamage[0]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '1')
				{
					m_pUIDamage[1]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[1]->Update();
					m_pUIDamage[1]->Render();
					m_pUIDamage[1]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '2')
				{
					m_pUIDamage[2]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[2]->Update();
					m_pUIDamage[2]->Render();
					m_pUIDamage[2]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '3')
				{
					m_pUIDamage[3]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[3]->Update();
					m_pUIDamage[3]->Render();
					m_pUIDamage[3]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '4')
				{
					m_pUIDamage[4]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[4]->Update();
					m_pUIDamage[4]->Render();
					m_pUIDamage[4]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '5')
				{
					m_pUIDamage[5]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[5]->Update();
					m_pUIDamage[5]->Render();
					m_pUIDamage[5]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '6')
				{
					m_pUIDamage[6]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[6]->Update();
					m_pUIDamage[6]->Render();
					m_pUIDamage[6]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '7')
				{
					m_pUIDamage[7]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[7]->Update();
					m_pUIDamage[7]->Render();
					m_pUIDamage[7]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '8')
				{
					m_pUIDamage[8]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
					m_pUIDamage[8]->Update();
					m_pUIDamage[8]->Render();
					m_pUIDamage[8]->SetAlpha(m_vecDamage[i].alpha);
				}
				else if (damageChar[j] == '9')
				{
					m_pUIDamage[9]->SetPosition(D3DXVECTOR3(tempPos.x + 30 * j, tempPos.y, tempPos.z));
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

void DamageUI::Render()
{
}

void DamageUI::AddDamage(int damage, float angle, float time, float endtime, float alpha, float x)
{
	ST_DAMAGETEXT tempDMGTEXT;
	tempDMGTEXT.Damage = damage;
	tempDMGTEXT.time = time;
	tempDMGTEXT.endTime = endtime;
	tempDMGTEXT.angle = angle;
	tempDMGTEXT.alpha = alpha;
	tempDMGTEXT.x = x;
	m_vecDamage.push_back(tempDMGTEXT);

}
