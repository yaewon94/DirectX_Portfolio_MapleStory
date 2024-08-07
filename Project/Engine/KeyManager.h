#pragma once
#include "Player.h"

// ����� �Է� ó�� Ŭ����
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	map<KEY_CODE, KEY_STATE> keyMap;
	Vec2 mousePos;

	Ptr<Player> player;

public:
	void Init();
	void Tick();

public:
	void AddKey(KEY_CODE keyCode);
};