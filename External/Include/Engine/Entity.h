#pragma once

// ������Ʈ, ������Ʈ, ���� ���� �ֻ��� Ŭ����
// TODO : �߻�Ŭ������ �����
class Entity : public IPtrReleasable
{
private:
	static UINT nextID;

private:
	const UINT ID;

public:
	UINT GetID() { return ID; }

protected:
	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();
};