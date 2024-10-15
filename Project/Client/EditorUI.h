#pragma once
#include "imgui/imgui.h"

class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

private:
	static UINT nextID;

private:
	const UINT m_ID;
	// imgui ��ü�� �̸��� ������ �Ȱ��� ��ü�� ����Ѵ�
	// ## ���� ���ڿ��� ȭ�鿡 ��µ��� �ʴ´�
	// ex) box##1, box##2 �̷� ������ ���� �̸��� �ٸ���, ȭ�鿡 ��µǴ� �̸��� ���� �� �� �ִ�
	string m_name;
	bool m_isActive;

public:
	EditorUI();
	~EditorUI();

public:
	const string& GetName() { return m_name; }
	bool IsActive() { return m_isActive; }
	
	void SetName(const string& name) { m_name = name + "##" + std::to_string(m_ID); }
	void SetActive(bool isActive) { m_isActive = isActive; }

public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void RenderUpdate() = 0;
};