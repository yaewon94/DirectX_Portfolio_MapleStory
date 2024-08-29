#pragma once
#include "Entity.h"
#include "LayerEnums.h"

class GameObject;

// ������Ʈ�� ������ ���� , ������ ���� ���� �����ϴ� ���
class Layer final : public Entity
{
private:
	const LAYER_TYPE Type;
	vector<Ptr<GameObject>> objs;

public:
	Layer(const LAYER_TYPE Type);
	~Layer();

public:
	void AddObject(Ptr<GameObject>& _obj);
	Ptr<GameObject> GetGameObject() { return objs.at(0); }

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};