#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer(const LAYER_TYPE Type) : Type(Type)
{
}

Layer::~Layer()
{
}

void Layer::AddObject(Ptr<GameObject>& _obj)
{
	// ���� ���̾����� üũ
	if (_obj->GetLayer() != LAYER_TYPE::NONE && _obj->GetLayer() != Type)
	{
		MessageBoxA(nullptr, "�ٸ� Ÿ���� ���̾ �߰��� �� �����ϴ�", "������Ʈ �߰� ����", MB_OK);
		return;
	}

	// �ߺ� �˻�
	for (auto& obj : objs)
	{
		if (_obj.GetAddressOf() == obj.GetAddressOf())
		{
			MessageBoxA(nullptr, "�̹� ��ϵ� ������Ʈ �Դϴ�", "������Ʈ �߰� ����", MB_OK);
			return;
		}
	}

	_obj->SetLayer(Type);
	objs.push_back(_obj);
}

void Layer::Init()
{
	for (auto& obj : objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto& obj : objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (auto& obj : objs)
	{
		obj->FinalTick();
	}
}

void Layer::Render()
{
	for (auto& obj : objs)
	{
		obj->Render();
	}
}