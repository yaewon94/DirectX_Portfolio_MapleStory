#pragma once
#include "MeshRender.h"

class Texture;
class StructuredBuffer;

// Ÿ�� ������ ����
struct TileInfo
{
	Vec2 leftTopUV;
	Vec2 sliceUV;
};

// Ÿ�� ������ ������Ʈ
class TileMap final : public MeshRender
{
	NO_COPY_ASSIGN(TileMap);

private:
	Vec2 m_tileCount;	// �������� Ÿ�� ����
	Vec2 m_tileSize;	// ���� Ÿ�� ������

	Ptr<Texture> m_atlas;
	Vec2 m_atlasTileCount;	// ��Ʋ�� �ؽ�ó�� �ִ� Ÿ���� ����
	Vec2 m_atlasTileIndex;	// �������� Ÿ���� �ε���

	TileInfo m_tileInfo;
	Ptr<StructuredBuffer> m_buffer;	// Ÿ�������� GPU�� ������ �� ���

public:
	TileMap(const Ptr<GameObject>& owner);
	TileMap(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~TileMap();

public:
	void SetTileCount(Vec2 count);
	void SetTileSize(Vec2 size);
	void SetAtlasTexture(const Ptr<Texture>& atlas, Vec2 tileCount);
	void SetTileIndex(Vec2 index);
	
public:
	virtual void Render() final;

private:
	void SetObjectScale();
};