#pragma once
#include "EditorUI.h"

class GameObject;

// �ϳ��� ���ӿ�����Ʈ�� ������ �ִ� ��� ������Ʈ���� ���������� �����ִ� UI
class InspectorUI final : public EditorUI
{
	NO_COPY_ASSIGN(InspectorUI);

private:
	Ptr<GameObject> m_target;

public:
	InspectorUI(const Ptr<GameObject>& target);
	~InspectorUI();

public:
	Ptr<GameObject> GetTarget() const { return m_target; }

public:
	virtual void RenderUpdate() final;
};