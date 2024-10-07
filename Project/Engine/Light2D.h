#pragma once
#include "Component.h"

enum class LIGHT_TYPE : int
{
	DIRECTIONAL,	// ���⼺ ���� (�¾籤, ��)
	POINT,			// �� ���� (����, ������, ��ų ����Ʈ, ȶ��)
	SPOT,			// ����Ʈ ����Ʈ (������)
};

struct Light2dInfo
{
	Vec3 color;
	Vec3 worldPos;
	Vec3 dir;
	LIGHT_TYPE type;
	float radius;
	float angle;
};

class Light2D final : public Component
{
private:
	Light2dInfo m_info;

public:
	Light2D(const Ptr<GameObject>& owner);
	Light2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Light2D();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Light2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	const Light2dInfo& GetInfo() { return m_info; }
	
	void SetAngle(float angle) { m_info.angle = angle; }
	void SetColor(Vec3 color) { m_info.color = color; }
	void SetRadius(float radius) { m_info.radius = radius; }
	void SetType(LIGHT_TYPE type) { m_info.type = type; }

public:
	virtual void Init() final;
	virtual void FinalTick() final;
};