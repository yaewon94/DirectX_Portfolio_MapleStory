#pragma once
#include "Singleton.h"
#include "Render.h"

class Camera;
class GameObject;
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
	vector<Ptr<Camera>> m_cameras;
	Ptr<Texture> m_postProcessTex;	// ��ó���� �ؽ�ó (����Ÿ�� ����뵵)

public:
	void AddCamera(const Ptr<Camera>& camera);
	void AddRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj);
	void DeleteRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj);
	void CopyRenderTarget();

public:
	int Init();
	void Render();

private:
	void BindOnGpu();

#ifdef _DEBUG
public:
	Ptr<GameObject> CreateDebugShape(const DebugShapeInfo& info);
	void ChangeDebugShape(const Ptr<GameObject>& obj, DEBUG_SHAPE shape);
#endif // _DEBUG
};