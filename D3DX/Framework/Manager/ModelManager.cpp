#include "../../stdafx.h"
#include "ModelManager.h"


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

void ModelManager::AddModel(string keyName, string folderPath, string fileName, MODELTYPE type)
{
	if (type == MODELTYPE_OBJ)
	{
		if (m_mObj.find(keyName) != m_mObj.end())
			return;

		ObjLoader loader;
		m_mObj.insert(make_pair(keyName, loader.Load(folderPath, fileName)));
	}

	if (type == MODELTYPE_ASE)
	{
		if (m_mAse.find(keyName) != m_mAse.end())
			return;

		AseLoader loader;
		m_mAse.insert(make_pair(keyName, loader.Load(folderPath,fileName)));
	}

	if (type == MODELTYPE_X)
	{
		if (m_mX.find(keyName) != m_mX.end())
			return;

		m_mX.insert(make_pair(keyName, folderPath + fileName));
	}
}

Model * ModelManager::GetModel(string keyName, MODELTYPE type)
{
	if (type == MODELTYPE_OBJ)
	{
		if (m_mObj.find(keyName) != m_mObj.end())
		{
			ModelOBJ * obj = new ModelOBJ();
			ST_OBJECT * data = m_mObj.find(keyName)->second;
			obj->Setup(data);
			obj->CreateBound(data->size);
			obj->SetKeyName(keyName);
			obj->SetAlpha(data->alpha);
			return obj;
		}
	}
	if (type == MODELTYPE_ASE)
	{
		if (m_mAse.find(keyName) != m_mAse.end())
		{
			ModelASE * ase = new ModelASE();
			ST_ASE * data = new ST_ASE;
			data = m_mAse.find(keyName)->second;
			ase->Setup(data);
			ase->CreateBound(data->size);
			ase->SetKeyName(keyName);
			return ase;
		}
	}
	if (type == MODELTYPE_X)
	{
		if (m_mX.find(keyName) != m_mX.end())
		{
			ModelX * x = new ModelX();
			SkinnedMesh * data = new SkinnedMesh;
			string fullPath = m_mX[keyName].c_str();
			string folder = Util::GetFileFolder((char*)fullPath.c_str());
			fullPath = (char*)m_mX[keyName].c_str();
			string file = Util::GetFileName((char*)fullPath.c_str());
			data->Setup(folder, file);
			x->Setup(data);
			x->SetKeyName(keyName);
			x->SetFullPath(m_mX[keyName]);
			return x;
		}
	}
	return NULL;
}

void ModelManager::Release()
{
	auto objIter = m_mObj.begin();
	for (; objIter != m_mObj.end(); objIter++)
		SAFE_RELEASE(objIter->second->mesh);

	auto aseIter = m_mAse.begin();
	for (; aseIter != m_mAse.end(); aseIter++)
		SAFE_RELEASE(aseIter->second);

	m_mX.clear();
}

ModelOBJ * ModelOBJ::Clone() const
{
	return new ModelOBJ(*this);
}

ModelOBJ::~ModelOBJ()
{
	m_pMesh = NULL;
}

void ModelOBJ::Render()
{
	if (m_isBlend) DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	else DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Debug();

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	vector<int> drawOrder;
	for (int i = 0; i < m_pMesh->mat.size(); i++)
	{
		D3DSURFACE_DESC desc;
		m_pMesh->mat[i].t->GetLevelDesc(0, &desc);
		if (desc.Format == D3DFMT_X8R8G8B8)
			drawOrder.push_back(i);
	}
	for (int i = 0; i < m_pMesh->mat.size(); i++)
	{
		D3DSURFACE_DESC desc;
		m_pMesh->mat[i].t->GetLevelDesc(0, &desc);
		if (desc.Format == D3DFMT_A8R8G8B8)
			drawOrder.push_back(i);
	}

	for (int i = 0; i < drawOrder.size(); i++)
	{
		DEVICE->SetTexture(0, m_pMesh->mat[drawOrder[i]].t);
		DEVICE->SetMaterial(&m_pMesh->mat[drawOrder[i]].m);
		DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pMesh->mesh->DrawSubset(drawOrder[i]);
	}
}

bool ModelOBJ::IsDetailPick(Ray ray)
{
	ST_PNT_VERTEX * vd;
	m_pMesh->mesh->LockVertexBuffer(0, (void**)&vd);
	vector<ST_PNT_VERTEX> vecVertex(m_pMesh->mesh->GetNumVertices());
	memcpy(&vecVertex[0], vd, sizeof(ST_PNT_VERTEX) * m_pMesh->mesh->GetNumVertices());
	m_pMesh->mesh->UnlockVertexBuffer();

	for (int j = 0; j < m_pMesh->mesh->GetNumVertices(); j += 3)
	{
		D3DXVECTOR3 v0 = vd[j].p;
		D3DXVECTOR3 v1 = vd[j + 1].p;
		D3DXVECTOR3 v2 = vd[j + 2].p;

		D3DXVec3TransformCoord(&v0, &v0, &m_matWorld);
		D3DXVec3TransformCoord(&v1, &v1, &m_matWorld);
		D3DXVec3TransformCoord(&v2, &v2, &m_matWorld);

		if (D3DXIntersectTri(&v0, &v1, &v2, &ray.orig, &ray.dir, NULL, NULL, NULL))
			return true;
	}

	return false;
}

