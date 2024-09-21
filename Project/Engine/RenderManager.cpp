#include "pch.h"
#include "RenderManager.h"
#include "Device.h"
#include "AssetManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Material.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::AddCamera(const Ptr<Camera>& _camera)
{
	// �ߺ� üũ
	for (auto& camera : m_cameras)
	{
		if (camera.GetAddressOf() == _camera.GetAddressOf())
		{
			MessageBoxA(nullptr, "�̹� ��ϵ� ī�޶� �Դϴ�", "ī�޶� ��� ����", MB_OK);
			return;
		}
	}

	// ī�޶� ���
	m_cameras.push_back(_camera);
}

void RenderManager::Render()
{
	// ���� �����ӿ� ������ �� �� �����
	Device::GetInstance()->Clear();

	// ī�޶� ������
	for (auto& cam : m_cameras)
	{
		cam->Render();
	}

#ifdef _DEBUG
	// Debug Shape ������
	for (auto& obj : m_debugObjs)
	{
		obj->Render();
	}
#endif // _DEBUG

	// RenderTarget -> ������ ���
	Device::GetInstance()->Present();
}

Ptr<GameObject> RenderManager::AddDebugShape(const DebugShapeInfo& info)
{
	Ptr<GameObject> obj;

	obj->SetLayer(LAYER_TYPE::DEBUG);
	obj->GetTransform()->SetLocalPos(info.pos);
	obj->GetTransform()->SetLocalScale(info.scale);
	obj->GetTransform()->SetLocalRotation(info.rotation);

	Ptr<MeshRender> meshRender = obj->AddComponent<MeshRender>();
	ChangeDebugShape(obj, info.shape);
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Debug_Material"));
	ChangeDebugColor(obj, info.color);

	m_debugObjs.push_back(obj);
	obj->Init();

	return obj;
}

void RenderManager::ChangeDebugShape(const Ptr<GameObject>& obj, DEBUG_SHAPE shape)
{
	switch (shape)
	{
	case DEBUG_SHAPE::RECT:
		obj->GetComponent<MeshRender>()->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh_D"));
		break;
	default:
		throw std::logic_error("���¿� ��ϵ��� ���� Debug Shape �Դϴ�");
	}
}

void RenderManager::ChangeDebugColor(const Ptr<GameObject>& obj, Vec4 color)
{
	obj->GetComponent<MeshRender>()->GetMaterial()->SetColor(color);
}