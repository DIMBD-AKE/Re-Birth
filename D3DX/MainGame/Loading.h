#pragma once

enum LOAD_KIND
{
	LK_MODEL,		//모델
	LK_TEXTURE,		//텍스쳐
	LK_SINGLETONE,	//싱글톤
	LK_SOUND,		//사운드
	LK_PARTICLE,	//파티클
	LK_END			//끝났냐
};

struct RESOURCE
{
	string keyName;
	string folderPath;	//텍스쳐는 이 변수가 path다, 파티클은 이 변수가 텍스쳐 키 네임이다.
	string fileName;	//파티클은 이 변수가 경로이다.
	MODELTYPE type;
	bool loop;
};

class LoadItem
{
private:
	//로딩 아이템 종류
	LOAD_KIND	m_eKind;
	RESOURCE	m_stResource;

public:

	void LoadModel(string keyName, string folderPath, string fileName, MODELTYPE type);
	void LoadTexture(string keyName, string path);
	void LoadSound(string keyName, string path, bool loop);
	void LoadParticle(string keyName, string TextureKeyName, string Path);
		//AddParticle("ttest", TEXTUREMANAGER->GetTexture("파티클시험"), "./Particle/ttest.ptc");z

	LOAD_KIND GetLoadKind() { return m_eKind; }

	RESOURCE GetItemResource(){ return m_stResource; }

	LoadItem();
	~LoadItem();
};


class Loading
{

private:
	typedef vector<LoadItem*> vecLoadItem;
	typedef vector<LoadItem*>::iterator vecLoadItemIter;

private:
	vecLoadItem m_vLoadItem;

	//백그라운드 이미지

	//프로그래스바 


	int m_nCurrentGauge;
public:
	void Setup();

	BOOL LoadingDone();
	
	void LoadModel(string keyName, string folderPath, string fileName, MODELTYPE type);
	void LoadTexture(string keyName, string path);
	void LoadSound(string keyName, string path, bool loop);
	void LoadParticle(string keyName, string TextureKeyName, string Path);

	void LoadSingletone(string keyName, const char* fileName);

	float GaugePercent() { return m_nCurrentGauge / (float)m_vLoadItem.size(); }
	LOAD_KIND CurrentType() { return m_nCurrentGauge < m_vLoadItem.size() ? m_vLoadItem[m_nCurrentGauge]->GetLoadKind() : LK_END; }

	Loading();
	~Loading();
};

