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

		SkinnedMesh * skin = new SkinnedMesh;
		skin->Setup(folderPath, fileName);
		m_mX.insert(make_pair(keyName, skin));
	}

	if (type == MODELTYPE_STATICX)
	{
		if (m_mStaticX.find(keyName) != m_mStaticX.end())
			return;

		ST_STATICX * staticX = new ST_STATICX;
		LPD3DXBUFFER mtrlBuffer;
		LPD3DXBUFFER adjBuffer;
		DWORD numMtrl;
		D3DXLoadMeshFromX((folderPath + fileName).c_str(),
			D3DXMESH_MANAGED,
			DEVICE,
			&adjBuffer, &mtrlBuffer, NULL, &numMtrl,
			&staticX->mesh);

		if (mtrlBuffer)
		{
			D3DXMATERIAL * mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
			staticX->numMtrl = numMtrl;
			for (int i = 0; i < numMtrl; i++)
			{
				mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
				staticX->vecMtl.push_back(mtrls[i].MatD3D);
				if (mtrls[i].pTextureFilename)
					staticX->vecTex.push_back(TEXTUREMANAGER->AddTexture(mtrls[i].pTextureFilename, folderPath + mtrls[i].pTextureFilename));
				else
					staticX->vecTex.push_back(NULL);
			}
		}

		BYTE * pVertex;
		D3DXVECTOR3 min;
		D3DXVECTOR3 max;
		staticX->mesh->LockVertexBuffer(0, (void**)&pVertex);
		D3DXComputeBoundingBox((D3DXVECTOR3*)pVertex, staticX->mesh->GetNumVertices(),
			D3DXGetFVFVertexSize(staticX->mesh->GetFVF()), &min, &max);

		D3DXVECTOR3 offset;
		offset.x = -min.x - (max.x - min.x) / 2;
		offset.y = -min.y;
		offset.z = -min.z - (max.z - min.z) / 2;
		staticX->offset = offset;

		staticX->sizeBox.highX = max.x + offset.x;
		staticX->sizeBox.highY = max.y + offset.y;
		staticX->sizeBox.highZ = max.z + offset.z;
		staticX->sizeBox.lowX = min.x + offset.x;
		staticX->sizeBox.lowY = min.y + offset.y;
		staticX->sizeBox.lowZ = min.z + offset.z;

		staticX->mesh->UnlockVertexBuffer();

		SAFE_RELEASE(mtrlBuffer);

		staticX->mesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0);

		SAFE_RELEASE(adjBuffer);

		m_mStaticX.insert(make_pair(keyName, staticX));
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
			data->CloneAnimation(m_mX.find(keyName)->second);
			x->Setup(data);
			x->SetKeyName(keyName);
			return x;
		}
	}
	if (type == MODELTYPE_STATICX)
	{
		if (m_mStaticX.find(keyName) != m_mStaticX.end())
		{
			ModelStaticX * staticX = new ModelStaticX();
			staticX->Setup(m_mStaticX[keyName]);
			staticX->CreateBound(m_mStaticX[keyName]->sizeBox);
			staticX->SetKeyName(keyName);
			return staticX;
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

	auto xIter = m_mX.begin();
	for (; xIter != m_mX.end(); xIter++)
		SAFE_DELETE(xIter->second);

	auto sXIter = m_mStaticX.begin();
	for (; sXIter != m_mStaticX.end(); sXIter++)
	{
		SAFE_RELEASE(sXIter->second->mesh);
		SAFE_DELETE(sXIter->second);
	}
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
	if (!CAMERA->IsFrustum(GetBoundSphere())) return;
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

	// OBB
	m_stBoundBox.obb.vAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_stBoundBox.obb.vAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_stBoundBox.obb.vAxisDir[2] = D3DXVECTOR3(0, 0, 1);
	m_stBoundBox.obb.fAxisLen[0] = (box.highX + fabs(box.lowX)) / 2.0f;
	m_stBoundBox.obb.fAxisLen[1] = (box.highY + fabs(box.lowY)) / 2.0f;
	m_stBoundBox.obb.fAxisLen[2] = (box.highZ + fabs(box.lowZ)) / 2.0f;

	// 바운드스페어
	float centerX = (box.lowX + box.highX) / 2.0f;
	float centerY = (box.lowY + box.highY) / 2.0f;
	float centerZ = (box.lowZ + box.highZ) / 2.0f;
	m_stBoundSphere.center = D3DXVECTOR3(centerX, centerY, centerZ);
	float maxX = (fabs(box.lowX) >= box.highX) ? fabs(box.lowX) : box.highX;
	float maxY = (fabs(box.lowY) >= box.highY) ? fabs(box.lowY) : box.highY;
	float maxZ = (fabs(box.lowZ) >= box.highZ) ? fabs(box.lowZ) : box.highZ;
	m_stBoundSphere.radius = D3DXVec3Length(&(D3DXVECTOR3(maxX, maxY, maxZ)));
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

	// OBB
	D3DXVec3TransformCoord(&box.obb.vCenterPos, &D3DXVECTOR3(0, 0, 0), &matT);
	box.obb.fAxisLen[0] *= box.scale.x * m_vScale.x;
	box.obb.fAxisLen[1] *= box.scale.y * m_vScale.y;
	box.obb.fAxisLen[2] *= box.scale.z * m_vScale.z;
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformCoord(&box.obb.vAxisDir[i], &box.obb.vAxisDir[i], &matR);

	// BOX
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
	vector<float> vecDist;
	for (int i = 0; i < box.vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0, v1, v2;
		v0 = box.vecVertex[i].p;
		v1 = box.vecVertex[i + 1].p;
		v2 = box.vecVertex[i + 2].p;

		if (D3DXIntersectTri(&v0, &v1, &v2, &ray.orig, &ray.dir, NULL, NULL, dist))
			vecDist.push_back(*dist);
	}
	if (!vecDist.empty())
	{
		float length = vecDist[0];
		for (int i = 0; i < vecDist.size(); i++)
			if (length > vecDist[i])
				length = vecDist[i];
		*dist = length;
		return true;
	}
	return false;
}

bool Model::IsPickBoundSphere(Ray ray, float * dist)
{
	ST_SPHERE sphere = GetBoundSphere();
	bool ret = IntersectSphere(sphere, ray);
	if (ret && dist) *dist = D3DXVec3Length(&(ray.orig - sphere.center));
	return ret;
}

bool Model::IsCollisionSphere(Model * target)
{
	float length = target->GetBoundSphere().radius + GetBoundSphere().radius;
	return (D3DXVec3Length(&(*target->GetPosition() - m_vPosition)) <= length);
}

bool Model::IsCollisionOBB(Model * target)
{
	ST_OBB thisBox = GetBoundBox().obb;
	ST_OBB targetBox = target->GetBoundBox().obb;

	return CollisionOBB(thisBox, targetBox);
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
	if (!CAMERA->IsFrustum(GetBoundSphere())) return;
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
	data->CloneAnimation(this->m_pSMesh);
	clone->Setup(data);
	clone->SetKeyName(this->m_keyName);
	return clone;
}

ModelX::~ModelX()
{
	m_pSMesh->Release();
}

void ModelX::Render()
{
	if (!CAMERA->IsFrustum(GetBoundSphere())) return;
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Debug();
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	m_pSMesh->UpdateRender(&m_matWorld, false);
}

void ModelX::DummyRender()
{
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Debug();
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	m_pSMesh->UpdateRender(&m_matWorld, true);
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

	m_pSMesh->SetIndex(animMap[name]);
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

void ModelX::SetAnimationPosition(float pos)
{
	m_pSMesh->SetAnimationPosition(pos);
}

bool ModelX::SetBlendAnimation(string name)
{
	auto animMap = GetAnimation();
	if (animMap.find(name) == animMap.end())
		return false;

	m_pSMesh->SetBlendIndex(animMap[name]);
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

bool ModelX::SetBlendTime(float time)
{
	if (time < 0 || time > 1)
		return false;

	m_pSMesh->SetBlendTime(time);
	return true;
}

void ModelX::SetAnimationSpeed(float speed)
{
	m_pSMesh->SetAnimationSpeed(speed);
}

bool ModelX::IsAnimationEnd()
{
	return m_pSMesh->IsAnimationEnd();
}

bool ModelX::IsAnimationPercent(float rate)
{
	return m_pSMesh->IsAnimationPercent(rate);
}

float ModelX::GetAnimationPeriod(string name)
{
	auto animMap = GetAnimation();
	if (animMap.find(name) == animMap.end())
		return -1;

	return m_pSMesh->GetAnimationPeriod(animMap[name]);
}

float ModelX::GetAnimationPeriod(int index)
{
	auto animMap = GetAnimation();
	if (animMap.size() <= index || index < 0)
		return -1;

	return m_pSMesh->GetAnimationPeriod(index);
}

float ModelX::GetCurrentAnimationPercent()
{
	return m_pSMesh->GetCurrentAnimationPercent();
}

float ModelX::GetShaderAlpha()
{
	return m_pSMesh->GetAlpha();
}

void ModelX::SetShaderColorOffset(float offset)
{
	m_pSMesh->SetColorOffset(offset);
}

float ModelX::GetShaderColorOffset()
{
	return m_pSMesh->GetColorOffset();
}

void ModelX::SetShaderRimPower(float power)
{
	m_pSMesh->SetRimPower(power);
}

float ModelX::GetShaderRimPower()
{
	return m_pSMesh->GetRimPower();
}

void ModelX::SetShaderRimColor(D3DXVECTOR3 color)
{
	m_pSMesh->SetRimColor(color);
}

D3DXVECTOR3 ModelX::GetShaderRimColor()
{
	return m_pSMesh->GetRimColor();
}

void ModelX::SetShaderHologram(bool holo)
{
	m_pSMesh->SetHologram(holo);
}

bool ModelX::GetShaderHologram()
{
	return m_pSMesh->GetHologram();
}

void ModelX::SetShaderFadeCut(float fade)
{
	m_pSMesh->SetFadeCut(fade);
}

float ModelX::GetShaderFadeCut()
{
	return m_pSMesh->GetFadeCut();;
}

D3DXMATRIX * ModelX::GetBoneMatrix(string name)
{
	return m_pSMesh->GetBoneMatrix(name);
}

void ModelX::SetShaderAlpha(float alpha)
{
	m_pSMesh->SetAlpha(Clamp(0, 1, alpha));
}

ModelStaticX * ModelStaticX::Clone() const
{
	return new ModelStaticX(*this);
}

ModelStaticX::~ModelStaticX()
{
}

void ModelStaticX::Render()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	Debug();
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, m_pStaticX->offset.x, m_pStaticX->offset.y, m_pStaticX->offset.z);
	for (int i = 0; i < m_pStaticX->numMtrl; i++)
	{
		DEVICE->SetTexture(0, m_pStaticX->vecTex[i]);
		DEVICE->SetMaterial(&m_pStaticX->vecMtl[i]);
		DEVICE->SetTransform(D3DTS_WORLD, &(matT * m_matWorld));
		m_pStaticX->mesh->DrawSubset(i);
	}
}