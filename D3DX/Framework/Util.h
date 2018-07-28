#pragma once

namespace UTIL
{
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

	static int NRand(int low, int high)
	{
		return low + rand() % (high-low+1);
	}

	static float FRand(float low, float high)
	{
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
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

	static float GetDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
	{
		D3DXVECTOR3 tempV = pos1 - pos2;

		return D3DXVec3Length(&tempV);
	}

	static bool IntersectSphere(D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2)
	{
		float distance = GetDistance(pos1, pos2);

		if (radius1 + radius2 >= distance)
		{
			return true;
		}

		return false;
	}

	static bool IntersectSphere(ST_SPHERE sphere1, ST_SPHERE sphere2)
	{
		float distance = GetDistance(sphere1.center, sphere2.center);

		if (sphere1.radius + sphere2.radius >= distance)
		{
			return true;
		}
		return false;
	}

	//µÎ º¤ÅÍ°£ÀÇ °¢µµ -> 0,0, ¹æÇâº¤ÅÍx, ¹æÇâº¤ÅÍy
	static float GetAngle(float x1, float z1, float x2, float z2)
	{
		float x = x2 - x1;
		float y = z2 - z1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (z2 > z1)
		{
			angle = D3DX_PI * 2 - angle;
			if (angle >= D3DX_PI * 2) angle -= D3DX_PI*2;
		}

		return angle;
	}

	static float GetAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
	{
		float x = TargetPos.x - pos.x;
		float y = TargetPos.z - pos.z;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (TargetPos.z > pos.z)
		{
			angle = D3DX_PI * 2 - angle;
			if (angle >= D3DX_PI * 2) angle -= D3DX_PI * 2;
		}

		return angle;
	}

	static bool CollisionOBB(ST_OBB thisBox, ST_OBB targetBox)
	{
		double c[3][3];
		double absC[3][3];
		double d[3];

		double r0, r1, r;
		int i;

		const double cutoff = 0.999999;
		bool existsParallelPair = false;

		D3DXVECTOR3 diff = thisBox.vCenterPos - targetBox.vCenterPos;

		for (i = 0; i < 3; ++i)
		{
			c[0][i] = D3DXVec3Dot(&thisBox.vAxisDir[0], &targetBox.vAxisDir[i]);
			absC[0][i] = abs(c[0][i]);
			if (absC[0][i] > cutoff)
				existsParallelPair = true;
		}
		d[0] = D3DXVec3Dot(&diff, &thisBox.vAxisDir[0]);
		r = abs(d[0]);
		r0 = thisBox.fAxisLen[0];
		r1 = targetBox.fAxisLen[0] * absC[0][0] + targetBox.fAxisLen[1] * absC[0][1] + targetBox.fAxisLen[2] * absC[0][2];

		if (r > r0 + r1)
			return false;

		for (i = 0; i < 3; ++i)
		{
			c[1][i] = D3DXVec3Dot(&thisBox.vAxisDir[1], &targetBox.vAxisDir[i]);
			absC[1][i] = abs(c[1][i]);
			if (absC[1][i] > cutoff)
				existsParallelPair = true;
		}

		d[1] = D3DXVec3Dot(&diff, &thisBox.vAxisDir[1]);
		r = abs(d[1]);
		r0 = thisBox.fAxisLen[1];
		r1 = targetBox.fAxisLen[0] * absC[1][0] + targetBox.fAxisLen[1] * absC[1][1] + targetBox.fAxisLen[2] * absC[1][2];

		if (r > r0 + r1)
			return false;

		for (i = 0; i < 3; ++i)
		{
			c[2][i] = D3DXVec3Dot(&thisBox.vAxisDir[2], &targetBox.vAxisDir[i]);
			absC[2][i] = abs(c[2][i]);
			if (absC[2][i] > cutoff)
				existsParallelPair = true;
		}

		d[2] = D3DXVec3Dot(&diff, &thisBox.vAxisDir[2]);
		r = abs(d[2]);
		r0 = thisBox.fAxisLen[2];
		r1 = targetBox.fAxisLen[0] * absC[2][0] + targetBox.fAxisLen[1] * absC[2][1] + targetBox.fAxisLen[2] * absC[2][2];

		if (r > r0 + r1)
			return false;

		r = abs(D3DXVec3Dot(&diff, &targetBox.vAxisDir[0]));
		r0 = thisBox.fAxisLen[0] * absC[0][0] + thisBox.fAxisLen[1] * absC[1][0] + thisBox.fAxisLen[2] * absC[2][0];
		r1 = targetBox.fAxisLen[0];

		if (r > r0 + r1)
			return false;

		r = abs(D3DXVec3Dot(&diff, &targetBox.vAxisDir[1]));
		r0 = thisBox.fAxisLen[0] * absC[0][1] + thisBox.fAxisLen[1] * absC[1][1] + thisBox.fAxisLen[2] * absC[2][1];
		r1 = targetBox.fAxisLen[1];

		if (r > r0 + r1)
			return false;

		r = abs(D3DXVec3Dot(&diff, &targetBox.vAxisDir[2]));
		r0 = thisBox.fAxisLen[0] * absC[0][2] + thisBox.fAxisLen[1] * absC[1][2] + thisBox.fAxisLen[2] * absC[2][2];
		r1 = targetBox.fAxisLen[2];

		if (r > r0 + r1)
			return false;

		if (existsParallelPair == true)
			return true;

		r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
		r0 = thisBox.fAxisLen[1] * absC[2][0] + thisBox.fAxisLen[2] * absC[1][0];
		r1 = targetBox.fAxisLen[1] * absC[0][2] + targetBox.fAxisLen[2] * absC[0][1];
		if (r > r0 + r1)
			return false;

		r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
		r0 = thisBox.fAxisLen[1] * absC[2][1] + thisBox.fAxisLen[2] * absC[1][1];
		r1 = targetBox.fAxisLen[0] * absC[0][2] + targetBox.fAxisLen[2] * absC[0][0];
		if (r > r0 + r1)
			return false;

		r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
		r0 = thisBox.fAxisLen[1] * absC[2][2] + thisBox.fAxisLen[2] * absC[1][2];
		r1 = targetBox.fAxisLen[0] * absC[0][1] + targetBox.fAxisLen[1] * absC[0][0];
		if (r > r0 + r1)
			return false;

		r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
		r0 = thisBox.fAxisLen[0] * absC[2][0] + thisBox.fAxisLen[2] * absC[0][0];
		r1 = targetBox.fAxisLen[1] * absC[1][2] + targetBox.fAxisLen[2] * absC[1][1];
		if (r > r0 + r1)
			return false;

		r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
		r0 = thisBox.fAxisLen[0] * absC[2][1] + thisBox.fAxisLen[2] * absC[0][1];
		r1 = targetBox.fAxisLen[0] * absC[1][2] + targetBox.fAxisLen[2] * absC[1][0];
		if (r > r0 + r1)
			return false;

		r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
		r0 = thisBox.fAxisLen[0] * absC[2][2] + thisBox.fAxisLen[2] * absC[0][2];
		r1 = targetBox.fAxisLen[0] * absC[1][1] + targetBox.fAxisLen[1] * absC[1][0];
		if (r > r0 + r1)
			return false;

		r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
		r0 = thisBox.fAxisLen[0] * absC[1][0] + thisBox.fAxisLen[1] * absC[0][0];
		r1 = targetBox.fAxisLen[1] * absC[2][2] + targetBox.fAxisLen[2] * absC[2][1];
		if (r > r0 + r1)
			return false;

		r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
		r0 = thisBox.fAxisLen[0] * absC[1][1] + thisBox.fAxisLen[1] * absC[0][1];
		r1 = targetBox.fAxisLen[0] * absC[2][2] + targetBox.fAxisLen[2] * absC[2][0];
		if (r > r0 + r1)
			return false;

		r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
		r0 = thisBox.fAxisLen[0] * absC[1][2] + thisBox.fAxisLen[1] * absC[0][2];
		r1 = targetBox.fAxisLen[0] * absC[2][1] + targetBox.fAxisLen[1] * absC[2][0];
		if (r > r0 + r1)
			return false;

		return true;
	}

	static D3DXVECTOR3 GetFront(D3DXVECTOR3 rot, D3DXVECTOR3 front)
	{
		D3DXVECTOR3 ret;
		D3DXMATRIX matR;
		D3DXMatrixRotationYawPitchRoll(&matR, rot.y, rot.x, rot.z);
		D3DXVec3TransformCoord(&ret, &front, &matR);
		return ret;
	}
};