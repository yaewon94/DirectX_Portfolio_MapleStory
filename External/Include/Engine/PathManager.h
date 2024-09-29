#pragma once

// ��� ó�� Ŭ����
class PathManager final : public Singleton<PathManager>
{
	SINGLETON(PathManager);

private:
	wstring contentPath;

public:
	wstring GetContentPath() { return contentPath; }

public:
	void Init();

private:
	void GetParentPath(wchar_t* path);
};