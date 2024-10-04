#pragma once
#include "Component.h"
#include "CameraEnums.h"
#include "LayerEnums.h"
#include "Render.h"

class RenderComponent;

// ī�޶� ������Ʈ
// TODO : ���� ī�޶�, �Ϲ� ī�޶� ���� (Ŭ���� ���� �ٸ� �������)
class Camera final : public Component
{
private:
	PROJECTION_TYPE m_projType;	// ���� Ÿ��
	float m_near, m_far;		// ������ ������ �ش�Ǵ� z�� �ּҰ�, �ִ밪
	float m_aspectRatio;		// ���� ���� ��Ⱦ��
	LAYER_TYPES m_layers;		// �������� ���̾� ����

	// �������� (PROJECTION_TYPE::PERSPECTIVE)
	float m_fov;	// field of view (�þ߰�)

	// �������� (PROJECTION_TYPE::ORTHOGRAPHIC)
	float m_width;	// ���� ���α���
	float m_scale;	// ���� ����

	// ��ȯ���
	Matrix m_matView;	// view ���
	Matrix m_matProj;	// projection ���

	// ������ ����
	// (�ѹ� ������ SHADER_DOMAIN, LAYER_TYPE�� �ٲ�� ���� ���� �����Ƿ� list���� vector���)
	map<SHADER_DOMAIN, map<LAYER_TYPE, vector<Ptr<RenderComponent>>>> m_renderMap;

public:
	Camera(const Ptr<GameObject>& owner);
	Camera(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Camera();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Camera>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	void SetLayerOnOff(LAYER_TYPE layer);
	void AddRenderObj(const Ptr<GameObject>& obj);
	void DeleteRenderObj(const Ptr<GameObject>& obj);

public:
	virtual void Init() final;
	virtual void FinalTick() final;
	void Render();

private:
	void OnChangeRotation();
};