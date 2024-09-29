#pragma once

class Animator2D;
class Camera;
class Collider2D;
class Component;
class MeshRender;
class RenderComponent;
class Script;
class Transform;

// ������Ʈ Ÿ��
enum class COMPONENT_TYPE
{
	// ����� ���� ������Ʈ Ÿ��
	SCRIPT = -100,

	// ������ ������Ʈ
	RENDER = -1,

	// ���ӿ��� �⺻ ������Ʈ
	TRANSFORM,
	COLLIDER_2D,
	ANIMATOR_2D,
	CAMERA, MESH_RENDER
};

template<typename T> requires std::derived_from<T, Component>
static constexpr COMPONENT_TYPE GetType()
{
	//// TODO : ��Ÿ�ӿ� ������Ʈ �߰��Ҷ� ���� �ȳ����� Ȯ��
	if constexpr (std::is_base_of_v<Script, T>) return COMPONENT_TYPE::SCRIPT;
	if constexpr (std::is_same_v<T, Camera>) return COMPONENT_TYPE::CAMERA;
	if constexpr (std::is_same_v<T, Collider2D>) return COMPONENT_TYPE::COLLIDER_2D;
	if constexpr (std::is_same_v<T, Animator2D>) return COMPONENT_TYPE::ANIMATOR_2D;
	if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;
	if constexpr (std::is_same_v<T, RenderComponent>) return COMPONENT_TYPE::RENDER;
	if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;

	throw std::logic_error(MSG_INVALID_TYPE_CASTING);
}

template<typename T> requires std::derived_from<T, Component>
static constexpr bool IsRenderComponent()
{
	if constexpr (std::is_base_of_v<RenderComponent, T>) return true;
	else return false;
}