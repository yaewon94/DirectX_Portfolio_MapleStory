#pragma once
#include "Singleton.h"
#include "Render.h"

class StructuredBuffer;
class Camera;
class GameObject;
class Texture;
class Light2D;
class Texture;

// ī�޶� index
enum class CAMERA_TYPE : UINT
{
	MAIN_CAMERA
};


// ������ ��� Ŭ����
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);
	
private:
	Ptr<Texture> m_rtTex;	// Render Target
	Ptr<Texture> m_dsTex;	// Depth Stencil

	vector<Ptr<Camera>> m_cameras;
	Ptr<Texture> m_postProcessTex;	// ��ó���� �ؽ�ó (����Ÿ�� ����뵵)

	vector<Ptr<Light2D>> m_light2Ds;
	Ptr<StructuredBuffer> m_light2dBuffer;

public:
	void AddCamera(const Ptr<Camera>& camera);
	void AddLight2D(const Ptr<Light2D>& light);
	void AddRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj);
	void DeleteRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj);
	void CopyRenderTarget();

public:
	int Init();
	void Render();

private:
	//void BindOnGpu();
	void Clear();

#ifdef _DEBUG
public:
	Ptr<GameObject> CreateDebugShape(const DebugShapeInfo& info);
	void ChangeDebugShape(const Ptr<GameObject>& obj, DEBUG_SHAPE shape);
#endif // _DEBUG
};