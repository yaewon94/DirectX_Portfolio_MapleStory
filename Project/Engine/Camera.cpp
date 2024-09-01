#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "RenderManager.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Render.h"

Ptr<Camera> Camera::mainCamera = nullptr;

Camera::Camera(const Ptr<GameObject>& owner)
	: Component(owner)
	, m_projType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_near(1.f), m_far(500.f)
	, m_aspectRatio(Engine::GetInstance()->GetResolution().y / Engine::GetInstance()->GetResolution().x)
	, m_layers(0xffffffff)	// ��� ���̾� ������
	, m_fov(XM_PI / 2.f)
	, m_width(Engine::GetInstance()->GetResolution().x)
	, m_scale(m_aspectRatio)
{
}

Camera::Camera(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
	auto cam = origin.ptr_dynamic_cast<Camera>();
	m_projType = cam->m_projType;
	m_near = cam->m_near;
	m_far = cam->m_far;
	m_aspectRatio = cam->m_aspectRatio;
	m_layers = cam->m_layers;
	m_fov = cam->m_fov;
	m_width = cam->m_width;
	m_scale = cam->m_scale;
}

Camera::~Camera()
{
}

void Camera::SetLayerOnOff(LAYER_TYPE layer)
{
	// ��ϵ� ���̾��� ���
	if (m_layers & layer)
	{
		// ex. ???????1 & 00000001 => 00000001
		// layer ��Ʈ���� 11111110
		// ???????1 & 11111110 => #######0
		// ? ��Ʈ�� ��ġ�� ���̾ ��ϵǾ� �ִ� ���� ������ #���� 1�� ������,
		// ��ϵǾ� ���� ���� ���� #���� 0�� �ǹǷ� �ٸ� ���̾� ���� ������ ���� ����
		m_layers &= ~layer;
	}
	// ��ϵ��� ���� ���
	else
	{
		// ex. ???????0 | 00000001 => ???????1
		m_layers |= layer;
	}
}

void Camera::Init()
{
	// ���� ī�޶� ����
	if (mainCamera == nullptr)
	{
		this->GetOwner()->SetName(L"Main Camera");
		mainCamera = Ptr<Camera>(this);
	}

	// RenderManager�� ī�޶� ���
	RenderManager::GetInstance()->AddCamera(Ptr<Camera>(this));

	// View��� ��� (TODO : �� ������ ������ �� ���� ȣ��ǵ��� ����)
	Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
	Matrix matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
	m_matView = matTrans;
	g_transform.viewMatrix = m_matView;

	// ������� ��� (TODO : �� ������ ������ �� ���� ȣ��ǵ��� ����)
	m_matProj = XMMatrixOrthographicLH(m_width, m_width * m_aspectRatio, m_near, m_far);
	g_transform.projMatrix = m_matProj;
}

void Camera::FinalTick()
{
}

void Camera::Render()
{
	LevelManager::GetInstance()->Render(m_layers);
}