#pragma once
#include "Singleton.h"
#include "Render.h"
#include "CameraValues.h"

class StructuredBuffer;
class Camera;
class GameObject;
class Texture;
class Light2D;
class Texture;

// ������ ��� Ŭ����
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);
	
private:
	map<CAMERA_TYPE, Ptr<Camera>> m_cameraMap;

	Ptr<Texture> m_rtTex;	// Render Target
	Ptr<Texture> m_dsTex;	// Depth Stencil
	Ptr<Texture> m_postProcessTex;	// ��ó���� �ؽ�ó (����Ÿ�� ����뵵)

	vector<Ptr<Light2D>> m_light2Ds;
	Ptr<StructuredBuffer> m_light2dBuffer;

public:
	int ChangeCameraType(Ptr<Camera> camera, CAMERA_TYPE type);
	void AddRenderObj(Ptr<GameObject> obj, CAMERA_TYPE type = CAMERA_TYPE::MAIN_CAMERA);
	void DeleteRenderObj(Ptr<GameObject> obj, CAMERA_TYPE type = CAMERA_TYPE::MAIN_CAMERA);

	void AddLight2D(Ptr<Light2D> light);

public:
	int Init();
	void Render();

public:
	void CopyRenderTarget();

private:
	//void BindOnGpu();
	void Clear();

#ifdef _DEBUG
public:
	void InitDebugShape(Ptr<GameObject> obj, const DebugShapeInfo& info);
	void ChangeDebugShape(Ptr<GameObject> obj, DEBUG_SHAPE shape);
	void ChangeDebugPos(Ptr<GameObject> obj, Vec3 pos);
	void ChangeDebugScale(Ptr<GameObject> obj, Vec3 scale);
#endif // _DEBUG
};