#pragma once
#include "Component.h"

enum class LIGHT_TYPE : int
{
	DIRECTIONAL,	// ���⼺ ���� (�¾籤, ��)
	POINT,			// �� ���� (����, ������, ��ų ����Ʈ, ȶ��)
	SPOT,			// ����Ʈ ����Ʈ (������)
};

// Light2D, Light3D �� �θ� Ŭ���� (abstract)
class Light : public Component
{
	NO_COPY_ASSIGN(Light);

protected:
	Light(const Ptr<GameObject>& owner);
	Light(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Light();

public:
	virtual COMPONENT_TYPE GetBaseType() final { return COMPONENT_TYPE::LIGHT; }
};