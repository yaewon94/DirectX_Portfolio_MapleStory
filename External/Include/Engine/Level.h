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
	map<LAYER_TYPE, Ptr<Layer>> m_layerMap;

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
	// @return : layer�� ���ӿ�����Ʈ �� ���� ���� ��ϵ� ��
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);

private:
	// ������Ʈ �߰� ��, �ش� ���̾ ������ �ڵ� �߰�
	void AddLayer(LAYER_TYPE layer);
};