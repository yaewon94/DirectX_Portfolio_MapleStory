#pragma once

// Ű ��
enum KEY_CODE
{
	LEFT = VK_LEFT, RIGHT = VK_RIGHT
};

// Ű ����
enum class KEY_STATE
{
	NONE, TAP, KEY_DOWN, RELEASED
};

// ����� �Է� ó�� Ŭ����
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	map<KEY_CODE, KEY_STATE> keyMap;
	Vec2 mousePos;

public:
	void Init();
	void Tick();

public:
	void AddKey(KEY_CODE keyCode);
};