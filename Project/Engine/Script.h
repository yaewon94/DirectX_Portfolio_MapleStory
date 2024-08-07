#pragma once
#include "Component.h"

class GameObject;

// ����� ���� ��ũ��Ʈ ������Ʈ
class Script : public Component
{
	NO_COPY_ASSIGN(Script);

protected:
	Script(const GameObject& Owner);
	Script(const Script& origin, const GameObject& Owner);
	~Script();
};