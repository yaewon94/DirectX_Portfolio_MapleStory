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
	//GetCurrentDirectory(256, curDir); // �ƹ��͵� �Ȱǵ�ȴµ� ���ڱ� Client ������Ʈ ��ġ�� ��η� �ٲ�
	GetModuleFileName(nullptr, curDir, 256);
	GetParentPath(curDir);
	GetParentPath(curDir);

	// $(SolutionDir)Output
	contentPath = curDir;
	contentPath += L"\\content\\";
}

void PathManager::GetParentPath(wchar_t* path)
{
	// �θ� ���͸��� �̵�
	for (size_t i = wcslen(path) - 1; i > 0; --i)
	{
		if (path[i] == L'\\')
		{
			path[i] = L'\0';
			break;
		}
	}
}