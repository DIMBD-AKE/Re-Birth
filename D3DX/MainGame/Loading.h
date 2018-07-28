#pragma once

enum LOAD_KIND
{
	LK_MODEL,		//��
	LK_TEXTURE,		//�ؽ���
	LK_SINGLETONE,	//�̱���
	LK_SOUND,		//����
	LK_PARTICLE,	//��ƼŬ
	LK_END			//������
};

struct RESOURCE
{
	string keyName;
	string folderPath;	//�ؽ��Ĵ� �� ������ path��, ��ƼŬ�� �� ������ �ؽ��� Ű �����̴�.
	string fileName;	//��ƼŬ�� �� ������ ����̴�.
	MODELTYPE type;
	bool loop;
};

class LoadItem
{
private:
	//�ε� ������ ����
	LOAD_KIND	m_eKind;
	RESOURCE	m_stResource;

public:

	void LoadModel(string keyName, string folderPath, string fileName, MODELTYPE type);
	void LoadTexture(string keyName, string path);
	void LoadSound(string keyName, string path, bool loop);
	void LoadParticle(string keyName, string TextureKeyName, string Path);
		//AddParticle("ttest", TEXTUREMANAGER->GetTexture("��ƼŬ����"), "./Particle/ttest.ptc");z

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

	//��׶��� �̹���

	//���α׷����� 


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

