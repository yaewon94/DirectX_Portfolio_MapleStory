#pragma once
#include "Singleton.h"
#include "Render.h"

class Camera;

// ����� ��� ����
struct DebugShapeInfo
{
	DEBUG_SHAPE shape = DEBUG_SHAPE::RECT;
	Vec3 pos;
	Vec4 color = COLOR_GREEN;

	const float Duration;
	float curTime = 0.f;

	bool hasDepthTest = false;	// �������� ���� ����
};

// ������ ��� Ŭ����
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);

private:
	vector<Ptr<Camera>> cameras;

public:
	void AddCamera(const Ptr<Camera>& camera);

public:
	void Render();
};