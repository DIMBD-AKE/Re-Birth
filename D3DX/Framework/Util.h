#pragma once

class Util
{
public:
	static char* GetFileType(char* fullPath)
	{
		char * context;
		char * tok;
		char * ret = NULL;
		tok = strtok_s(fullPath, ".", &context);
		while (tok != NULL)
		{
			ret = tok;
			tok = strtok_s(NULL, ".", &context);
		}
		return ret;
	}

	static char* GetFileName(char* fullPath)
	{
		char * context;
		char * tok;
		char * ret = NULL;
		tok = strtok_s(fullPath, "/", &context);
		while (tok != NULL)
		{
			ret = tok;
			tok = strtok_s(NULL, "/", &context);
		}
		return ret;
	}

	static string GetFileFolder(char* fullPath)
	{
		char * context;
		char * tok;
		string ret = "";
		tok = strtok_s(fullPath, "/", &context);
		while (tok != NULL)
		{
			if (strlen(context) > 0)
				ret += string(tok) + string("/");
			tok = strtok_s(NULL, "/", &context);
		}
		return ret;
	}

	static D3DXVECTOR2 Convert3DTo2D(D3DXVECTOR3 v)
	{
		D3DXMATRIX proj, view, world;
		D3DVIEWPORT9 vp;
		DEVICE->GetTransform(D3DTS_PROJECTION, &proj);
		DEVICE->GetTransform(D3DTS_VIEW, &view);
		DEVICE->GetViewport(&vp);
		D3DXMatrixIdentity(&world);
		D3DXVec3Project(&v, &v, &vp, &proj, &view, &world);
		return D3DXVECTOR2(v.x, v.y);
	}

	static D3DXVECTOR3 ConvertGridPos(D3DXVECTOR3 pos, float cellSize)
	{
		D3DXVECTOR3 grid;
		grid.x = round(pos.x / cellSize) * cellSize;
		grid.y = round(pos.y / cellSize) * cellSize;
		grid.z = round(pos.z / cellSize) * cellSize;
		return grid;
	}

	static Ray RayAtViewSpace(POINT mouse)
	{
		D3DVIEWPORT9 vp;
		DEVICE->GetViewport(&vp);

		D3DXMATRIX proj;
		DEVICE->GetTransform(D3DTS_PROJECTION, &proj);

		Ray r;
		r.dir.x = ((2.0f * mouse.x) / vp.Width - 1.0f) / proj._11;
		r.dir.y = ((-2.0f * mouse.y) / vp.Height + 1.0f) / proj._22;
		r.dir.z = 1.0f;
		r.orig = D3DXVECTOR3(0, 0, 0);
		return r;
	}

	static Ray RayAtWorldSpace(POINT mouse)
	{
		Ray r = RayAtViewSpace(mouse);

		D3DXMATRIX view, inv;
		DEVICE->GetTransform(D3DTS_VIEW, &view);
		D3DXMatrixInverse(&inv, NULL, &view);

		D3DXVec3TransformCoord(&r.orig, &r.orig, &inv);
		D3DXVec3TransformNormal(&r.dir, &r.dir, &inv);
		D3DXVec3Normalize(&r.dir, &r.dir);

		return r;
	}

	static bool IntersectSphere(ST_SPHERE sphere, Ray ray)
	{
		D3DXMATRIX matInvWorld;
		D3DXMatrixIdentity(&matInvWorld);
		matInvWorld._41 = -sphere.center.x;
		matInvWorld._42 = -sphere.center.y;
		matInvWorld._43 = -sphere.center.z;

		D3DXVec3TransformCoord(&ray.orig, &ray.orig, &matInvWorld);
		D3DXVec3TransformNormal(&ray.dir, &ray.dir, &matInvWorld);

		float vv = D3DXVec3Dot(&ray.dir, &ray.dir);
		float qv = D3DXVec3Dot(&ray.orig, &ray.dir);
		float qq = D3DXVec3Dot(&ray.orig, &ray.orig);
		float rr = sphere.radius * sphere.radius;

		return qv * qv - vv * (qq - rr) >= 0;
	}
};