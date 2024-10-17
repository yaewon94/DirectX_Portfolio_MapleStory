#include "pch.h"
#include "TransformUI.h"
#include "Engine/LayerEnums.h"
#include "Engine/Transform.h"

TransformUI::TransformUI(const Ptr<GameObject>& target) 
	: EditorUI(target)
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	Ptr<Transform> tr = GetTarget()->GetTransform();
	Vec3 localPos = tr->GetLocalPos();
	Vec3 localScale = tr->GetLocalScale();
	Vec3 localRot = tr->GetLocalRotation();

	ImGui::Text("Local Position");	// ��� ���ڿ� ���
	ImGui::SameLine(130);			// ���� ��µ� ���ڿ��� ���� ���ο� ��� (@param - Text�� ���ڼ��� �������� ��µ�)
	ImGui::InputFloat3("##pos", localPos);	// �Է�ĭ (@param : �󺧸�, �Է°��� ������ ����)
	//if (ImGui::DragFloat3("##pos", localPos))
	//{
		tr->SetLocalPos(localPos);
	//}

	ImGui::Text("Local Scale");
	ImGui::SameLine(130);
	ImGui::InputFloat3("##scale", localScale);
	//if (ImGui::DragFloat3("##scale", localScale))
	//{
		tr->SetLocalScale(localScale);
	//}

	ImGui::Text("Local Rotation");
	ImGui::SameLine(130);
	localRot = (localRot / XM_PI) * 180.f;
	ImGui::InputFloat3("##Rotation", localRot);
	//if (ImGui::DragFloat3("##Rotation", localRot, 0.1f))
	//{
		localRot = (localRot / 180) * XM_PI;
		tr->SetLocalRotation(localRot);
	//}
}