#pragma once
#include "EditorUI.h"

class ComponentUI;
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

	template<typename T> requires std::derived_from<T, ComponentUI>
	void AddChild()
	{
		// UI �� �����ϴ� ���
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
		}
		// UI �� �������� �ʴ� ���
		else
		{
			ComponentUI& ui = (ComponentUI&)(RegisterChild<T>(*new T));
			ui.CallbackCreateSuccess();
		}
	}

public:
	virtual void RenderUpdate() final {}
};