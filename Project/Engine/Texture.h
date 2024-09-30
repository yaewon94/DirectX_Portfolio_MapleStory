#pragma once
#include "Asset.h"
#include "Render.h"

// �ؽ�ó ����
class Texture final : public Asset
{
	NO_COPY_ASSIGN(Texture);

private:
	ScratchImage m_img;						// �̹������� �ε�, ���� ���
	ComPtr<ID3D11Texture2D> m_tex2D;		// (ScratchImage)SysMem -> GPUMem
	ComPtr<ID3D11ShaderResourceView> m_srv;	// Shader ���� �ڿ����� ����� �̹���
	D3D11_TEXTURE2D_DESC m_desc;
	TEXTURE_PARAM m_registerNum;

public:
	Texture(const wstring& Key, const wstring& relativePath);
	~Texture();

public:
	TEXTURE_PARAM GetRegisterNum() { return m_registerNum; }
	UINT GetWidth() { return m_desc.Width; }
	UINT GetHeight() { return m_desc.Height; }

public:
	virtual int Load() final;

public:
	void BindOnGpu(TEXTURE_PARAM param);
	void Clear();
};