#pragma once

struct ST_DAMAGETEXT			//������ �ؽ�Ʈ�� ����ü
{
	int Damage;
	float time;
	float endTime;
	float angle;
	float alpha;
	float x;

};

class DamageUI
{
	UIObject*				m_pUIDamage[10];		//�������� UIObj����
	vector<ST_DAMAGETEXT>		m_vecDamage;

public:
	DamageUI();
	~DamageUI();

	void Setup(bool IsPlayer);
	void Render(D3DXVECTOR3 pos);

	void AddDamage(int damage, float angle = rand()%100, float time = 0.0f,
		float endtime = 1.0f, float alpha = 255.0f, float x = 0.0f);
};

