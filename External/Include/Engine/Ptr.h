#pragma once
//#include "Entity.h"

// ����Ʈ ������ ���ø�
/*
// ������� ��ȯ���� ���� �߻�
//template<typename T> requires std::derived_from<T, Entity>
*/
template<typename T>
class Ptr final
{
private:
	T* t;

public:
	T* const* GetAddressOf() const { return &t; }

public:
	// ��������� ȣ��
	Ptr DeepCopy()
	{
		if constexpr (std::is_copy_constructible_v<T>)
		{
			Ptr<T> clone = Ptr<T>(nullptr);
			clone.t = new T(*t);
			return clone;
		}

		throw std::logic_error("�ش� Ŭ������ ��������ڰ� ���ų� ������ �� �����ϴ�");
	}

public:
	// �ʱ�ȭ �뵵 ���븸��� or ����Ʈ ������ �ִ� ��ü ������ �� ȣ��
	Ptr() : t(nullptr)
	{
		if constexpr (std::is_abstract_v<T>) throw std::logic_error("�߻�Ŭ������ ��ü�� ������ �� �����ϴ�");
		
		if constexpr (std::is_constructible_v<T>) t = new T;
	}

	// @ param : ������ ��ü�� ������ �Ķ����
	template<typename... Args>
	Ptr(Args... args) : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T, Args...>) t = new T(args...);
		else throw std::logic_error("�ش� �Ķ���͸� ���� �����ڰ� �������� �ʰų� ������ �� �����ϴ�");
	}

	// args==nullptr�� Ptr(args...) ȣ�� ����
	Ptr(nullptr_t) : t(nullptr)
	{
	}

	// @ param : ������ ��ü
	Ptr(T* const t) : t(t)
	{
		if (t != nullptr) t->AddRefCount();
	}

	// ��������� (lValue)
	Ptr(const Ptr& origin) : t(nullptr)
	{
		*this = origin;
	}

	// ��������� (rValue)
	Ptr(Ptr&& origin) noexcept : t(nullptr)
	{
		*this = std::move(origin);
	}

	// �Ҹ���
	~Ptr()
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}
	}

public:
	// ���Կ����� (lValue)
	Ptr& operator=(const Ptr& other)
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		if (other.t != nullptr)
		{
			t = other.t;
			t->AddRefCount();
		}

		return *this;
	}

	// ���Կ����� (rValue)
	Ptr& operator=(Ptr&& other) noexcept
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		if (other.t != nullptr)
		{
			t = other.t;
			t->AddRefCount();

			other.t->Release();
			other.t = nullptr;
		}

		return *this;
	}

	// ���Կ����� (nullptr_t)
	nullptr_t operator=(nullptr_t)
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		return nullptr;
	}
		
	// �� ������ (==)
	bool operator==(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return true;
		else return false;
	}

	// �� ������ (!=)
	bool operator!=(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return false;
		else return true;
	}

	// ������ ���� ������
	T* const operator->() const
	{
		if (t == nullptr) throw std::logic_error(MSG_NULLPTR_EXCEPTION);
		return t;
	}

	// ����Ʈ������ ����ȯ
	template<typename U>
	Ptr<U> ptr_dynamic_cast() const
	{
		if (t == nullptr) return nullptr;
		else if (dynamic_cast<U*>(t) != nullptr) return Ptr<U>((U*)t);
		else return nullptr;
	}

public:
	// �����Ҵ�,���� ����
	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;

	// �ڵ� ����ȯ ����
	template<typename U>
	operator Ptr<U>() const = delete;
};