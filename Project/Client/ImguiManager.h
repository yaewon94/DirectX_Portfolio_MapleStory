#pragma once

class EditorUI;

// imgui �������� �����ϴ� Ŭ����
class ImguiManager final : public Singleton<ImguiManager>
{
	SINGLETON(ImguiManager);

private:
	map<string, EditorUI*> m_mapUI;

public:
	// EditorUI ���� �̸��� �ߺ����� �ʰ� ó�������Ƿ�, �Ķ���ͷ� �̸��� ���� �ʾƵ� ��
	void AddUI(EditorUI& ui);

public:
	int Init();
	void Progress();

private:
	void Tick();
	void Render();

#ifdef _DEBUG
private:
	void Test_CreateEditorUI();
#endif // _DEBUG
};