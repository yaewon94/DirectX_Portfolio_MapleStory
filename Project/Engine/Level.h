#pragma once
#include "Entity.h"
#include "LayerValues.h"

class Layer;
class GameObject;

// ������Ʈ�� �����ϴ� ������ scene ����
// TODO : �߻�Ŭ���� ��ȯ
class Level : public Entity
{
	friend class LevelManager;

private:
	map<LAYER_TYPE, Ptr<Layer>> m_layerMap;

public:
	Level();
	~Level();

private:
	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();

private:
	Ptr<GameObject> AddObject(const Ptr<GameObject>& obj);
	void DeleteObject(const Ptr<GameObject>& obj);

	// @return : layer�� ���ӿ�����Ʈ �� ���� ���� ��ϵ� �� ����
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
};