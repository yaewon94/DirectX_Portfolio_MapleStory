#include "pch.h"
#include "CameraUI.h"
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

ImVec2 CameraUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 8);


CameraUI::CameraUI(Ptr<GameObject> target) 
	: ComponentUI("Camera", target)
{
}

CameraUI::~CameraUI()
{
}

Ptr<Component> CameraUI::AddComponent()
{
	return GetTarget()->AddComponent<Camera>().ptr_dynamic_cast<Component>();
}

Ptr<Component> CameraUI::GetComponent(bool isBaseType)
{
	return GetTarget()->GetComponent<Camera>().ptr_dynamic_cast<Component>();
}

void CameraUI::RenderUpdate()
{
	static Ptr<Camera> camera = GetTarget()->GetComponent<Camera>();

	RenderTitle();

	// ī�޶� Ÿ�� (������ �켱����)
	int camType = (int)(camera->GetCameraType());
	ImGui::Text("Camera Type\n(Render priority)");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::Combo("##cam_type", &camType, CameraTypeArr, CameraTypeArrSize))
	{
		camera->SetCameraType((CAMERA_TYPE)camType);
	}

	// ���� Ÿ��
	int projType = (int)(camera->GetProjectionType());
	ImGui::Text("Projection");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::Combo("##cam_proj", &projType, ProjTypeArr, ProjTypeArrSize))
	{
		camera->SetProjectionType((PROJECTION_TYPE)projType);
	}

	// ī�޶� ���� Z�� ������ ���� (near ~ far)
	float Near = camera->GetNear();
	float Far = camera->GetFar();
	ImGui::Text("Near");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_near", &Near, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (Near >= Far)
		{
			Near = camera->GetNear();
			MessageBoxA(nullptr, "near���� far������ �۾ƾ� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			camera->SetNear(Near);
		}
	}

	ImGui::Text("Far");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_far", &Far, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (Far <= Near)
		{
			Far = camera->GetFar();
			MessageBoxA(nullptr, "far���� near������ Ŀ�� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			camera->SetFar(Far);
		}
	}

	// ī�޶� ���� X,Y�� ������ ����
	float width = camera->GetViewWidth();
	ImGui::Text("View Width");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_width", &width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (width <= 0.f)
		{
			width = camera->GetViewWidth();
			MessageBoxA(nullptr, "view width ���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			camera->SetViewWidth(width);
		}
	}

	float height = camera->GetViewHeight();
	ImGui::Text("View Height");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_height", &height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (height <= 0.f)
		{
			height = camera->GetViewHeight();
			MessageBoxA(nullptr, "view height ���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			camera->SetViewHeight(height);
		}
	}

	// �������� (3D ������) ���
	if (projType == (int)PROJECTION_TYPE::PERSPECTIVE)
	{
		// �þ߰�
		ImGui::Text("Field of view");
		ImGui::SameLine(SAMELINE_VALUE);
		int fov = camera->GetFieldOfView() * 180.f / XM_PI;
		if (ImGui::InputInt("##cam_fov", &fov, 0))
		{
			camera->SetFieldOfView(fov);
		}
	}
	// �������� (2D ������) ���
	else
	{
		// ���� ����
		ImGui::Text("View Scale");
		ImGui::SameLine(SAMELINE_VALUE);
		float scale = camera->GetScale();
		if (ImGui::InputFloat("##cam_scale", &scale, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (scale <= 0.f)
			{
				scale = camera->GetScale();
				MessageBoxA(nullptr, "view scale ���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
			}
			else
			{
				camera->SetScale(scale);
			}
		}
	}

	// �������� ���̾� ����
	LAYER_TYPES layers = camera->GetRenderLayers();
	ImGui::Text("Layers");
	ImGui::BeginTable("##cam_layers_table", 4);
	for (const auto& tuple : LayerTypeArr)
	{
		LAYER_TYPE layer = std::get<0>(tuple);
		const char* layerName = std::get<1>(tuple);
		bool flag = layer & layers;

		ImGui::TableNextColumn();
		if (ImGui::Checkbox(layerName, &flag))
		{
			camera->SetLayerOnOff(layer);
		}
	}
	ImGui::EndTable();
}