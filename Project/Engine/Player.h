#pragma once
#include "Script.h"
#include "KeyEnums.h"

// �÷��̾� ������Ʈ
class Player final : public Script
{
	NO_COPY_ASSIGN(Player);

private:
	Ptr<Transform> transform;

public:
	Player(const Ptr<GameObject>& owner);
	Player(const Ptr<Script>& origin, const Ptr<GameObject>& owner);
	~Player();

	virtual Ptr<Script> Clone(const Ptr<Script>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Player>(origin, owner).ptr_dynamic_cast<Script>();
	}

public:
	virtual void Init() final;
	virtual void Tick() final {}

public:
	void Move(KEY_CODE key);
};