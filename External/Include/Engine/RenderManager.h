#pragma once
#include "Singleton.h"

class Camera;

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