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

	static float Clamp(float min, float max, float value)
	{
		if (value < min) value = min;
		if (value > max) value = max;
		return value;
	}

	static float Overflow(float min, float max, float value)
	{
		if (value > max)
			value -= (int)(value / max) * max;
		if (value < min)
			value += (int)(value / max) * max;
		return value;
	}

	static D3DXVECTOR3 Linear(D3DXVECTOR3 v0, D3DXVECTOR3 v1, float t)
	{
		t = Clamp(0, 1, t);
		return (1 - t) * v0 + t * v1;
	}

	static D3DXVECTOR3 Bezier2(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float t)
	{
		t = Clamp(0, 1, t);
		return pow(1 - t, 2) * v0 +
			2 * t *(1 - t) * v1 +
			pow(t, 2) * v2;
	}

	static D3DXVECTOR3 Bezier3(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, float t)
	{
		t = Clamp(0, 1, t);
		return v0 * pow(1 - t, 3) +
			3 * v1 * t * pow(1 - t, 2) +
			3 * v2 * pow(t, 2) * (1 - t) +
			v3 * pow(t, 3);
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

	static POINT MakePoint(float x, float y)
	{
		POINT pt;
		pt.x = x; pt.y = y;
		return pt;
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