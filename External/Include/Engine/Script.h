#pragma once
#include "Component.h"

// ����� ���� ��ũ��Ʈ ������Ʈ
class Script : public Component
{
	NO_COPY_ASSIGN(Script);

protected:
	Script(const Ptr<GameObject>& owner);
	Script(const Ptr<Script>& origin, const Ptr<GameObject>& owner);
	~Script();

public:
	virtual Ptr<Script> Clone(const Ptr<Script>& origin, const Ptr<GameObject>& owner) = 0;

public:
	virtual void Tick() = 0;
	virtual void FinalTick() override {}

private:
	// delete
	virtual Ptr<Component> Clone(const Ptr<Component>&, const Ptr<GameObject>&) final
	{
		return nullptr;
	}
};