#pragma once

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIX	CombinedTransformationMatrix; // 부모노드와 누적된 매트릭스
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	LPD3DXMESH		pOrigMesh; // 원본 메시
	D3DXMATRIX**	ppBoneMatrixPtrs; // 영향을 주는 프레임들의 월드 매트릭스 포인터
	D3DXMATRIX*		pBoneOffsetMatrices; // 원본 메시를 로컬로 보내주는 매트릭스
	D3DXMATRIX*		pCurrentBoneMatrices; // 현재 본의 계산된 월드 매트릭스를 저장할 매트릭스

	std::vector<D3DMATERIAL9>		vecMtl;
	std::vector<LPDIRECT3DTEXTURE9>	vecTex;
	std::vector<LPDIRECT3DTEXTURE9>	vecNor;
};

class AllocatedHierachy : public ID3DXAllocateHierarchy
{
protected:
	SYNTHESIZE(std::string, m_sFolder, Folder);

public:
	AllocatedHierachy();
	~AllocatedHierachy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;
};

class SkinnedMesh
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	bool						m_isBlend;
	bool						m_isHolo;
	float						m_fBlendTime;
	float						m_fPassedTime;

	LPD3DXEFFECT				m_pShaderEffect;

	SYNTHESIZE(float, m_fAlpha, Alpha);
	SYNTHESIZE(float, m_fOffset, ColorOffset);
	SYNTHESIZE(float, m_fRimPower, RimPower);
	SYNTHESIZE(D3DXVECTOR3, m_vRimColor, RimColor);

private:
	map<string, int>			m_animMap;

public:
	SkinnedMesh();
	~SkinnedMesh();

	void CloneAnimation(SkinnedMesh * orig);

	void Setup(string szFolder, string szFile);
	void Update(bool dummy);
	void Animate();

	void SetIndex(int index);
	void SetBlendIndex(int index);
	void SetBlendTime(float time) { m_fBlendTime = time; }
	void SetAnimationSpeed(float speed);
	void SetAnimationPosition(float pos);
	void SetHologram(bool holo) { m_isHolo = holo; }
	bool GetHologram() { return m_isHolo; }
	bool IsAnimationPercent(float rate);
	bool IsAnimationEnd();

	float GetAnimationPeriod(int index);

	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent, bool dummy);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void Render(LPD3DXFRAME pFrame, D3DXMATRIX * matWorld);

	void FindAllChild(LPD3DXFRAME pFrame, vector<LPD3DXFRAME>& vecChild);
	D3DXMATRIX* GetBoneMatrix(string boneName);

	void UpdateRender(D3DXMATRIX * matWorld, bool dummy);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void Destroy(D3DXFRAME* pFrame);

	void Release();

	map<string, int> GetAnimMap() { return m_animMap; }
};