#pragma once
#include "Asset.h"

// �ؽ�ó ����
class Texture final : public Asset
{
	NO_COPY_ASSIGN(Texture);

private:
	ScratchImage m_img;						// �̹������� �ε�, ���� ���
	ComPtr<ID3D11Texture2D> m_tex2D;		// (ScratchImage)SysMem -> GPUMem
	ComPtr<ID3D11ShaderResourceView> m_srv;	// Shader ���� �ڿ����� ����� �̹���
	D3D11_TEXTURE2D_DESC m_desc;

public:
	Texture(const wstring& Key, const wstring& relativePath);
	~Texture();

public:
	virtual int Load() final;

private:
	void BindOnGpu(int _registerNum);
	void Clear(int _registerNum);
};