#pragma once
#include "Component.h"

class Material;

// ������ ��� ������Ʈ
class RenderComponent : public Component
{
	NO_COPY_ASSIGN(RenderComponent);

protected:
	Ptr<Material> m_material;

protected:
	RenderComponent(const Ptr<GameObject>& owner);
	RenderComponent(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~RenderComponent();

public:
	void SetMaterial(const Ptr<Material>& material);

public:
	Ptr<Material> GetMaterial();

public:
	virtual void FinalTick() override {}
	virtual void Render() = 0;
};