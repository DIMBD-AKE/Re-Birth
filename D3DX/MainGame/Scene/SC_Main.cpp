#include "../../stdafx.h"
#include "SC_Main.h"
#include "../Character/CharacterParant.h"
#include "../Character/Character_Gun.h"
#include "../Character/Character_Magic.h"
#include "../Character/Character_Sword.h"
#include "../Character/Character_fist.h"
#include "../Item/ItemManager.h"
#include <algorithm>


SC_Main::SC_Main()
{
}


SC_Main::~SC_Main()
{
}

void SC_Main::OnClick(UIObject * pSender)
{
	if (m_eState == MS_TITLE)
	{
		if (pSender->GetName().compare("Character Select") == 0)
			m_eState = MS_PORTRAIT;

		if (pSender->GetName().compare("Option") == 0)
			m_eState = MS_OPTION;

		if (pSender->GetName().compare("Ranking") == 0)
		{
			m_eState = MS_RANKING;
			CalcRank();
		}
	}

	if (pSender->GetName().compare("Start") == 0)
	{
		/*SCENE->ChangeScene("Test");
		return;*/

		SOUND->Stop("Main Theme");
		SCENE->ChangeScene("Game", false);
		CharacterParant * character = NULL;
		if (m_sSelect.compare("파이란") == 0)
		{
			character = new Character_fist;
			character->Init(CHRTYPE_FIST, CHAR_ONE);
		}
		if (m_sSelect.compare("아카날") == 0)
		{
			character = new Character_Magic;
			character->Init(CHRTYPE_MAGIC, CHAR_ONE);
		}
		if (m_sSelect.compare("헤스티아") == 0)
		{
			character = new Character_Magic;
			character->Init(CHRTYPE_MAGIC, CHAR_TWO);
		}
		if (m_sSelect.compare("베카") == 0)
		{
			character = new Character_Sword;
			character->Init(CHRTYPE_SWORD, CHAR_ONE);
		}
		if (m_sSelect.compare("리아") == 0)
		{
			character = new Character_Sword;
			character->Init(CHRTYPE_SWORD, CHAR_TWO);
		}
		if (m_sSelect.compare("벨벳") == 0)
		{
			character = new Character_Sword;
			character->Init(CHRTYPE_SWORD, CHAR_THREE);
		}
		if (m_sSelect.compare("메그너스") == 0)
		{
			character = new Character_Gun;
			character->Init(CHRTYPE_GUN, CHAR_ONE);
		}
		if (m_sSelect.compare("스카디") == 0)
		{
			character = new Character_Gun;
			character->Init(CHRTYPE_GUN, CHAR_TWO);
		}
		SCENE->GetCurrentScene()->SetData(0, character);
		int stage = 0;
		SCENE->GetCurrentScene()->SetData(1, &stage);
		float time = 0;
		SCENE->GetCurrentScene()->SetData(2, &time);
		SCENE->GetCurrentScene()->SetData(3, &m_sSelect);
		SCENE->GetCurrentScene()->Init();
	}

	if (pSender->GetName().compare("Character Select") &&
		pSender->GetName().compare("Start") &&
		m_eState == MS_PORTRAIT)
	{
		m_sSelect = pSender->GetName();
		MakeModel();
	}

	if (m_eState == MS_OPTION)
	{
		for (int i = 0; i < 20; i++)
		{
			if (pSender->GetName().compare("Volume " + to_string(i)) == 0)
			{
				for (int j = 0; j < 20; j++)
				{
					if (j <= i)
						m_pVolume->Find("Volume " + to_string(j))->SetColor(D3DXVECTOR3(255, 255, 255));
					else
						m_pVolume->Find("Volume " + to_string(j))->SetColor(D3DXVECTOR3(128, 128, 128));
				}

				SOUND->Stop("Main Theme");
				VOLUME = i / (float)19;
				SOUND->Play("Main Theme", VOLUME);
			}
		}
	}
}

void SC_Main::OnOver(UIObject * pSender)
{
	if (pSender->GetName().compare("Character Select") &&
		pSender->GetName().compare("Background") && 
		pSender->GetName().compare("Start") &&
		pSender->GetName().compare("Option") &&
		pSender->GetName().compare("Ranking") &&
		m_eState == MS_PORTRAIT)
	{
		m_pChrOver->SetPosition(pSender->GetPosition() - D3DXVECTOR3(6, 6, 0));
		m_pChrOver->SetScale(pSender->GetScale());
		m_pSelect->SetScale(pSender->GetScale());
		m_isPortrait = true;
	}
}

