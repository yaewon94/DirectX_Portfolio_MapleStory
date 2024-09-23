#pragma once
#include "Singleton.h"
#include "LayerEnums.h"

class Collider2D;

// �浹�� �� Collider�� ID
union COLLIDER_ID
{
	struct
	{
		UINT left, right;
	};

	ULONGLONG ID;
};

// �� Collider�� �浹 �˻� ��� Ŭ����
class CollisionManager : public Singleton<CollisionManager>
{
	SINGLETON(CollisionManager);

private:
	map<LAYER_TYPE, vector<Ptr<Collider2D>>> m_colliderMap;
	unordered_set<ULONGLONG> m_collisionSet;

public:
	void AddCollider(const Ptr<Collider2D>& collider);
	void RemoveCollider(const Ptr<Collider2D>& collider);
	
public:
	void Tick();

private:
	void CheckCollision(LAYER_TYPE a, LAYER_TYPE b);
	bool IsCollision(const Ptr<Collider2D>& a, const Ptr<Collider2D>& b);
	void ChangeCollisionSet(UINT a, UINT b, bool isCollision);
};