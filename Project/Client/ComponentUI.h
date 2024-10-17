#pragma once
#include "EditorUI.h"

class Component;
class GameObject;

// ���ӿ�����Ʈ�� ������ �ִ� ������Ʈ ���� ���� �����ϴ� UI
class ComponentUI : public EditorUI
{
	NO_COPY_ASSIGN(ComponentUI);

protected:
	ComponentUI(const string& name);
	~ComponentUI();

protected:
	virtual void AddComponent() = 0;
	virtual Ptr<Component> GetComponent() = 0;

public:
	void CallbackCreateSuccess();

//protected:
//	void SetComponentTitle();
};