Model::Model()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vRotation = D3DXVECTOR3(0, 0, 0);
	m_vScale = D3DXVECTOR3(1, 1, 1);
}

Model::~Model()
{
}

void Model::World()
{
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS * matR * matT;
}

void Model::Update()
{
}

void Model::Debug()
{
	if (!g_isDebug) return;
	if (m_stBoundBox.vecVertex.empty()) return;

	DWORD prevFillMode;
	D3DXMATRIX matS, matR, matT;
	D3DMATERIAL9 mat;
	LPD3DXMESH meshSphere;

	DEVICE->GetRenderState(D3DRS_FILLMODE, &prevFillMode);
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// BoundBox
	D3DXMatrixScaling(&matS, m_stBoundBox.scale.x * m_vScale.x, m_stBoundBox.scale.y * m_vScale.y,
		m_stBoundBox.scale.z * m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matT, m_stBoundBox.pos.x + m_vPosition.x,
		m_stBoundBox.pos.y + m_vPosition.y, m_stBoundBox.pos.z + m_vPosition.z);
	DEVICE->SetTransform(D3DTS_WORLD, &(matS * matR * matT));
	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_stBoundBox.vecVertex.size() / 3,
		&m_stBoundBox.vecVertex[0], sizeof(ST_PC_VERTEX));

	// BoundSphere
	LPD3DXMESH mesh;
	ST_SPHERE sphere = GetBoundSphere();
	D3DXCreateSphere(DEVICE, sphere.radius, 8, 8, &mesh, NULL);
	D3DXMatrixTranslation(&matT, sphere.center.x, sphere.center.y, sphere.center.z);
	DEVICE->SetTransform(D3DTS_WORLD, &matT);
	mesh->DrawSubset(0);
	SAFE_RELEASE(mesh);

	DEVICE->SetRenderState(D3DRS_FILLMODE, prevFillMode);
}

void Model::CreateBound(ST_SIZEBOX box)
{
	if(!m_stBoundBox.vecVertex.empty()) return;

	// 바운드박스
	ST_PC_VERTEX v;
	vector<ST_PC_VERTEX> vecVertex;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR3(box.lowX, box.lowY, box.lowZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.lowX, box.highY, box.lowZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.highX, box.highY, box.lowZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.highX, box.lowY, box.lowZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.lowX, box.lowY, box.highZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.lowX, box.highY, box.highZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.highX, box.highY, box.highZ);	vecVertex.push_back(v);
	v.p = D3DXVECTOR3(box.highX, box.lowY, box.highZ);	vecVertex.push_back(v);

	vector<WORD> vecIndex;
	vecIndex.push_back(0); vecIndex.push_back(1);	vecIndex.push_back(2);
	vecIndex.push_back(0);	vecIndex.push_back(2);	vecIndex.push_back(3);

	vecIndex.push_back(7);	vecIndex.push_back(6);	vecIndex.push_back(5);
	vecIndex.push_back(7);	vecIndex.push_back(5);	vecIndex.push_back(4);

	vecIndex.push_back(3);	vecIndex.push_back(2);	vecIndex.push_back(6);
	vecIndex.push_back(3);	vecIndex.push_back(6);	vecIndex.push_back(7);

	vecIndex.push_back(4);	vecIndex.push_back(5);	vecIndex.push_back(1);
	vecIndex.push_back(4);	vecIndex.push_back(1);	vecIndex.push_back(0);

	vecIndex.push_back(4);	vecIndex.push_back(0);	vecIndex.push_back(3);
	vecIndex.push_back(4);	vecIndex.push_back(3);	vecIndex.push_back(7);

	vecIndex.push_back(1);	vecIndex.push_back(5);	vecIndex.push_back(6);
	vecIndex.push_back(1);	vecIndex.push_back(6);	vecIndex.push_back(2);

	for (int i = 0; i < vecIndex.size(); i++)
		m_stBoundBox.vecVertex.push_back(vecVertex[vecIndex[i]]);

	m_stBoundBox.scale = D3DXVECTOR3(1, 1, 1);

	// 바운드스페어
	float centerX = (box.lowX + box.highX) / 2.0f;
	float centerY = (box.lowY + box.highY) / 2.0f;
	float centerZ = (box.lowZ + box.highZ) / 2.0f;
	m_stBoundSphere.center = D3DXVECTOR3(centerX, centerY, centerZ);
	float maxX = (fabs(box.lowX) >= box.highX) ? fabs(box.lowX) : box.highX;
	float maxY = (fabs(box.lowY) >= box.highY) ? fabs(box.lowY) : box.highY;
	float maxZ = (fabs(box.lowZ) >= box.highZ) ? fabs(box.lowZ) : box.highZ;
	m_stBoundSphere.radius = maxX;
	if (m_stBoundSphere.radius < maxY) m_stBoundSphere.radius = maxY;
	if (m_stBoundSphere.radius < maxZ) m_stBoundSphere.radius = maxZ;
}

