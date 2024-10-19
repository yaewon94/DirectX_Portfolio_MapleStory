#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
// TODO : Transform UI â �ݱ⸦ ������ ������ �ʰ� �ؾ� ��
class TransformUI final : public ComponentUI
{
	NO_COPY_ASSIGN(TransformUI);

private:
	static ImVec2 s_childSize;

public:
	TransformUI(Ptr<GameObject> target);
	~TransformUI();

public:
	virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;

	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};