#pragma once

class MonsterParent;


//������� ���͵��� �Ѱ��ϴ� Ŭ����
class MonsterManager
{

	GET(vector<MonsterParent>, m_vMM, MonsterManager);
	//vector<MonsterParent> m_vMM;

public:
	MonsterManager();
	~MonsterManager();

	
};

