#pragma once
#include "Singleton.h"
#include "LayerValues.h"

class Collider;

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
	map<LAYER_TYPE, vector<Ptr<Collider>>> m_colliderMap;
	unordered_set<ULONGLONG> m_collisionSet;	// �浹�� �� �ݶ��̴� �����

public:
	void AddCollider(const Ptr<Collider>& collider);
	void RemoveCollider(const Ptr<Collider>& collider);
	
public:
	void Tick();

private:
	// �ٸ� Ÿ���� ���̾ ���� ������Ʈ �ݶ��̴����� �浹 �˻�
	void CheckCollision(LAYER_TYPE a, LAYER_TYPE b);
	// �浹 ���� �Ǻ�
	bool IsCollision(const Ptr<Collider>& a, const Ptr<Collider>& b);
	// ���� �����Ӱ� ���Ͽ� ������ �̺�Ʈ ȣ��, m_CollisionSet�� �߰� �Ǵ� ����
	void ChangeCollisionSet(const Ptr<Collider>& a, const Ptr<Collider>& b, bool isCollision);
};