void SC_Main::OnExit(UIObject * pSender)
{
	if (pSender->GetName().compare("Character Select") && 
		pSender->GetName().compare("Background") &&
		pSender->GetName().compare("Start") &&
		pSender->GetName().compare("Option") &&
		pSender->GetName().compare("Ranking") &&
		m_eState == MS_PORTRAIT)
		m_isPortrait = false;
}

void SC_Main::Release()
{
	SAFE_RELEASE(m_pUI);
	SAFE_RELEASE(m_pPortrait);
	SAFE_RELEASE(m_pSelect);
	SAFE_RELEASE(m_pChrOver);
	SAFE_RELEASE(m_pVolume);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pContext);
}

void SC_Main::Init()
{
	g_clearColor = 0xFF000000;
	SOUND->Play("Main Theme", VOLUME);

	m_eState = MS_TITLE;
	m_isPortrait = false;
	m_sSelect = "";
	m_pModel = NULL;

	m_pUI = new UIObject;
	m_pUI->SetPosition(D3DXVECTOR3(0, 0, 1));
	m_pUI->SetTexture(TEXTUREMANAGER->GetTexture("Main Background"));
	m_pUI->SetName("Background");
	
	UIObject * child = new UIObject;
	child->SetPosition(D3DXVECTOR3(580, 351, 0));
	child->SetTexture(TEXTUREMANAGER->GetTexture("Main Button"));
	child->SetName("Character Select");
	child->SetFunction(this);
	m_pUI->AddChild(child);

	child = new UIObject;
	child->SetPosition(D3DXVECTOR3(580, 450, 0));
	child->SetTexture(TEXTUREMANAGER->GetTexture("Main Button"));
	child->SetName("Option");
	child->SetFunction(this);
	m_pUI->AddChild(child);

	child = new UIObject;
	child->SetPosition(D3DXVECTOR3(580, 550, 0));
	child->SetTexture(TEXTUREMANAGER->GetTexture("Main Button"));
	child->SetName("Ranking");
	child->SetFunction(this);
	m_pUI->AddChild(child);

	m_pStart = new UIObject;
	m_pStart->SetPosition(D3DXVECTOR3(630, 650, 0));
	m_pStart->SetTexture(TEXTUREMANAGER->GetTexture("Main Button"));
	m_pStart->SetScale(D3DXVECTOR3(0.8, 0.8, 1));
	m_pStart->SetName("Start");
	m_pStart->SetFunction(this);

	m_pSelect = new UIObject;
	m_pSelect->SetName("Select");
	m_pSelect->SetTexture(TEXTUREMANAGER->GetTexture("Main Chr Select"));

	m_pPortrait = new UIObject;
	m_pPortrait->SetName("Root");
	m_pPortrait->SetTexture(TEXTUREMANAGER->GetTexture("Character Background"));

	m_pChrOver = new UIObject;
	m_pChrOver->SetName("Over");
	m_pChrOver->SetTexture(TEXTUREMANAGER->GetTexture("Character Chr Over"));

	child = new UIObject;
	child->SetFunction(this);
	m_pPortrait->AddChild(child);

	m_pContext = new Dialogue;
	m_pContext->Init(D3DXVECTOR2(550, 280), 30, "나눔명조", 0.05, 0xFFFFFFFF);
	
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			int index = y * 2 + x;
			D3DXVECTOR3 pos = D3DXVECTOR3(70, 140, 0);
			pos.x += x * 150;
			pos.y += y * 150;

			child = new UIObject;
			child->SetPosition(pos);
			child->SetFunction(this);
			child->SetScale(D3DXVECTOR3(0.5, 0.5, 1));

			if (index == 0)
			{
				child->SetName("아카날");
				child->SetTexture(TEXTUREMANAGER->GetTexture("아카날_사진"));
				m_pContext->AddText("아카날 - 마법사\n\n일러는 여자같은데 모델은 남자다.");
			}
			if (index == 1)
			{
				child->SetName("파이란");
				child->SetTexture(TEXTUREMANAGER->GetTexture("파이란_사진"));
				m_pContext->AddText("파이란 - 권사\n\n나도 바운딩스페어쓰고싶당\n바우우우우우우운딩스페어!!!!!!!\n\n바운딩!!!스페어!!!!!");
			}
			if (index == 2)
			{
				child->SetName("베카");
				child->SetTexture(TEXTUREMANAGER->GetTexture("베카_사진"));
				m_pContext->AddText("베카 - 검사\n\n크으...\n??? : 드림뽕에 취한다.");
			}
			if (index == 3)
			{
				child->SetName("헤스티아");
				child->SetTexture(TEXTUREMANAGER->GetTexture("헤스티아_사진"));
				m_pContext->AddText("헤스티아 - 마법사\n\n모자를 쓰고있다.\n마법사다.\n..");
			}
			if (index == 4)
			{
				child->SetName("메그너스");
				child->SetTexture(TEXTUREMANAGER->GetTexture("메그너스_사진"));
				m_pContext->AddText("메그너스 - 총\n\n남캐 그 자체다\n맘에 안들지만 평타가 쓸만하니\n넘어가도록 하자.");
			}
			if (index == 5)
			{
				child->SetName("리아");
				child->SetTexture(TEXTUREMANAGER->GetTexture("리아_사진"));
				m_pContext->AddText("리아 - 검사\n\n안경을 쓰고있다.\n테스트용으로 꽤 쓰이는것 같다.");
			}
			if (index == 6)
			{
				child->SetName("스카디");
				child->SetTexture(TEXTUREMANAGER->GetTexture("스카디_사진"));
				m_pContext->AddText("스카디 - 궁수\n\n크으...");
			}
			if (index == 7)
			{
				child->SetName("벨벳");
				child->SetTexture(TEXTUREMANAGER->GetTexture("벨벳_사진"));
				m_pContext->AddText("벨벳 - 근접\n\n왠지 모르게 마음에 드는 캐릭터다.\n'ㅅ'");
			}
			
			m_pPortrait->AddChild(child);
		}
	}

	m_pVolume = new UIObject;
	m_pVolume->SetName("Root");
	m_pVolume->SetPosition(D3DXVECTOR3(520, 270, 0));
	for (size_t i = 0; i < 20; i++)
	{
		child = new UIObject;
		child->SetName("Volume " + to_string(i));
		child->SetPosition(D3DXVECTOR3(i * 24, 0, 0));
		child->SetTexture(TEXTUREMANAGER->GetTexture("Option Volume"));
		child->SetFunction(this);
		if (VOLUME * 19 < i)
			child->SetColor(D3DXVECTOR3(128, 128, 128));
		m_pVolume->AddChild(child);
	}
}

