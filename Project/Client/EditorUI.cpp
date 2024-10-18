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

void EditorUI::SetActive(bool isActive)
{
	m_isActive = isActive;

	for (const auto& child : m_children)
	{
		child->SetActive(isActive);
	}
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
				//ImGui::Separator();
			}
			ImGui::End();
		}
		else
		{
			ImGui::BeginChild(m_name.c_str(), this->GetChildSize());	
			RenderUpdate();
			UINT id = 1;
			for (EditorUI* child : m_children)
			{
				child->Render();
				//ImGui::Separator();
			}
			ImGui::EndChild();
		}
	}
}

void EditorUI::RenderTitle()
{
	// TODO : ��ư ���� �ٸ� Ÿ������ ��µǰ� (�ؽ�Ʈ ������ �ϸ� ## ���� ���ڿ��� ��µǾ����)
	ImGui::Button(GetName().c_str());

	/*ImGui::PushID(0);

	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

	ImGui::PopStyleColor(1);
	ImGui::PopID();*/
}