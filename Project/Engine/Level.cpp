#include "pch.h"
#include "Level.h"
#include "Layer.h"

#include "GameObject.h"
#include "MeshRender.h"
#include "Player.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"
#include "Collider2D.h"
#include "Animator2D.h"
#include "Sprite.h"

Level::Level()
{
}

Level::~Level()
{
	m_layerMap.clear();
}

void Level::Init()
{
	{	 
		// [�ӽ�]
		// �÷��̾� ������Ʈ �߰�
		Ptr<GameObject> g_player = Ptr<GameObject>();
		g_player->SetName(L"Player");
		g_player->SetLayer(LAYER_TYPE::PLAYER);
		g_player->AddComponent<Player>();
		g_player->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 0.f));
		g_player->AddComponent<Collider2D>();
		Ptr<Sprite> sprite = AssetManager::GetInstance()->AddAsset<Sprite>(L"PlayerIdleSprite", L"");
		sprite->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>(L"PlayerIdleTexture", L"Player/Idle.png"), 3);
		Ptr<Animator2D> animator = g_player->AddComponent<Animator2D>();
		animator->AddSprite("Idle", sprite);
		animator->ChangeAnimation("Idle");

		//// �÷��̾��� �ڽ� ������Ʈ �߰�
		//Ptr<GameObject> child = Ptr<GameObject>();
		//child->SetName(L"PlayerChild");
		//meshRender = child->AddComponent<MeshRender>();
		//meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		//meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material"));
		//meshRender->GetMaterial()->SetAlpha(0.2f);
		//g_player->AddChild(child);

		// ���� ������Ʈ �߰�
		Ptr<GameObject> monster = Ptr<GameObject>();
		monster->SetLayer(LAYER_TYPE::MONSTER);
		monster->GetTransform()->SetLocalPosX(400.f);
		Ptr<MeshRender> meshRender = monster->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		// ���� ���� ���
		Ptr<Material> material = AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material").DeepCopy();
		meshRender->SetMaterial(material);
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"MonsterTexture", L"NoiseTest.png"));
		monster->AddComponent<Collider2D>();
	}

	for (auto& layer : m_layerMap)
	{
		layer.second->Init();
	}
}

void Level::Tick()
{
	for (auto& layer : m_layerMap)
	{
		layer.second->Tick();
	}
}

void Level::FinalTick()
{
	for (auto& layer : m_layerMap)
	{
		layer.second->FinalTick();
	}
}

void Level::Render(LAYER_TYPES layers)
{
	// ���� ������ ��ϵ� ���̾� ��
	for (auto& pair : m_layerMap)
	{
		// ���̾� ���տ� ��ϵ� ��� ������
		if (layers & pair.first)
		{
			pair.second->Render();
		}
	}
}

Ptr<GameObject> Level::AddObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();

	// ���ӿ�����Ʈ�� ���̾�� ��ġ�ϴ� ���̾ ���
	if (m_layerMap.find(layer) == m_layerMap.end()) m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	return m_layerMap.find(layer)->second->AddObject(obj);
}

void Level::DeleteObject(const Ptr<GameObject>& obj)
{
	const auto iter = m_layerMap.find(obj->GetLayer());

	if (iter == m_layerMap.end())
	{
		if (obj->GetLayer() != LAYER_TYPE::DEFAULT)
		{
			throw std::logic_error("������Ʈ ���� ���� : ���� ������ ��ϵ� ���̾ �ƴմϴ�");
		}
	}
	else
	{
		iter->second->DeleteObject(obj);

		if (iter->second->IsEmpty())
		{
			iter->second = nullptr;
			m_layerMap.erase(iter);
		}
	}
}

Ptr<GameObject> Level::GetGameObject(LAYER_TYPE layer)
{
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		throw std::logic_error("������Ʈ ã�� ���� : ���� ������ ��ϵ� ���̾ �ƴմϴ�");
	}
	else
	{
		return iter->second->GetGameObject();
	}
}