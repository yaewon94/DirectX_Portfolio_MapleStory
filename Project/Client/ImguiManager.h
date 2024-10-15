#pragma once

class EditorUI;

// imgui �������� �����ϴ� Ŭ����
class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

private:
	map<string, EditorUI*> m_mapUI;

public:
	int Init();
	void Progress();

private:
	void Tick();
	void Render();
};