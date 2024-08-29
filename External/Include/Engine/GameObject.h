#pragma once
#include "Entity.h"
#include "ComponentEnums.h"
#include "LayerEnums.h"

class Component;
class Transform;
class MeshRender;
class Script;

// ���ӿ�����Ʈ
class GameObject final : public Entity
{
private:
	LAYER_TYPE layer;

	map<COMPONENT_TYPE, Ptr<Component>> componentMap;
	Ptr<Transform> transform;
	Ptr<MeshRender> meshRender;
	vector<Ptr<Script>> scripts;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	LAYER_TYPE GetLayer() { return layer; }
	void SetLayer(LAYER_TYPE layer) { this->layer = layer; }

	Ptr<Transform> GetTransform();

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
				if constexpr (Type == COMPONENT_TYPE::MESH_RENDER) meshRender = component;
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