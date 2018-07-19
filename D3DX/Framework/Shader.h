#pragma once
class Shader
{
public:
	Shader();
	~Shader();

	static LPD3DXEFFECT LoadShader(string path);
	static LPD3DXMESH LoadModel(const char * szFolder, const char * szFile);
};