void SC_Main::Update()
{
	m_pUI->Update();

	if (m_eState == MS_PORTRAIT)
		m_pPortrait->Update();

	if (m_eState == MS_PORTRAIT && m_sSelect.size() > 0)
	{
		m_pSelect->SetPosition(m_pPortrait->Find(m_sSelect)->GetPosition());
		m_pSelect->Update();
		m_pContext->Update();
		m_pStart->Update();
		TEXT->Add("게임시작", 720, 675, 30, "나눔명조", 0xFFFFFFFF);
	}

	m_pChrOver->Update();

	if (m_eState == MS_TITLE)
	{
		D3DXVECTOR2 mouse = D3DXVECTOR2(MOUSE_POS.x, MOUSE_POS.y);
		m_fElapse += 0.05;
		int alpha = sin(m_fElapse) * 30 + 180;
		m_pUI->Find("Character Select")->SetAlpha(alpha);
		m_pUI->Find("Option")->SetAlpha(alpha);
		m_pUI->Find("Ranking")->SetAlpha(alpha);
		TEXT->Add("시작", 724, 382, 40, "나눔명조", D3DCOLOR_ARGB(alpha, 255, 255, 255));
		TEXT->Add("설정", 724, 482, 40, "나눔명조", D3DCOLOR_ARGB(alpha, 255, 255, 255));
		TEXT->Add("랭킹", 724, 582, 40, "나눔명조", D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}

	if (m_eState == MS_OPTION)
	{
		TEXT->Add("설정", 724, 50, 40, "나눔명조", 0xFFFFFFFF);
		TEXT->Add("볼륨", 724, 200, 40, "나눔명조", 0xFFFFFFFF);
		m_pVolume->Update();
	}

	if (m_eState == MS_RANKING)
		ShowRank();

	if (INPUT->KeyDown(VK_BACK))
		m_eState = MS_TITLE;

	if (m_pModel)
	{
		if (INPUT->KeyPress('A')) m_pModel->GetRotation()->y -= 0.1;
		if (INPUT->KeyPress('D')) m_pModel->GetRotation()->y += 0.1;
		m_pModel->World();
	}
}

void SC_Main::Render()
{
	if (m_eState == MS_TITLE)
		m_pUI->Render();

	if (m_eState == MS_OPTION)
	{
		m_pVolume->Render();
	}

	if (m_eState == MS_PORTRAIT)
	{
		m_pPortrait->Render();

		if (m_sSelect.size() > 0)
			m_pSelect->Render();

		if (m_isPortrait)
			m_pChrOver->Render();

		m_pStart->Render();

		if (m_pModel)
		{
			if (m_pModel->IsAnimationEnd())
				m_pModel->SetAnimation("IDLE");
			m_pModel->Render();
		}
	}
}

void SC_Main::MakeModel()
{
	CAMERA->SetMode(CAMERA_FOLLOW_HOLD);
	CAMERA->SetTarget(&m_vPos, &m_vPos);
	CAMERA->SetTargetOffset(D3DXVECTOR3(-5, 3, 0));
	CAMERA->SetCamOffset(D3DXVECTOR3(0, 0, 0));

	SAFE_DELETE(m_pModel);
	m_pModel = MODELMANAGER->GetModel(m_sSelect, MODELTYPE_X);
	m_pModel->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_pModel->SetAnimation("BattleReady");
	m_pModel->SetScale(D3DXVECTOR3(0.025, 0.025, 0.025));
	m_pContext->SetIndex(GetIndex());
}

int SC_Main::GetIndex()
{
	if (m_sSelect.compare("아카날") == 0) return 0;
	if (m_sSelect.compare("파이란") == 0) return 1;
	if (m_sSelect.compare("베카") == 0) return 2;
	if (m_sSelect.compare("헤스티아") == 0) return 3;
	if (m_sSelect.compare("메그너스") == 0) return 4;
	if (m_sSelect.compare("리아") == 0) return 5;
	if (m_sSelect.compare("스카디") == 0) return 6;
	if (m_sSelect.compare("벨벳") == 0) return 7;
	return -1;
}

void SC_Main::ShowRank()
{
	TEXT->Add("랭킹", 724, 50, 40, "나눔명조", 0xFFFFFFFF);
	TEXT->Add("캐릭터", 415, 150, 36, "나눔명조", 0xFFFFFFFF);
	TEXT->Add("시간", 730, 150, 36, "나눔명조", 0xFFFFFFFF);
	TEXT->Add("아이템", 1000, 150, 36, "나눔명조", 0xFFFFFFFF);

	for (int i = 0; i < 10; i++)
	{
		if (m_vecRank.size() <= i) break;
		TEXT->Add(m_vecRank[i].name, 415, 220 + 40 * i, 26, "나눔명조", 0xFFFFFFFF);
		char temp[32];
		sprintf_s(temp, "%.3f", m_vecRank[i].time);
		TEXT->Add(temp, 730, 220 + 40 * i, 26, "나눔명조", 0xFFFFFFFF);
		if (m_vecRank[i].item > 0)
		{
			ItemParent * item = ITEMMANAGER->GetItem(m_vecRank[i].item);
			TEXT->Add(item->GetName(), 1000, 220 + 40 * i, 26, "나눔명조", 0xFFFFFFFF);
			SAFE_DELETE(item);
		}
		else
			TEXT->Add("없음", 1000, 220 + 40 * i, 26, "나눔명조", 0xFFFFFFFF);
	}
}

void SC_Main::CalcRank()
{
	m_vecRank.clear();

	FILE* fp;
	fopen_s(&fp, "Ranking.rev", "r");

	if (!fp)
		return;

	while (true)
	{
		char line[128];
		fgets(line, 128, fp);

		ST_RANK rank;
		char * tok;
		char * context;
		tok = strtok_s(line, "\t\n", &context);
		if (!tok) continue;
		rank.name = tok;
		tok = strtok_s(NULL, "\t\n", &context);
		rank.time = atof(tok);
		tok = strtok_s(NULL, "\t\n", &context);
		rank.item = atoi(tok);
		m_vecRank.push_back(rank);

		if (feof(fp))
			break;
	}

	fclose(fp);

	sort(m_vecRank.begin(), m_vecRank.end(), RankSort);
}

bool SC_Main::RankSort(ST_RANK a, ST_RANK b)
{
	return (a.time < b.time);
}
