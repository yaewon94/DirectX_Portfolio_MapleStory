#pragma once
#include "Entity.h"
#include "ComponentEnums.h"
#include "LayerEnums.h"

class Component;
class Transform;
class Script;
class RenderComponent;

// ���ӿ�����Ʈ
class GameObject final : public Entity
{
private:
	wstring name;
	LAYER_TYPE layer;

	map<COMPONENT_TYPE, Ptr<Component>> componentMap;
	vector<Ptr<Script>> scripts;
	Ptr<RenderComponent> renderComponent;

	// GetComponent ���� �ٷ� �̿��� �� �ְ�
	Ptr<Transform> transform;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	const wstring& GetName() { return name; }
	LAYER_TYPE GetLayer() { return layer; }
	Ptr<Transform> GetTransform();

	void SetName(const wstring& name) { this->name = name; }
	void SetLayer(LAYER_TYPE layer) { this->layer = layer; }

public:
	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> AddComponent()
	{
		Ptr<T> component = GetComponent<T>();

		if (component != nullptr)
		{
			MessageBoxA(nullptr, "�̹� �ش� ������Ʈ�� �����մϴ�", "������Ʈ �߰� ����", MB_OK);
			return component;
		}
		else
		{
			constexpr COMPONENT_TYPE Type = GetType<T>();
			component = Ptr<T>(Ptr<GameObject>(this));

			// ����� ���� ������Ʈ
			if constexpr (Type == COMPONENT_TYPE::SCRIPT)
			{
				scripts.push_back(component.ptr_dynamic_cast<Script>());
			}
			// ���ӿ��� �⺻ ������Ʈ
			else
			{
				// ������ ������Ʈ ����
				if constexpr (IsRenderComponent<T>())
				{
					if (renderComponent == nullptr)
					{
						renderComponent = component.ptr_dynamic_cast<RenderComponent>();
					}
					else
					{
						MessageBox(nullptr, L"������ ������Ʈ�� �̹� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
						return nullptr;
					}
				}
				else if constexpr (Type == COMPONENT_TYPE::TRANSFORM) transform = component;

				componentMap.insert(make_pair(Type, component.ptr_dynamic_cast<Component>()));
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
			for (auto& script : scripts)
			{
				Ptr<T> component = script.ptr_dynamic_cast<T>();
				if (component != nullptr) return component;
			}

			return nullptr;
		}
		// ������ ������Ʈ
		else if constexpr (Type == COMPONENT_TYPE::RENDER)
		{
			return renderComponent;
		}
		// ���ӿ��� �⺻ ������Ʈ
		else
		{
			const auto iter = componentMap.find(Type);
			if (iter == componentMap.end()) return nullptr;
			else return iter->second.ptr_dynamic_cast<T>();
		}
	}

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

private:
	GameObject(GameObject&&) = delete;
	GameObject& operator=(GameObject&&) = delete;
};