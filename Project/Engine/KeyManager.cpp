#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"
#include "RenderTest.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	AddKey(KEY_CODE::LEFT);
	AddKey(KEY_CODE::RIGHT);
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

				// [�ӽ��ڵ�]
				MoveTest(key.first);

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
	auto iter = keyMap.find(keyCode);

	if (iter != keyMap.end())
	{
		keyMap.erase(iter);
	}

	keyMap.insert(make_pair(keyCode, KEY_STATE::NONE));
}