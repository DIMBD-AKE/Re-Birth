#pragma once

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIX	CombinedTransformationMatrix; // �θ���� ������ ��Ʈ����
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	LPD3DXMESH		pOrigMesh; // ���� �޽�
	D3DXMATRIX**	ppBoneMatrixPtrs; // ������ �ִ� �����ӵ��� ���� ��Ʈ���� ������
	D3DXMATRIX*		pBoneOffsetMatrices; // ���� �޽ø� ���÷� �����ִ� ��Ʈ����
	D3DXMATRIX*		pCurrentBoneMatrices; // ���� ���� ���� ���� ��Ʈ������ ������ ��Ʈ����

	std::vector<D3DMATERIAL9>		vecMtl;
	std::vector<LPDIRECT3DTEXTURE9>	vecTex;
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
	float						m_fBlendTime;
	float						m_fPassedTime;

private:
	map<string, int>			m_animMap;

public:
	SkinnedMesh();
	~SkinnedMesh();

	void Setup(string szFolder, string szFile);
	void Update();
	void Animate();

	void SetIndex(int index);
	void SetBlendIndex(int index);
	void SetBlendTime(float time) { m_fBlendTime = time; }
	void SetAnimationSpeed(float speed);
	bool IsAnimationPercent(float rate);
	bool IsAnimationEnd();

	float GetAnimationPeriod(int index);

	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void Render(LPD3DXFRAME pFrame, D3DXMATRIX * matWorld);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void Destroy(D3DXFRAME* pFrame);

	map<string, int> GetAnimMap() { return m_animMap; }
};