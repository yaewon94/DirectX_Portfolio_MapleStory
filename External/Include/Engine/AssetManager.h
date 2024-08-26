#pragma once
#include "Asset.h"

// ���� ���� Ŭ����
class AssetManager final : public Singleton<AssetManager>
{
	SINGLETON(AssetManager);

private:
	array<map<wstring, Ptr<Asset>>, (UINT)ASSET_TYPE::COUNT_END> assetMapArr;

public:
	template<typename T> requires std::derived_from<T, Asset> 
	Ptr<T> AddAsset(const wstring& Key, const wstring& relativePath)
	{
		Ptr<T> asset = FindAsset<T>();

		if (asset != nullptr)
		{
			MessageBoxA(nullptr, "�ش� KEY�� ���� ������ �̹� �����մϴ�", "���� �߰� ����", MB_OK);
			return asset;
		}
		else
		{
			return AddAssetNoCheck(Key, relativePath);
		}
	}

	template<typename T> requires std::derived_from<T, Asset> 
	Ptr<T> FindAsset(const wstring& Key, const wstring& relativePath = L"")
	{
		auto& assetMap = assetMapArr[(UINT)GetType<T>()];
		const auto iter = assetMap.find(Key);

		if (iter != assetMap.end()) return (iter->second).ptr_dynamic_cast<T>();
		else if (relativePath != L"") return AddAssetNoCheck<T>(Key, relativePath);
		else return nullptr;
	}

private:
	template<typename T> requires std::derived_from<T, Asset>
	Ptr<T> AddAssetNoCheck(const wstring& Key, const wstring& relativePath)
	{
		Ptr<T> asset = Ptr<T>(Key, relativePath);
		assetMapArr[(UINT)GetType<T>()].insert(make_pair(Key, asset.ptr_dynamic_cast<Asset>()));

		return asset;
	}
};