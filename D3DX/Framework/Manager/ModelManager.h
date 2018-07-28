#pragma once
#include "../Parser/ObjLoader.h"
#include "../Parser/AseLoader.h"
#include "../Parser/SkinnedMesh.h"

enum MODELTYPE
{
	MODELTYPE_OBJ,
	MODELTYPE_ASE,
	MODELTYPE_X,
	MODELTYPE_STATICX
};

class Model
{
	SYNTHESIZE(string, m_keyName, KeyName);
	SYNTHESIZE_PT(D3DXMATRIX, m_matWorld, World);
	SYNTHESIZE_PT(D3DXVECTOR3, m_vRotation, Rotation);
	SYNTHESIZE_PT(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_PT(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(bool, m_isBlend, Blend);

public:
	Model();
	virtual Model * Clone() const = 0;
	virtual ~Model();

	virtual void World();
	virtual void Update();
	virtual void Render() = 0;
	virtual void DummyRender() {}

	// OBJ 파일 전용
	SYNTHESIZE(bool, m_isAlpha, Alpha);
	virtual bool IsDetailPick(Ray ray) { return false; }

	// X 파일 전용
	virtual map<string, int> GetAnimation() { return map<string, int>(); }
	virtual bool SetAnimation(string name) { return false; }
	virtual bool SetAnimation(int index) { return false; }
	virtual void SetAnimationPosition(float pos) {}
	virtual bool SetBlendAnimation(string name) { return false; }
	virtual bool SetBlendAnimation(int index) { return false; }
	virtual bool SetBlendTime(float time) { return false; }
	virtual void SetAnimationSpeed(float speed) {}
	virtual bool IsAnimationEnd() { return false; }
	virtual bool IsAnimationPercent(float rate) { return false; }
	virtual float GetAnimationPeriod(string name) { return 0; }
	virtual float GetAnimationPeriod(int index) { return 0; }
	virtual void SetShaderAlpha(float alpha) {}
	virtual float GetShaderAlpha() { return 0; }
	virtual void SetShaderColorOffset(float offset) {}
	virtual float GetShaderColorOffset() { return 0; }
	virtual void SetShaderRimPower(float power) {}
	virtual float GetShaderRimPower() { return 0; }
	virtual void SetShaderRimColor(D3DXVECTOR3 color) {}
	virtual D3DXVECTOR3 GetShaderRimColor() { return D3DXVECTOR3(); }
	virtual D3DXMATRIX* GetBoneMatrix(string name) { return NULL; }

protected:
	ST_BOUNDBOX	m_stBoundBox;
	ST_SPHERE	m_stBoundSphere;

public:
	void Debug();

	// BoundBox, Sphere 생성
	void CreateBound(ST_SIZEBOX box);

	void SetBoundBox(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	ST_BOUNDBOX GetBoundBox();
	ST_BOUNDBOX GetOrigBoundBox() { return m_stBoundBox; }
	void SetBoundSphere(D3DXVECTOR3 center, float radius);
	ST_SPHERE GetBoundSphere();
	ST_SPHERE GetOrigBoundSphere() { return m_stBoundSphere; }

	bool IsPickBoundBox(Ray ray, float * dist);
	bool IsPickBoundSphere(Ray ray, float * dist);

	bool IsCollisionSphere(Model * target);
	bool IsCollisionOBB(Model * target);
};

class ModelOBJ : public Model
{
private:
	ST_OBJECT* m_pMesh;

public:
	ModelOBJ() {}
	virtual ModelOBJ * Clone() const;
	virtual ~ModelOBJ();

	void Setup(ST_OBJECT* data) { m_pMesh = data; }
	virtual void Render();

	virtual bool IsDetailPick(Ray ray);
};

class ModelASE : public Model
{
private:
	ST_ASE* m_pAse;

public:
	ModelASE() {}
	virtual ModelASE * Clone() const;
	virtual ~ModelASE();

	void Setup(ST_ASE* data) { m_pAse = data; }
	virtual void World();
	virtual void Update();
	virtual void Render();
};

class ModelX : public Model
{
private:
	SkinnedMesh * m_pSMesh;

public:
	ModelX() {}
	virtual ModelX * Clone() const;
	virtual ~ModelX();

	void Setup(SkinnedMesh* data) { m_pSMesh = data; }
	virtual void Render();
	virtual void DummyRender();

	virtual map<string, int> GetAnimation();
	virtual bool SetAnimation(string name);
	virtual bool SetAnimation(int index);
	virtual void SetAnimationPosition(float pos);
	virtual bool SetBlendAnimation(string name);
	virtual bool SetBlendAnimation(int index);
	virtual bool SetBlendTime(float time);
	virtual void SetAnimationSpeed(float speed);
	virtual bool IsAnimationEnd();
	virtual bool IsAnimationPercent(float rate);
	virtual float GetAnimationPeriod(string name);
	virtual float GetAnimationPeriod(int index);
	virtual D3DXMATRIX* GetBoneMatrix(string name);

	virtual void SetShaderAlpha(float alpha);
	virtual float GetShaderAlpha();
	virtual void SetShaderColorOffset(float offset);
	virtual float GetShaderColorOffset();
	virtual void SetShaderRimPower(float power);
	virtual float GetShaderRimPower();
	virtual void SetShaderRimColor(D3DXVECTOR3 color);
	virtual D3DXVECTOR3 GetShaderRimColor();
};

class ModelStaticX : public Model
{
private:
	ST_STATICX * m_pStaticX;

public:
	ModelStaticX() {}
	virtual ModelStaticX * Clone() const;
	virtual ~ModelStaticX();

	void Setup(ST_STATICX* data) { m_pStaticX = data; }
	virtual void Render();
};

class ModelManager
{
	SINGLETONE(ModelManager);

private:
	map<string, ST_OBJECT*>		m_mObj;
	map<string, ST_ASE*>		m_mAse;
	map<string, SkinnedMesh*>	m_mX;
	map<string, ST_STATICX*>	m_mStaticX;

public:
	void AddModel(string keyName, string folderPath, string fileName, MODELTYPE type);
	Model* GetModel(string keyName, MODELTYPE type);

	void Release();
};

#define MODELMANAGER ModelManager::GetInstance()