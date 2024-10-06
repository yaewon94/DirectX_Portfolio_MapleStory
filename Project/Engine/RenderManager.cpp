#include "pch.h"
#include "RenderManager.h"
#include "Engine.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "AssetManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

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

void RenderManager::AddRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj)
{
	m_cameras[(UINT)type]->AddRenderObj(obj);
}

void RenderManager::DeleteRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj)
{
	m_cameras[(UINT)type]->DeleteRenderObj(obj);
}

void RenderManager::CopyRenderTarget()
{
	Ptr<Texture> rtTex = AssetManager::GetInstance()->FindAsset<Texture>(RENDER_TARGET_TEX_NAME);
	CONTEXT->CopyResource(m_postProcessTex->GetTexture2D().Get(), rtTex->GetTexture2D().Get());
}

int RenderManager::Init()
{
	m_postProcessTex = AssetManager::GetInstance()->CreateTexture(L"PostProcessTex"
																, Engine::GetInstance()->GetResolution()
																, DXGI_FORMAT_R8G8B8A8_UNORM
																, D3D11_BIND_SHADER_RESOURCE);

	if (m_postProcessTex == nullptr) return E_FAIL;
	else return S_OK;
}

void RenderManager::Render()
{
	// ������, ���ҽ� ���ε�
	BindOnGpu();

	// ���� �����ӿ� ������ �� �� �����
	Device::GetInstance()->Clear();

	// ī�޶� ������
	for (auto& cam : m_cameras)
	{
		cam->Render();
	}

	// RenderTarget -> ������ ���
	Device::GetInstance()->Present();
}

void RenderManager::BindOnGpu()
{
	static Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::GLOBAL);
	cb->SetData(&g_global);
	cb->BindOnGpu();
}

Ptr<GameObject> RenderManager::CreateDebugShape(const DebugShapeInfo& info)
{
	Ptr<GameObject> obj;

	obj->GetTransform()->SetLocalPos(info.pos);
	obj->GetTransform()->SetLocalScale(info.scale);
	obj->GetTransform()->SetLocalRotation(info.rotation);

	Ptr<MeshRender> meshRender = obj->AddComponent<MeshRender>();
	ChangeDebugShape(obj, info.shape);
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Debug_Material"));
	meshRender->GetMaterial()->SetColor(info.color);

	obj->SetLayer(LAYER_TYPE::DEBUG);
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