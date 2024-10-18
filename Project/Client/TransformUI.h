#pragma once
#include "ComponentUI.h"

class Component;

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
// TODO : Transform UI â �ݱ⸦ ������ ������ �ʰ� �ؾ� ��
class TransformUI final : public ComponentUI
{
	NO_COPY_ASSIGN(TransformUI);

private:
	static ImVec2 s_childSize;

public:
	TransformUI();
	~TransformUI();

public:
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;

private:
	virtual void AddComponent() final;
	virtual Ptr<Component> GetComponent() final;
};