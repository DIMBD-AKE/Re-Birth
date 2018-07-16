#pragma once

enum LOAD_KIND
{
	LK_MODEL,		//��
	LK_TEXTURE,		//�ؽ���
	LK_SINGLETONE,	//�̱���
	LK_END			//������
};

struct RESOURCE
{
	string keyName;
	string folderPath;	//�ؽ��Ĵ� �� ������ path��
	string fileName;
	MODELTYPE type;
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
	void Update();
	void Render();

	BOOL loadingDone();
	
	void LoadModel(string keyName, string folderPath, string fileName, MODELTYPE type);
	void LoadTexture(string keyName, string path);

	void LoadSingletone(string keyName, const char* fileName);


	Loading();
	~Loading();
};

