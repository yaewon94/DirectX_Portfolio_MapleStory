#include "pch.h"
#include "TransformUI.h"
#include "Engine/LayerValues.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"

ImVec2 TransformUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 3);

TransformUI::TransformUI(Ptr<GameObject> target)
	: ComponentUI("Transform", target)
	, m_tr(target->GetTransform())
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	Vec3 localPos = m_tr->GetLocalPos();
	Vec3 localScale = m_tr->GetLocalScale();
	Vec3 localRot = m_tr->GetLocalRotation();

	RenderTitle();

	ImGui::Text("Local Position");	// ��� ���ڿ� ���
	ImGui::SameLine(SAMELINE_VALUE);			// ���� ��µ� ���ڿ��� ���� ���ο� ��� (@param - Text�� ���ڼ��� �������� ��µ�)
	ImGui::InputFloat3("##tr_pos", localPos);	// �Է�ĭ (@param : �󺧸�, �Է°��� ������ ����)
	//if (ImGui::DragFloat3("##pos", localPos))
	//{
		m_tr->SetLocalPos(localPos);
	//}

	ImGui::Text("Local Scale");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat3("##tr_scale", localScale);
	//if (ImGui::DragFloat3("##scale", localScale))
	//{
		m_tr->SetLocalScale(localScale);
	//}

	ImGui::Text("Local Rotation");
	ImGui::SameLine(SAMELINE_VALUE);
	localRot = (localRot / XM_PI) * 180.f;
	ImGui::InputFloat3("##tr_rotation", localRot);
	//if (ImGui::DragFloat3("##Rotation", localRot, 0.1f))
	//{
		localRot = (localRot / 180) * XM_PI;
		m_tr->SetLocalRotation(localRot);
	//}
}

Ptr<Component> TransformUI::AddComponent()
{
	return GetTarget()->AddComponent<Transform>().ptr_dynamic_cast<Component>();
}

Ptr<Component> TransformUI::GetComponent(bool isBaseType)
{
	return GetTarget()->GetTransform().ptr_dynamic_cast<Component>();
}