#pragma once
#include "Entity.h"
#include "LayerEnums.h"

class GameObject;

// ������Ʈ�� ������ ���� , ������ ���� ���� �����ϴ� ���
class Layer final : public Entity
{
private:
	vector<Ptr<GameObject>> objs;

public:
	Layer();
	~Layer();

public:
	void AddObject(Ptr<GameObject>& _obj);

public:
public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};