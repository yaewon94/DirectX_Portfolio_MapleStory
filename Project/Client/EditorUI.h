#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"

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
	~EditorUI();

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

	void SetActive(bool isActive) { m_isActive = isActive; }
	template<typename T> requires std::derived_from<T, EditorUI>
	void AddChild()
	{
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
		}
		/*else if (m_target->GetRenderComponent() != nullptr)
		{
			throw std::logic_error("������ ������Ʈ�� �ϳ��� ���� �� �ֽ��ϴ�");
		}*/
		else
		{
			m_children.push_back(new T);
		}

		// �θ� ����
		m_children.back()->m_parent = this;
		
		// ImguiManager�� ���
		ImguiManager::GetInstance()->AddUI(*m_children.back());
	}


// about EditorUI functions called every frame
public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void RenderUpdate() = 0;
};