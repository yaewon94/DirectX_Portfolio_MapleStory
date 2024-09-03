#include "pch.h"
#include "Texture.h"
#include "Device.h"

Texture::Texture(const wstring& Key, const wstring& relativePath) 
	: Asset(Key, relativePath)
	, m_desc{}
{
}

Texture::~Texture()
{
}

int Texture::Load()
{
	HRESULT result;
	const wstring Path = GetFullPath();

	// ==========================
	// ���� => System Memory
	// ==========================
	wchar_t szExt[10] = {};
	_wsplitpath_s(Path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);
	wstring strExt = szExt;

	if (strExt == L".dds" || strExt == L".DDS")
	{
		result = LoadFromDDSFile(Path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_img);
	}
	else if (strExt == L".tga" || strExt == L".TGA")
	{
		result = LoadFromTGAFile(Path.c_str(), nullptr, m_img);
	}
	else
	{
		// WIC : Window Image Component (.png, .jpg, .jpeg, .bmp)
		result = LoadFromWICFile(Path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_img);
	}

	if (FAILED(result))
	{
		MessageBox(nullptr, L"�ؽ�ó �ε� ����", L"�ؽ�ó �ε� ����", MB_OK);
		return E_FAIL;
	}

	// ==========================
	// System Memory => GPU
	// ==========================
	CreateShaderResourceView(DEVICE.Get()
		, m_img.GetImages()
		, m_img.GetImageCount()
		, m_img.GetMetadata()
		, m_srv.GetAddressOf());

	// Shader Resource View �� �̿��� ������ü(Texture2D) ���� �˾Ƴ���
	// ScratchImage => Texture2D
	m_srv->GetResource((ID3D11Resource**)m_tex2D.GetAddressOf());

	// Texture2D�� desc ����
	m_tex2D->GetDesc(&m_desc);

	return S_OK;
}

void Texture::BindOnGpu(int _registerNum)
{
	// Pixel Shader Stage
	CONTEXT->PSSetShaderResources(_registerNum, 1, m_srv.GetAddressOf());
}

void Texture::Clear(int _registerNum)
{
	ID3D11ShaderResourceView* srv = nullptr;
	CONTEXT->PSSetShaderResources(_registerNum, 1, &srv);
}