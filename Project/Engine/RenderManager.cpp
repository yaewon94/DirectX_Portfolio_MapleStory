#include "pch.h"
#include "RenderManager.h"
#include "Device.h"
#include "Camera.h"
#include "GameObject.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::AddCamera(const Ptr<Camera>& _camera)
{
	// �ߺ� üũ
	for (auto& camera : cameras)
	{
		if (camera.GetAddressOf() == _camera.GetAddressOf())
		{
			MessageBoxA(nullptr, "�̹� ��ϵ� ī�޶� �Դϴ�", "ī�޶� ��� ����", MB_OK);
			return;
		}
	}

	// ī�޶� ���
	cameras.push_back(_camera);
}

void RenderManager::Render()
{
	// ���� �����ӿ� ������ �� �� �����
	Device::GetInstance()->Clear();

	// ī�޶� ������
	for (auto& cam : cameras)
	{
		cam->Render();
	}

	// RenderTarget -> ������ ���
	Device::GetInstance()->Present();
}