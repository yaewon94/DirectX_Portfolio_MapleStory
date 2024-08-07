#pragma once
#include "Entity.h"

// ������Ʈ Ÿ��
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
};

// ���ӿ�����Ʈ�� ������ ������Ʈ Ŭ����
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);
	friend class GameObject;

private:
	const GameObject& Owner;

protected:
	Component(const GameObject& Owner);
	Component(const Component& origin, const GameObject& Owner);
	~Component();
	virtual Component* Clone(const GameObject& Owner) = 0;

protected:
	virtual void Init() {}
	virtual void Tick() {}
	virtual void FinalTick() {}
};