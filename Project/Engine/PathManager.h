#pragma once

// ��� ó�� Ŭ����
class PathManager final : public Singleton<PathManager>
{
	SINGLETON(PathManager);

private:
	string contentPath;

public:
	string GetContentPath() { return contentPath; }

public:
	void Init();

private:
	void GetParentPath(char* path);
};