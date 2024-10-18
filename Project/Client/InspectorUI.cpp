#include "pch.h"
#include "InspectorUI.h"
#include "TransformUI.h"
#include "Collider2DUI.h"
#include "Engine/GameObject.h"

InspectorUI::InspectorUI(const Ptr<GameObject>& target) 
	: EditorUI("Inspector")
	, m_target(target)
{
	// ���ӿ�����Ʈ�� �ʼ��� ������ �־�� �ϴ� ������Ʈ
	AddChild<TransformUI>();

	// TODO : ������Ʈ�� ������ �ִ� ������Ʈ�� �ҷ��ͼ� UI �߰�
	AddChild<Collider2DUI>();
}

InspectorUI::~InspectorUI()
{
}