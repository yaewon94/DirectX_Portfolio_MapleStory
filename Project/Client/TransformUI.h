#pragma once
#include "EditorUI.h"

class GameObject;

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
class TransformUI final : public EditorUI
{
	NO_COPY_ASSIGN(TransformUI);
	
private:
	Ptr<GameObject> target;

public:
	TransformUI();
	~TransformUI();

public:
	virtual void RenderUpdate() final;
};