#include "pch.h"
#include "Level.h"
#include "Layer.h"

#include "GameObject.h"
#include "MeshRender.h"
#include "Player.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "Texture.h"

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
		g_player->AddComponent<Player>();
		Ptr<MeshRender> meshRender = g_player->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		meshRender->SetShader(AssetManager::GetInstance()->FindAsset<GraphicShader>(L"Std2D_Shader"));

		// �ؽ�ó ���� ����
		Ptr<Texture> texture = AssetManager::GetInstance()->FindAsset<Texture>(L"TextureTest", L"Poby.jpeg");
		if (texture == nullptr)
		{
			assert(nullptr);
		}
		g_player->GetComponent<MeshRender>()->SetTexture(texture);

		AddObject(LAYER_TYPE::PLAYER, g_player);
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

void Level::AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj)
{
	if (m_layerMap.find(layer) == m_layerMap.end()) AddLayer(layer);
	m_layerMap.find(layer)->second->AddObject(obj);
}

Ptr<GameObject> Level::GetGameObject(LAYER_TYPE layer)
{
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		MessageBoxA(nullptr, "�ش� ���̾��� ������Ʈ�� �����ϴ�", "������Ʈ ã�� ����", MB_OK);
		return nullptr;
	}
	else
	{
		return iter->second->GetGameObject();
	}
}

void Level::AddLayer(LAYER_TYPE layer)
{
	if (m_layerMap.find(layer) == m_layerMap.end())
	{
		m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	}
}