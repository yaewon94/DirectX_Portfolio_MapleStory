#pragma once
#include "Component.h"

// ������Ʈ�� �浹 ������ ���� ������Ʈ
class Collider2D final : public Component
{
	NO_COPY_ASSIGN(Collider2D);

private:
	Vec3 m_offset;
	Vec3 m_scale;

public:
	Collider2D(const Ptr<GameObject>& owner);
	Collider2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Collider2D();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Collider2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	virtual void Init() final;
	virtual void FinalTick() final {}

#ifdef _DEBUG
private:
	Ptr<GameObject> m_debugObj;
#endif // _DEBUG
};