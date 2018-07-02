#pragma once

class MonsterParent;


//만들어진 몬스터들을 총괄하는 클래스
class MonsterManager
{

	GET(vector<MonsterParent>, m_vMM, MonsterManager);
	//vector<MonsterParent> m_vMM;

public:
	MonsterManager();
	~MonsterManager();

	
};

