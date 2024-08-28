#pragma once
#include "Singleton.h"
#include "LayerEnums.h"

class Level;
class GameObject;

// ���� ���� Ŭ����
class LevelManager final : public Singleton<LevelManager>
{
	SINGLETON(LevelManager);

private:
	Ptr<Level> curLevel = nullptr;

public:
	void Init();
	void Tick();
	void Render();

public:
	// @return : ���� ���� layer�� ���ӿ�����Ʈ �� ���� ���� ��ϵ� ��
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
};