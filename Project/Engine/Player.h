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
	Player(const Player& origin, const Ptr<GameObject>& owner);
	~Player();

public:
	virtual void Init() final;
	virtual void Tick() final {}

public:
	void Move(KEY_CODE key);
};