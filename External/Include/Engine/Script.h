#pragma once
#include "Component.h"

// ����� ���� ��ũ��Ʈ ������Ʈ
class Script : public Component
{
	NO_COPY_ASSIGN(Script);

protected:
	Script(const Ptr<GameObject>& owner);
	Script(const Script& origin, const Ptr<GameObject>& owner);
	~Script();

public:
	virtual void Tick() = 0;
	virtual void FinalTick() override {}
};