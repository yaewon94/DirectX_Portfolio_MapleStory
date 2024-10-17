#pragma once
#include "EditorUI.h"

class Transform;

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
// TODO : Transform UI â �ݱ⸦ ������ ������ �ʰ� �ؾ� ��
class TransformUI final : public EditorUI
{
	NO_COPY_ASSIGN(TransformUI);
	
public:
	TransformUI(const Ptr<GameObject>& target);
	~TransformUI();

public:
	virtual void RenderUpdate() final;
};