void Model::SetBoundBox(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_stBoundBox.pos = pos;
	m_stBoundBox.scale = scale;
}

ST_BOUNDBOX Model::GetBoundBox()
{
	ST_BOUNDBOX box = m_stBoundBox;
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, box.scale.x * m_vScale.x, box.scale.y * m_vScale.y,
		box.scale.z * m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matT, box.pos.x + m_vPosition.x,
		box.pos.y + m_vPosition.y, box.pos.z + m_vPosition.z);

	for (int i = 0; i < box.vecVertex.size(); i++)
		D3DXVec3TransformCoord(&box.vecVertex[i].p, &box.vecVertex[i].p, &(matS * matR * matT));
	
	return box;
}

void Model::SetBoundSphere(D3DXVECTOR3 center, float radius)
{
	m_stBoundSphere.center = center;
	m_stBoundSphere.radius = radius;
}

ST_SPHERE Model::GetBoundSphere()
{
	ST_SPHERE sphere = m_stBoundSphere;
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x,	m_vPosition.y, m_vPosition.z);
	D3DXVec3TransformCoord(&sphere.center, &sphere.center, &(matS * matR * matT));

	sphere.radius *= (m_vScale.x + m_vScale.y + m_vScale.z) / 3.0f;

	return sphere;
}

bool Model::IsPickBoundBox(Ray ray, float * dist)
{
	ST_BOUNDBOX box = GetBoundBox();
	for (int i = 0; i < box.vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0, v1, v2;
		v0 = box.vecVertex[i].p;
		v1 = box.vecVertex[i + 1].p;
		v2 = box.vecVertex[i + 2].p;

		if (D3DXIntersectTri(&v0, &v1, &v2, &ray.orig, &ray.dir, NULL, NULL, dist))
			return true;
	}
	return false;
}

bool Model::IsPickBoundSphere(Ray ray, float * dist)
{
	ST_SPHERE sphere = GetBoundSphere();
	bool ret = Util::IntersectSphere(sphere, ray);
	if (ret && dist) *dist = D3DXVec3Length(&(ray.orig - sphere.center));
	return ret;
}

ModelASE * ModelASE::Clone() const
{
	return new ModelASE(*this);
}

ModelASE::~ModelASE()
{
	m_pAse = NULL;
}

void ModelASE::World()
{
	Model::World();

	m_pAse->Update(0, &m_matWorld);
}

void ModelASE::Update()
{
	m_pAse->Update(m_pAse->GetKeyFrame(), &m_matWorld);
}

void ModelASE::Render()
{
	if (m_isBlend) DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	else DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Debug();
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	m_pAse->Render();
}

ModelX * ModelX::Clone() const
{
	ModelX * clone = new ModelX;
	SkinnedMesh * data = new SkinnedMesh;
	string fullPath = m_fullPath;
	string folder = Util::GetFileFolder((char*)fullPath.c_str());
	fullPath = m_fullPath;
	string file = Util::GetFileName((char*)fullPath.c_str());

	data->Setup(folder, file);
	*clone = *this;
	clone->Setup(data);
	return clone;
}

ModelX::~ModelX()
{
	SAFE_DELETE(m_pSMesh);
}

void ModelX::World()
{
	Model::World();
	m_pSMesh->Update();
}

void ModelX::Update()
{
	m_pSMesh->Animate();
}

void ModelX::Render()
{
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Debug();
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	m_pSMesh->Render(NULL, &m_matWorld);
}

map<string, int> ModelX::GetAnimation()
{
	return m_pSMesh->GetAnimMap();
}

bool ModelX::SetAnimation(string name)
{
	auto animMap = GetAnimation();
	if (animMap.find(name) == animMap.end())
		return false;

	m_pSMesh->SetIndex(GetAnimation()[name]);
	return true;
}

bool ModelX::SetAnimation(int index)
{
	auto animMap = GetAnimation();
	if (animMap.size() <= index || index < 0)
		return false;

	m_pSMesh->SetIndex(index);
	return true;
}

bool ModelX::SetBlendAnimation(string name)
{
	auto animMap = GetAnimation();
	if (animMap.find(name) == animMap.end())
		return false;

	m_pSMesh->SetBlendIndex(GetAnimation()[name]);
	return true;
}

bool ModelX::SetBlendAnimation(int index)
{
	auto animMap = GetAnimation();
	if (animMap.size() <= index || index < 0)
		return false;

	m_pSMesh->SetBlendIndex(index);
	return true;
}
