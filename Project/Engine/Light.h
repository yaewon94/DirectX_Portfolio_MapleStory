#pragma once
#include "Component.h"

enum class LIGHT_TYPE : int
{
	DIRECTIONAL = 0,	// ���⼺ ���� (�¾籤, ��)
	POINT = 1,			// �� ���� (����, ������, ��ų ����Ʈ, ȶ��)
	SPOT = 2,			// ����Ʈ ����Ʈ (������)
};

static const char* LightTypeArr[] = { "Directional", "Point", "Spot" };
static int LightTypeArrSize = sizeof(LightTypeArr) / sizeof(const char*);

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