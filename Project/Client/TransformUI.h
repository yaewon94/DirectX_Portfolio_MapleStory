#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
// TODO : Transform UI â �ݱ⸦ ������ ������ �ʰ� �ؾ� ��
class TransformUI final : public ComponentUI
{
	NO_COPY_ASSIGN(TransformUI);

public:
	TransformUI();
	~TransformUI();

public:
	virtual void RenderUpdate() final;

private:
	virtual void AddComponent() final;
	virtual Ptr<Component> GetComponent() final;
};