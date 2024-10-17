#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"

class ComponentUI;
class EditorUI;

template<typename T>
concept not_component_ui = std::is_base_of_v<EditorUI, T> && !std::is_base_of_v<ComponentUI, T>;

// �����͸�� ��� UI���� �ֻ��� Ŭ���� (�߻�Ŭ����)
// TODO : ���ӿ�����Ʈ ���� ���
// TODO : �� EditorUI�� X ǥ�ø� ������ �ش� ������Ʈ ���� (TransformUI ����)
// TODO : UI ������ ��ũ��Ʈ���� ����
class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

// static members
private:
	static UINT nextID;

// about EditorUI
private:
	bool m_isActive;
	// imgui ��ü�� �̸��� ������ �Ȱ��� ��ü�� ����Ѵ�
	// ## ���� ���ڿ��� ȭ�鿡 ��µ��� �ʴ´�
	// ex) box##1, box##2 �̷� ������ ���� �̸��� �ٸ���, ȭ�鿡 ��µǴ� �̸��� ���� �� �� �ִ�
	const string m_name;

	EditorUI* m_parent;
	vector<EditorUI*> m_children;

// Constructor, Destructor
public:
	EditorUI(const string& name);
	virtual ~EditorUI();

// [public] Getter, Setter
public:
	const string& GetName() { return m_name; }
	bool IsActive() { return m_isActive; }
	const EditorUI* const GetParent() { return m_parent; }
	
	template<typename T> requires std::derived_from<T, EditorUI>
	EditorUI* GetChild()
	{
		for (EditorUI* child : m_children)
		{
			if (dynamic_cast<T*>(child) != nullptr)
			{
				return child;
			}
		}

		return nullptr;
	}

	void SetActive(bool isActive);
	
	// ���ø� �޼ҵ�� virtual ��� �Ұ��� �� ������� ��
	template<typename T> requires not_component_ui<T>
	void AddChild()
	{
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
		}

		RegisterChild<T>(new T);
	}

// about EditorUI functions called every frame
public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void RenderUpdate() = 0;

protected:
	// ���� UI ��ü�� �޸𸮿� ���
	template<typename T> requires std::derived_from<T, EditorUI>
	void RegisterChild(T& t)
	{
		m_children.push_back(&t);
		m_children.back()->m_parent = this; // �θ� ����
		ImguiManager::GetInstance()->AddUI(*m_children.back()); // ImguiManager�� ���
	}
};