#pragma once
#include "Entity.h"
#include "LayerEnums.h"
#include "Render.h"

class GameObject;

// ������Ʈ�� ������ ���� , ������ ���� ���� �����ϴ� ���
class Layer final : public Entity
{
	NO_COPY_ASSIGN(Layer);

private:
	const LAYER_TYPE Type;
	map<SHADER_DOMAIN, vector<Ptr<GameObject>>> renderObjs;
	vector<Ptr<GameObject>> notRenderObjs;

public:
	Layer(const LAYER_TYPE Type);
	~Layer();

public:
	void AddObject(Ptr<GameObject>& _obj);
	Ptr<GameObject> GetGameObject();

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};