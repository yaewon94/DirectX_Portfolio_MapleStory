#pragma once

// ������Ʈ, ������Ʈ, ���� ���� �ֻ��� Ŭ����
class Entity
{
private:
	static UINT nextID;

private:
	const UINT ID;
	wstring name;

public:
	UINT GetID() { return ID; }
	const wstring& GetName() { return name; }
	void SetName(const wstring& name) { this->name = name; }

protected:
	Entity();
	Entity(const wstring& name);
	Entity(const Entity& origin);
	~Entity();

protected:
	virtual Entity* Clone() = 0;
};