#pragma once
#include "Entity.h"

class GameObject;
class MeshRender;
class Transform;
class Script;

// ������Ʈ Ÿ��
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
	, SCRIPT
};

// ���ӿ�����Ʈ�� ������ ������Ʈ Ŭ����
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);
	friend class GameObject;

private:
	template<typename T> requires std::derived_from<T,Component> 
	static T* Create(const GameObject& Owner);

	template<typename T> requires std::derived_from<T,Component> 
	static COMPONENT_TYPE GetType();

private:
	const GameObject& Owner;

protected:
	Component(const GameObject& Owner);
	Component(const Component& origin, const GameObject& Owner);
	~Component();

protected:
	const GameObject& GetOwner() { return Owner; }

private:
	virtual Component* Clone(const GameObject& Owner) = 0;
	void Destroy() { delete this; }

private:
	virtual void Init() {}
	virtual void Tick() {}
	virtual void FinalTick() {}
};

template<typename T> requires std::derived_from<T, Component>
inline T* Component::Create(const GameObject& Owner)
{
	return new T(Owner);
}

template<typename T> requires std::derived_from<T, Component>
inline COMPONENT_TYPE Component::GetType()
{
	// TODO : ��Ÿ�ӿ� ������Ʈ �߰��Ҷ� ���� �ȳ����� Ȯ��
	if constexpr (std::is_base_of_v<Script, T>) return COMPONENT_TYPE::SCRIPT;
	else if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;
	else if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;

	throw std::logic_error("������ Ÿ���� �����ϴ�");
}