#pragma once
#include "EditorUI.h"

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
class TransformUI final : public EditorUI
{
	NO_COPY_ASSIGN(TransformUI);

public:
	TransformUI();
	~TransformUI();

public:
	virtual void RenderUpdate() final;
};