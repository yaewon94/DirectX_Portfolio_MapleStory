#include "pch.h"
#include "TransformUI.h"
#include "Engine/TransformValues.h"

TransformUI::TransformUI()
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	ImGui::Text("Local Position");	// ��� ���ڿ� ���
	ImGui::SameLine(130);			// ���� ��µ� ���ڿ��� ���� ���ο� ��� (@param - Text�� ���ڼ��� �������� ��µ�)
	float arrPos[3] = {};
	ImGui::InputFloat3("##pos", arrPos);	// �Է�ĭ (@param : �󺧸�, �Է°��� ������ ����)

	ImGui::Text("Local Scale");
	ImGui::SameLine(130);
	float arrScale[3] = { DEFAULT_SCALE_NO_PARENT.x, DEFAULT_SCALE_NO_PARENT.y, DEFAULT_SCALE_NO_PARENT.z };
	ImGui::InputFloat3("##scale", arrScale);

	ImGui::Text("Local Rotation");
	ImGui::SameLine(130);
	float arrRot[3] = {};
	ImGui::InputFloat3("##Rotation", arrRot);
}