#include "pch.h"
#include "Layer.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Material.h"
#include "GraphicShader.h"
#include "MeshRender.h"

Layer::Layer(const LAYER_TYPE Type) : m_Type(Type)
{
}

Layer::~Layer()
{
}

Ptr<GameObject> Layer::AddObject(const Ptr<GameObject>& _obj)
{
	// �ߺ� �˻�
	for (auto& obj : m_objs)
	{
		if (obj.GetAddressOf() == _obj.GetAddressOf())
		{
			throw std::logic_error("������Ʈ �߰� ���� : �̹� ��ϵ� ������Ʈ �Դϴ�");
		}
	}

	// ������Ʈ ���
	m_objs.push_back(_obj);

	return _obj;
}

void Layer::DeleteObject(const Ptr<GameObject>& obj)
{
	for (auto iter = m_objs.begin(); iter != m_objs.end(); ++iter)
	{
		if (iter->GetAddressOf() == obj.GetAddressOf())
		{
			m_objs.erase(iter);
			return;
		}
	}

	throw std::logic_error("������Ʈ ���� ���� : �ش� ���̾ ��ϵ� ������Ʈ�� �ƴմϴ�");
}

Ptr<GameObject> Layer::GetGameObject()
{
	// ���� ù��° ��ü ��ȯ
	if (m_objs.size() > 0)  return m_objs[0];

	throw std::logic_error("������Ʈ ã�� ���� : �ش� ���̾ ��ϵ� ������Ʈ�� �����ϴ�");
}

void Layer::Init()
{
	for (auto& obj : m_objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto& obj : m_objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (auto& obj : m_objs)
	{
		obj->FinalTick();
	}
}

// ������Ʈ ������
// ������ > ����ũ > ���� > ��ó�� ������ ������
// TODO : Layer ���� �ٸ� Ŭ�������� ó���ϴ� ��� �����غ��� (������ Layer���� ó���ϴ°� ����ȣ���� ���� ��� �ϴ� ��)
void Layer::Render()
{
	Ptr<RenderComponent> renderComponent = nullptr;

	for (UINT domain = 0; domain < (UINT)SHADER_DOMAIN::COUNT_END; ++domain )
	{
		for (auto& obj : m_objs)
		{
			if ((renderComponent = obj->GetRenderComponent()) != nullptr)
			{
				if ((SHADER_DOMAIN)domain == renderComponent->GetMaterial()->GetShader()->GetDomain())
				{
					obj->Render();
				}
			}
		}
	}
}