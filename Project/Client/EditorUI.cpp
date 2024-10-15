#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::nextID = 0;

EditorUI::EditorUI() 
	: m_ID(nextID++), m_isActive(true)
{
	m_name = "##" + std::to_string(m_ID);
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