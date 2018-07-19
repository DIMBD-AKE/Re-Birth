#include "../stdafx.h"
#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

LPD3DXEFFECT Shader::LoadShader(string path)
{
	DWORD dwShaderFlags = 0;
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;

#if _DEBUG
	dwShaderFlags != D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(DEVICE,
		path.c_str(),
		NULL, NULL,
		dwShaderFlags,
		NULL,
		&ret, &pError);

	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void * ack = pError->GetBufferPointer();

		if (ack)
		{
			char * str = new char[size];
			strncpy_s(str, size, (const char*)ack, _TRUNCATE);
			OutputDebugString(str);
			SAFE_DELETE_ARRAY(str);
		}
	}

	return ret;
}

LPD3DXMESH Shader::LoadModel(const char * szFolder, const char * szFile)
{
	string sFullPath = string(szFolder);
	sFullPath += szFile;

	LPD3DXMESH ret = NULL;
	D3DXLoadMeshFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		DEVICE,
		NULL, NULL, NULL, NULL,
		&ret);

	return ret;
}
