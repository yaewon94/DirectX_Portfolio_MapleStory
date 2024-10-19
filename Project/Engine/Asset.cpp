#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(const string& Key, const string& relativePath)
	: Key(Key), relativePath(relativePath)
{
}

Asset::~Asset()
{
}

// TODO : �̰� ����� �Ǵ°� �³� Ȯ��
const wstring Asset::GetFullPathW()
{
	string fullPath = GetFullPathA();
	wstring fullPath_w;
	fullPath_w.assign(fullPath.begin(), fullPath.end());
	return fullPath_w;
}

const string Asset::GetFullPathA()
{
	return PathManager::GetInstance()->GetContentPath() + relativePath;
}