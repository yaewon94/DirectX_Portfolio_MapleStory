#pragma once
#include "Entity.h"

// ���� �ֻ��� Ŭ����
class Asset : public Entity
{
private:
	wstring key;
	wstring relativePath;

public:
	const wstring& GetKey() { return key; }
	
protected:
	Asset(const wstring& key, const wstring& relativePath);
	~Asset();

protected:	// ����
	Asset(const Asset&) = delete;
	virtual Asset* Clone() final { return nullptr; }
};