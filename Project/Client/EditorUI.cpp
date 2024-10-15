#include "pch.h"
#include "EditorUI.h"

EditorUI::EditorUI() 
	: m_isActive(true)
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Render()
{
	if (m_isActive)
	{
		// Begin() ~ End() ���� ȣ��� �������� ���� �����쿡 ������
		ImGui::Begin(m_name.c_str(), &m_isActive);
		RenderUpdate();
		ImGui::End();
	}
}