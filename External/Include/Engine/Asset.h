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
	NO_COPY_ASSIGN(Asset);
	friend class AssetManager;

private:
	const wstring Key;
	wstring relativePath;

protected:
	Asset(const wstring& Key, const wstring& relativePath);
	~Asset();

protected:
	const wstring& GetPath() { return relativePath; }
};