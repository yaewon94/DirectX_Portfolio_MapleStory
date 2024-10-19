#include "pch.h"
#include "Animator2D.h"
#include "AssetManager.h"
#include "Sprite.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameObject.h"
#include "TimeManager.h"

Animator2D::Animator2D(const Ptr<GameObject>& owner)
	: MeshRender(owner)
	, m_curAnim(nullptr)
	, m_curIndex(0)
	, m_playTime(0.f)
{
	SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Std2D_AlphaBlend_Material"));
}

Animator2D::Animator2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: MeshRender(origin, owner)
	, m_curIndex(0)
	, m_playTime(0.f)
{
	auto pOrigin = origin.ptr_dynamic_cast<Animator2D>();

	for (auto& pair : pOrigin->m_spriteMap)
	{
		m_spriteMap.insert(make_pair(pair.first, pair.second));
	}

	m_curAnim = pOrigin->m_curAnim;
}

Animator2D::~Animator2D()
{
}

void Animator2D::AddSprite(const string& Key, const Ptr<Sprite>& sprite)
{
	if (m_spriteMap.find(Key) != m_spriteMap.end()) throw std::logic_error("�̹� �����ϴ� Key�� �Դϴ�");
	else m_spriteMap.insert(make_pair(Key, sprite));
}

void Animator2D::ChangeAnimation(const string& Key)
{
	const auto iter = m_spriteMap.find(Key);

	if (iter == m_spriteMap.end())
	{
		throw std::logic_error("�ش� Key���� �������� �ʽ��ϴ�");
	}
	else
	{
		m_curAnim = iter->second;
		m_curIndex = 0;
		m_playTime = 0.f;
		GetMaterial()->SetTextureParam(TEX_0, m_curAnim->GetAtlasTexture());
	}
}

void Animator2D::FinalTick()
{
	float term = (1.f / m_curAnim->GetFPS());	// ������ �� ����

	if (m_playTime > term)
	{
		m_playTime = 0.f;

		if (++m_curIndex == m_curAnim->GetFrameCount())
		{
			if (!m_curAnim->IsRepeat())
			{
				// TODO : ���� �ִϸ��̼� ���� �Ǵ� �ٸ� �ִϸ��̼����� ��ȯ
			}
		}
	}
	else
	{
		m_playTime += TimeManager::GetInstance()->GetDeltaTime();
	}

}

void Animator2D::Render()
{
	m_curAnim->BindOnGpu(m_curIndex);
	MeshRender::Render();
	m_curAnim->Clear();
}