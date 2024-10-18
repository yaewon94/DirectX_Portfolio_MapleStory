#include "pch.h"
#include "RenderManager.h"
#include "Engine.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "StructuredBuffer.h"
#include "AssetManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Light2D.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

#define CLEAR_COLOR Vec4(0.f, 0.f, 0.f, 1.f)

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

// ��������� vector<Ptr<Light2D>> ����, AddLight2D()�� static���� vector<Light2dInfo>�� �����ϸ� �������� �ƴѰ� �ؼ�
// 1) �Ķ���͸� Light2dInfo* �� �޾Ƶ�
///// vector<Light2dInfo> �� �߰��ϰ� �Ǹ� ��ü�� ����Ǿ� �߰��ǹǷ� �ּұ�� �ߺ�üũ�� �� �� ���� ��
// 2) vector<Light2dInfo*>�� �ްԵǸ� ����ȭ ���ۿ� SetData(vector.data()) ȣ�� ��
///// vector.data()�� �����Ͱ� �ƴ� �ּҸ� �Ѱܹ����� ���� �߻�
void RenderManager::AddLight2D(const Ptr<Light2D>& light)
{
	// �ߺ�üũ
	for (auto& _light : m_light2Ds)
	{
		if (_light.GetAddressOf() == light.GetAddressOf())
		{
			throw std::logic_error("�̹� ��ϵ� Light2D �Դϴ�");
		}
	}

	m_light2Ds.push_back(light);

	// 2D ���� ���� ���ε�
	static vector<Light2dInfo> vecInfo;
	vecInfo.push_back(light->GetInfo());

	if (m_light2dBuffer->GetElementCount() < vecInfo.size())
	{
		m_light2dBuffer->CreateOnGpu(sizeof(Light2dInfo), (UINT)vecInfo.size());
	}
	m_light2dBuffer->SetData(vecInfo.data(), vecInfo.size());
	m_light2dBuffer->BindOnGpu(TEXTURE_PARAM::LIGHT_2D);

	// TODO : �� �����Ӹ��� �ٲ�� ������ �߰��Ǹ� BindOnGpu()���� ȣ���� ��
	// ���� ���� ���ε�
	static Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::GLOBAL);
	g_global.Light2dCount = (int)m_light2Ds.size();
	cb->SetData(&g_global);
	cb->BindOnGpu();
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
	// Render Target Texture, Depth Stencil Texture
	m_rtTex = AssetManager::GetInstance()->FindAsset<Texture>(L"RenderTargetTex");
	m_dsTex = AssetManager::GetInstance()->FindAsset<Texture>(L"DepthStencilTex");

	// ViewPort ���� (Window ȭ�� ���� ����)
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	viewport.Width = Engine::GetInstance()->GetResolution().x;
	viewport.Height = Engine::GetInstance()->GetResolution().y;

	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;

	CONTEXT->RSSetViewports(1, &viewport);

	// Rendering �������� ����
	CONTEXT->OMSetRenderTargets(1, m_rtTex->GetRenderTargetView().GetAddressOf(), m_dsTex->GetDepthStencilView().Get());

	// Post Process Texture
	m_postProcessTex = AssetManager::GetInstance()->CreateTexture(L"PostProcessTex"
																, Engine::GetInstance()->GetResolution()
																, DXGI_FORMAT_R8G8B8A8_UNORM
																, D3D11_BIND_SHADER_RESOURCE);

	if (m_postProcessTex == nullptr) return E_FAIL;
	else return S_OK;
}

void RenderManager::Render()
{
	// ���� ������ Target Ŭ����
	Clear();

	// ������ �� ���ҽ� ���ε�
	//BindOnGpu();

	// ī�޶� ������
	for (auto& cam : m_cameras)
	{
		cam->Render();
	}
}

void RenderManager::Clear()
{
	CONTEXT->ClearRenderTargetView(m_rtTex->GetRenderTargetView().Get(), CLEAR_COLOR);
	CONTEXT->ClearDepthStencilView(m_dsTex->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

//void RenderManager::BindOnGpu()
//{
//}

void RenderManager::InitDebugShape(const Ptr<GameObject>& obj, const DebugShapeInfo& info)
{
	ChangeDebugPos(obj, info.pos);
	ChangeDebugScale(obj, info.scale);
	obj->GetTransform()->SetLocalRotation(info.rotation);

	Ptr<MeshRender> meshRender = obj->AddComponent<MeshRender>();

	ChangeDebugShape(obj, info.shape);
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Debug_Material"));
	meshRender->GetMaterial()->SetColor(info.color);

	obj->SetLayer(LAYER_TYPE::DEBUG);
	obj->Init();
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

void RenderManager::ChangeDebugPos(const Ptr<GameObject>& obj, Vec3 pos)
{
	obj->GetTransform()->SetLocalPos(pos);
}

void RenderManager::ChangeDebugScale(const Ptr<GameObject>& obj, Vec3 scale)
{
	obj->GetTransform()->SetLocalScale(scale);
}