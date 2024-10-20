#include "pch.h"
#include "Material.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "GraphicShader.h"
#include "Texture.h"

Material::Material(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath), m_cb{}
{
}

Material::Material(const Material& origin) : Asset("", "")
{
	*this = origin;
}

Material::~Material()
{
}

Material& Material::operator=(const Material& other)
{
	if (this != &other)
	{
		// 주소 공유 (에셋이므로 깊은복사 X)
		m_shader = other.m_shader;
		m_textures = other.m_textures;

		// 개별 주소
		m_cb = other.m_cb;
	}

	return *this;
}

void Material::BindOnGpu()
{
	if (m_shader != nullptr)
	{
		// Texture
		for (int i=0; i<TEXTURE_PARAM::COUNT_END; ++i)
		{
			if(m_textures[i] != nullptr)
			{
				m_cb.bTex[i] = 1;
				m_textures[i]->BindOnGpu((TEXTURE_PARAM)i);
			}
		}

		// Const Buffer
		static Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::MATERIAL);
		cb->SetData(&m_cb);
		cb->BindOnGpu();

		// Shader
		m_shader->BindOnGpu();
	}
}

Ptr<GraphicShader> Material::GetShader()
{
	return m_shader;
}

void Material::SetShader(const Ptr<GraphicShader>& shader)
{
	m_shader = shader;

	// 알파블렌드 타입일 경우, 불투명도 100%로 초기화
	if (m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND
		|| m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND_COVERAGE)
	{
		SetAlpha(1.f);
	}
}

void Material::SetAlpha(float alpha)
{
	if (m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND 
		|| m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND_COVERAGE)
	{
		if (alpha < 0.f || alpha > 1.f)
		{
			throw std::logic_error("0.f 이상 1.f 이하의 값만 가능합니다");
		}

		m_cb.fArr[0] = alpha;
	}
	else
	{
		throw std::logic_error("알파블렌딩 타입만 알파값을 설정할 수 있습니다");
	}
}

void Material::SetTextureParam(TEXTURE_PARAM type, const Ptr<Texture>& texture)
{
	m_textures[type] = texture;
}

void Material::UnloadTexture(TEXTURE_PARAM param)
{
	if (m_textures[param] == nullptr)
	{
		throw std::logic_error("empty 레지스터 입니다");
	}

	TEXTURE_PARAM registerNum = m_textures[param]->GetRegisterNum();
	m_cb.bTex[registerNum] = 0;
	m_textures[param]->Clear();
	m_textures[param] = nullptr;
}