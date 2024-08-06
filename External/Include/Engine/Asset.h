#pragma once
#include "Entity.h"

// ���� Ÿ��
enum class ASSET_TYPE : UINT
{
	MESH, GRAPHIC_SHADER, COUNT_END
};

// ���� �ֻ��� Ŭ����
class Asset : public Entity
{
	friend class AssetManager;

private:
	const wstring Key;
	wstring relativePath;
	const ASSET_TYPE Type;

protected:
	Asset(ASSET_TYPE Type, const wstring& Key, const wstring& relativePath);
	~Asset();

protected:
	const wstring& GetPath() { return relativePath; }

protected:	// ����
	Asset(const Asset&) = delete;
	Asset& operator=(const Asset&) = delete;
};