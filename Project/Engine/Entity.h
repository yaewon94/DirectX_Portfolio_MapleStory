#pragma once

// ������Ʈ, ������Ʈ, ���� ���� �ֻ��� Ŭ����
// TODO : �߻�Ŭ������ �����
class Entity
{
private:
	static UINT nextID;

private:
	const UINT ID;
	UINT refCount;	// �ش� ��ü�� ���� ���� ����Ʈ ������ ��

public:
	UINT GetID() { return ID; }

protected:
	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();

private:
	// ����Ʈ �����ͷθ� ��ü �����ϵ��� ����
	//template<typename T> requires std::derived_from<T,Entity> friend class Ptr;
	template<typename T> friend class Ptr;

	void AddRefCount() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};