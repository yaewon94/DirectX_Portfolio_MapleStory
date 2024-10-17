#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"
#include "Engine/GameObject.h"

// �����͸�� ��� UI���� �ֻ��� Ŭ���� (�߻�Ŭ����)
// TODO : ���ӿ�����Ʈ ���� ���
// TODO : ���ӿ�����Ʈ ���� �� TransformUI�� �ڵ����� �߰��ǵ��� ����
// TODO : �� EditorUI�� X ǥ�ø� ������ �ش� ������Ʈ ���� (TransformUI ����)
class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

// static members
private:
	static UINT nextID;

// about EditorUI
private:
	const UINT m_ID;
	bool m_isActive;
	// imgui ��ü�� �̸��� ������ �Ȱ��� ��ü�� ����Ѵ�
	// ## ���� ���ڿ��� ȭ�鿡 ��µ��� �ʴ´�
	// ex) box##1, box##2 �̷� ������ ���� �̸��� �ٸ���, ȭ�鿡 ��µǴ� �̸��� ���� �� �� �ִ�
	string m_name;

	EditorUI* m_parent;
	vector<EditorUI*> m_children;

// about GameObject
private:
	Ptr<GameObject> m_target;

// Constructor, Destructor
public:
	EditorUI(const Ptr<GameObject>& target);
	~EditorUI();

// [protected] Getter, Setter
protected:
	Ptr<GameObject> GetTarget() { return m_target; }

// [public] Getter, Setter
public:
	const string& GetName() { return m_name; }
	bool IsActive() { return m_isActive; }
	const EditorUI& GetParent() { return *m_parent; }
	
	template<typename T> requires std::derived_from<T, EditorUI>
	const EditorUI& GetChild()
	{
		for (EditorUI* child : m_children)
		{
			if (dynamic_cast<T*>(child) != nullptr)
			{
				return *child;
			}
		}

		throw std::logic_error("�ش� Ÿ���� UI�� �����ϴ�");
	}

	void SetName(const string& name) { m_name = name + "##" + std::to_string(m_ID); }
	void SetActive(bool isActive) { m_isActive = isActive; }
	template<typename T> requires std::derived_from<T, EditorUI>
	void AddChild()
	{
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("�̹� ������ �ִ� ������Ʈ �Դϴ�");
		}
		else if (m_target->GetRenderComponent() != nullptr)
		{
			throw std::logic_error("������ ������Ʈ�� �ϳ��� ���� �� �ֽ��ϴ�");
		}
		else
		{
			m_children.push_back(new T);
		}

		// �θ� ����
		m_children.back().m_parent = this;
		
		// ImguiManager�� ���
		ImguiManager::GetInstance()->AddUI(m_children.back());
	}


// about EditorUI functions called every frame
public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void RenderUpdate() = 0;
};