#pragma once
#include "Entity.h"
#include "Component.h"
#include "MeshRender.h"

class Script;

// ���ӿ�����Ʈ
class GameObject final : public Entity
{
private:
	array<Component*, (UINT)COMPONENT_TYPE::COUNT_END> components;
	Ptr<MeshRender> meshRender;
	vector<Script*> scripts;

public:
	GameObject();
	~GameObject();
	GameObject* const Clone() { return new GameObject(*this); }

public:
	template<typename T> requires std::derived_from<T, Component> Ptr<T> AddComponent();
	template<typename T> requires std::derived_from<T, Component> Ptr<T> GetComponent();

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

private:
	GameObject(const GameObject& origin);
	GameObject& operator=(const GameObject& other);
};

template<typename T> requires std::derived_from<T, Component>
Ptr<T> GameObject::AddComponent()
{
	Ptr<T> component = GetComponent<T>();

	if (component.Get() != nullptr)
	{
		MessageBoxA(nullptr, "�̹� �ش� ������Ʈ�� �����մϴ�", "������Ʈ �߰� ����", MB_OK);
		return component;
	}
	else
	{
		T* t = Component::Create<T>(*this);
		Ptr<T> ptr(t);
		COMPONENT_TYPE type = Component::GetType<T>();
		components[(UINT)type] = t;

		if (type == COMPONENT_TYPE::MESH_RENDER) meshRender = Ptr<MeshRender>((MeshRender*)t);

		return ptr;
	}
}

template<typename T> requires std::derived_from<T, Component>
Ptr<T> GameObject::GetComponent()
{
	Component* component = components[(UINT)Component::GetType<T>()];

	if (component != nullptr) return Ptr<T>((T*)component);
	else return Ptr<T>();
}