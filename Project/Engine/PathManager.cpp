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
	char curDir[256];
	//GetCurrentDirectory(256, curDir); // �ƹ��͵� �Ȱǵ�ȴµ� ���ڱ� Client ������Ʈ ��ġ�� ��η� �ٲ�
	GetModuleFileNameA(nullptr, curDir, 256);
	GetParentPath(curDir);
	GetParentPath(curDir);

	// $(SolutionDir)Output
	contentPath = curDir;
	contentPath += "\\content\\";
}

void PathManager::GetParentPath(char* path)
{
	// �θ� ���͸��� �̵�
	for (size_t i = strlen(path) - 1; i > 0; --i)
	{
		if (path[i] == '\\')
		{
			path[i] = '\0';
			break;
		}
	}
}