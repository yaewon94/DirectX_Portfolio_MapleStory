#pragma once

class Component;
class Transform;
class MeshRender;
class Script;

// ������Ʈ Ÿ��
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
	, SCRIPT
};

template<typename T> requires std::derived_from<T, Component>
static COMPONENT_TYPE GetType()
{
	//// TODO : ��Ÿ�ӿ� ������Ʈ �߰��Ҷ� ���� �ȳ����� Ȯ��
	if constexpr (std::is_base_of_v<Script, T>) return COMPONENT_TYPE::SCRIPT;
	if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;
	if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;

	throw std::logic_error(MSG_INVALID_TYPE_CASTING);
}