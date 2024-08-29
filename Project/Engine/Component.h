#pragma once
#include "Entity.h"
#include "ComponentEnums.h"

class GameObject;

// ���ӿ�����Ʈ�� ������ ������Ʈ Ŭ����
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);

private:
	Ptr<GameObject> owner;

protected:
	Component(const Ptr<GameObject>& owner);
	Component(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Component();

public:
	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) = 0;

public:
	Ptr<GameObject> GetOwner() { return owner; }

public:
	virtual void Init() {}
	virtual void FinalTick() = 0;
};