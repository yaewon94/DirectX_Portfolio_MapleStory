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
#include "TileMap.h"

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
		// Ÿ�ϸ� ������Ʈ �߰�
		Ptr<GameObject> obj = Ptr<GameObject>();
		obj->GetTransform()->SetLocalPosY(-100.f);
		Ptr<TileMap> tileMap = obj->AddComponent<TileMap>();
		tileMap->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>(L"TileMapTex", L"TileTest.png"), Vec2(8, 8));
		tileMap->SetTileIndex(Vec2(3, 0));
		tileMap->SetTileCount(Vec2(10, 1));
		obj->SetLayer(LAYER_TYPE::GROUND);

		// �÷��̾� ������Ʈ �߰�
		Ptr<GameObject> g_player = Ptr<GameObject>();
		g_player->AddComponent<Player>();

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
		monster->GetTransform()->SetLocalPosX(400.f);
		Ptr<MeshRender> meshRender = monster->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		// ���� ���� ���
		Ptr<Material> material = AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material").DeepCopy();
		meshRender->SetMaterial(material);
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"MonsterTexture", L"NoiseTest.png"));
		monster->AddComponent<Collider2D>();
		monster->SetLayer(LAYER_TYPE::MONSTER);

		// Post Process Vortex Test
		Ptr<GameObject> post = Ptr<GameObject>();
		post->GetTransform()->SetLocalScale(Vec3(1000.f, 800.f, 0.f));
		meshRender = post->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Vortex_Material"));
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"PostProcessTex"));
		//meshRender->GetMaterial()->SetTextureParam(TEX_1, AssetManager::GetInstance()->FindAsset<Texture>(L"NoiseTex", L"NoiseTest.png"));
		post->SetLayer(LAYER_TYPE::DEFAULT);
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

Ptr<GameObject> Level::AddObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer < LAYER_TYPE::CAMERA)
	{
		throw std::logic_error("���� ������ LAYER_TYPE�� ������Ʈ�� ��� �����մϴ�");
	}

	// ���ӿ�����Ʈ�� ���̾�� ��ġ�ϴ� ���̾ ���
	if (m_layerMap.find(layer) == m_layerMap.end()) m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	return m_layerMap.find(layer)->second->AddObject(obj);
}

void Level::DeleteObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer < LAYER_TYPE::CAMERA) return;
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		throw std::logic_error("������Ʈ ���� ���� : ���� ������ ��ϵ� ���̾ �ƴմϴ�");
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