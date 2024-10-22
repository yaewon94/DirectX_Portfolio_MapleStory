#pragma once
#include "Entity.h"
#include "ComponentEnums.h"
#include "LayerValues.h"

class Component;
class Transform;
class Script;
class RenderComponent;
class Collider;

// ���ӿ�����Ʈ
class GameObject final : public Entity
{
private:
	wstring m_name;
	LAYER_TYPE m_layer;

	map<COMPONENT_TYPE, Ptr<Component>> m_components;	// ���� �⺻ ������Ʈ�� ���
	vector<Ptr<Script>> m_scripts;						// ����� ���� ������Ʈ ���

	Ptr<Transform> m_transform;
	Ptr<RenderComponent> m_renderComponent;
	Ptr<Collider> m_collider;

	Ptr<GameObject> m_parent;
	vector<Ptr<GameObject>> m_children;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	const wstring& GetName() { return m_name; }
	LAYER_TYPE GetLayer() { return m_layer; }
	Ptr<GameObject> GetParent() { return m_parent; }

	// ������Ʈ ���� �����ϱ� ���� �뵵
	Ptr<Transform> GetTransform();

	// �� ������Ʈ�� ����Ÿ�� ������Ʈ �Ѱ����� �����ϴ� �͵�
	Ptr<RenderComponent> GetRenderComponent();
	Ptr<Collider> GetCollider();

	void SetName(const wstring& name) { m_name = name; }
	// 0 �̻��� ���� ���� Level�� ��ϵ�
	void SetLayer(LAYER_TYPE layer);
	void AddChild(const Ptr<GameObject>& child, bool isSameLayer = true);

public:
	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> AddComponent()
	{
		Ptr<T> component = GetComponent<T>();

		if (component != nullptr)
		{
			throw std::logic_error("�̹� �ش� ������Ʈ�� �����մϴ�");
		}
		else
		{
			constexpr COMPONENT_TYPE Type = GetType<T>();
			component = Ptr<T>(Ptr<GameObject>(this));

			// ����� ���� ������Ʈ
			if constexpr (Type == COMPONENT_TYPE::SCRIPT)
			{
				m_scripts.push_back(component.ptr_dynamic_cast<Script>());
			}
			// ���ӿ��� �⺻ ������Ʈ
			else
			{
				// ������ ������Ʈ ����
				if constexpr (IsRenderComponent<T>())
				{
					if (m_renderComponent == nullptr)
					{
						m_renderComponent = component.ptr_dynamic_cast<RenderComponent>();
					}
					else
					{
						MessageBox(nullptr, L"������ ������Ʈ�� �̹� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
						return nullptr;
					}
				}
				// �ݶ��̴� ������Ʈ ����
				else if constexpr (IsColliderComponent<T>())
				{
					if (m_collider == nullptr)
					{
						m_collider = component.ptr_dynamic_cast<Collider>();
					}
					else
					{
						throw std::logic_error("�ݶ��̴� ������Ʈ�� �̹� �����մϴ�");
					}
				}

				m_components.insert(make_pair(Type, component.ptr_dynamic_cast<Component>()));
			}

			return component;
		}
	}

	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> GetComponent()
	{
		constexpr COMPONENT_TYPE Type = GetType<T>();

		// ����� ���� ������Ʈ
		if constexpr (Type == COMPONENT_TYPE::SCRIPT)
		{
			for (auto& script : m_scripts)
			{
				Ptr<T> component = script.ptr_dynamic_cast<T>();
				if (component != nullptr) return component;
			}

			return nullptr;
		}
		// ������ ������Ʈ
		else if constexpr (Type == COMPONENT_TYPE::RENDER)
		{
			return m_renderComponent;
		}
		// �ݶ��̴� ������Ʈ
		else if constexpr (Type == COMPONENT_TYPE::COLLIDER)
		{
			return m_collider;
		}
		// ���ӿ��� �⺻ ������Ʈ
		else
		{
			const auto iter = m_components.find(Type);
			if (iter == m_components.end()) return nullptr;
			else return iter->second.ptr_dynamic_cast<T>();
		}
	}

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

public:
	void OnCollisionEnter(LAYER_TYPE other);
	void OnCollisionStay(LAYER_TYPE other);
	void OnCollisionExit(LAYER_TYPE other);
};