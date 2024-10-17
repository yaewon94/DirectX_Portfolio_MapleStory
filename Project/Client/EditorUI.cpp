#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::nextID = 0;

EditorUI::EditorUI(const string& name)
	: m_name(name + "##" + std::to_string(nextID++))
	, m_isActive(true)
	, m_parent(nullptr)
{
}

EditorUI::~EditorUI()
{
	for (EditorUI* child : m_children)
	{
		if (child != nullptr)
		{
			delete child;
			child = nullptr;
		}
	}

	m_parent = nullptr;

	ImguiManager::GetInstance()->DeleteUI(*this);
}

void EditorUI::Render()
{
	if (m_isActive)
	{
		if (m_parent == nullptr)
		{
			// Begin() ~ End() ���� ȣ��� �������� ���� �����쿡 ������
			ImGui::Begin(m_name.c_str(), &m_isActive);
			RenderUpdate();
			for (EditorUI* child : m_children)
			{
				child->Render();
			}
			ImGui::End();
		}
		else
		{
			// TODO : �������� ���̰� ��µǵ��� ����
			ImGui::BeginChild(m_name.c_str());
			RenderUpdate();
			for (EditorUI* child : m_children)
			{
				child->Render();
			}
			ImGui::EndChild();
		}
	}
}