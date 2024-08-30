#include "pch.h"
#include "Entity.h"

UINT Entity::nextID = 0;

Entity::Entity() : ID(nextID++), refCount(1)
{
}


Entity::Entity(const Entity& origin) : ID(nextID++), refCount(1)
{
}

Entity::~Entity()
{
	if (refCount > 0) throw std::logic_error("�ش� ��ü�� ���� ������ �Դϴ�");
}