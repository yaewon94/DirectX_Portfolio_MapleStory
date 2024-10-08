#pragma once
#include "Asset.h"

class Shader : public Asset
{
protected:
	ComPtr<ID3DBlob> errorBlob;

protected:
	Shader(const wstring& key, const wstring& relativePath);
	~Shader();

public:
	virtual int Load() final { return S_OK; }
};