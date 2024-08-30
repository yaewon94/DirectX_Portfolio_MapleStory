#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"
#include "Player.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Level.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	// Ű �� �ʱ�ȭ
	AddKey(KEY_CODE::LEFT);
	AddKey(KEY_CODE::RIGHT);

	// �÷��̾� �ʱ�ȭ
	player = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::PLAYER)->GetComponent<Player>();
}

void KeyManager::Tick()
{
	// �����찡 ��Ŀ�� ���϶�
	if (Engine::GetInstance()->GetHwnd() == GetFocus())
	{
		for (auto& key : keyMap)
		{
			// �̹� �����ӿ� �ش� Ű�� ����
			if (GetAsyncKeyState(key.first) & 0x8001)
			{
				if (key.second == KEY_STATE::NONE) key.second = KEY_STATE::TAP;
				else if (key.second == KEY_STATE::TAP) key.second = KEY_STATE::KEY_DOWN;

				// TODO : ���� KEY���� ȣ���ϴ� �Լ� �Ϲ�ȭ �ϱ�
				player->Move(key.first);	// �ӽ��ڵ�
			}
			// �ȴ���
			else
			{
				if (key.second == KEY_STATE::NONE) continue;
				else if (key.second == KEY_STATE::RELEASED) key.second = KEY_STATE::NONE;
				else key.second = KEY_STATE::RELEASED;
			}
		}

		// ���콺 ��ǥ üũ
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(Engine::GetInstance()->GetHwnd(), &pos);
		mousePos = Vec2((float)pos.x, (float)pos.y);
	}
	// �����찡 ��Ŀ�� ���� �ƴ�
	else
	{
		for (auto& key : keyMap)
		{
			key.second = KEY_STATE::NONE;
		}
	}
}

void KeyManager::AddKey(KEY_CODE keyCode)
{
	const auto iter = keyMap.find(keyCode);

	if (iter != keyMap.end())
	{
		keyMap.erase(iter);
	}

	keyMap.insert(make_pair(keyCode, KEY_STATE::NONE));
}