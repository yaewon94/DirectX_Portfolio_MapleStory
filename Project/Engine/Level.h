#pragma once
#include "Entity.h"
#include "LayerEnums.h"

class Layer;
class GameObject;

// ������Ʈ�� �����ϴ� ������ scene ����
// TODO : �߻�Ŭ���� ��ȯ
class Level : public Entity
{
private:
	array<Ptr<Layer>, (UINT)LAYER_TYPE::COUNT_END> layers;

public:
	Level();
	~Level();

public:
	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();
	virtual void Render() final;

public:
	void AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj);
};