#include "pch.h"
#include "TileMap.h"
#include "Device.h"
#include "StructuredBuffer.h"
#include "GameObject.h"
#include "Transform.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

TileMap::TileMap(const Ptr<GameObject>& owner) 
	: MeshRender(owner)
	, m_tileCount(Vec2(1, 1)), m_tileSize(Vec2(100, 100))
	, m_atlas(nullptr)
	, m_tileInfo{}
{
	SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("TileMap_Material"));
}

TileMap::TileMap(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: MeshRender(origin, owner)
{
	auto pOrigin = origin.ptr_dynamic_cast<TileMap>();

	SetAtlasTexture(pOrigin->m_atlas, pOrigin->m_atlasTileCount);
	SetTileIndex(pOrigin->m_atlasTileIndex);
	SetTileCount(pOrigin->m_tileCount);
	SetTileSize(pOrigin->m_tileSize);
}

TileMap::~TileMap()
{
}

void TileMap::SetTileCount(Vec2 count)
{
	if (count.x < 0 || count.y < 0)
	{
		throw std::logic_error("Ÿ�� ������ ���� ������ �����մϴ�");
	}

	m_tileCount = count;
	SetObjectScale();

	// ����ȭ ���� ����
	if (FAILED(m_buffer->CreateOnGpu(sizeof(TileInfo), m_tileCount.x * m_tileCount.y)))
	{
		throw std::logic_error("����ȭ ���� ���� ����");
	}
}

void TileMap::SetTileSize(Vec2 size)
{
	m_tileSize = size;
	SetObjectScale();
}

void TileMap::SetAtlasTexture(const Ptr<Texture>& atlas, Vec2 tileCount)
{
	m_atlas = atlas;
	m_atlasTileCount = tileCount;

	m_tileInfo.leftTopUV = Vec2(m_atlasTileIndex.x / m_atlasTileCount.x
								, m_atlasTileIndex.y / m_atlasTileCount.y);
	m_tileInfo.sliceUV = Vec2(1.f / m_atlasTileCount.x
							, 1.f / m_atlasTileCount.y);
}

void TileMap::SetTileIndex(Vec2 index)
{
	m_atlasTileIndex = index;

	m_tileInfo.leftTopUV = Vec2(m_atlasTileIndex.x / m_atlasTileCount.x
								, m_atlasTileIndex.y / m_atlasTileCount.y);
}

void TileMap::Render()
{
	// ��ǥ
	GetOwner()->GetTransform()->BindOnGpu();

	// ����
	m_material->SetTextureParam(TEX_0, m_atlas);
	m_material->SetScalarParam(VEC2_0, m_tileCount);
	m_material->BindOnGpu();

	// ����ȭ ����
	m_buffer->SetData(&m_tileInfo, 1);
	m_buffer->BindOnGpu(TEXTURE_PARAM::TILEMAP);

	// ������
	GetMesh()->Render();
}

void TileMap::SetObjectScale()
{
	GetOwner()->GetTransform()->SetLocalScale(Vec3(m_tileCount.x * m_tileSize.x
													, m_tileCount.y * m_tileSize.y
													, 1.f));
}