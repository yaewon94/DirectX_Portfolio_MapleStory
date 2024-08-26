#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// .exe ���� ��� �˾Ƴ���
	wchar_t curDir[256];
	GetCurrentDirectory(256, curDir);

	// �θ� ���͸��� �̵�
	for (size_t i = wcslen(curDir) - 1; i > 0; --i)
	{
		if (curDir[i] == L'\\')
		{
			curDir[i] = L'\0';
			break;
		}
	}

	// $(SolutionDir)Output
	contentPath = curDir;
	contentPath += L"\\content\\";
}