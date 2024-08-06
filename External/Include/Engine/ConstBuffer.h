#pragma once
#include "Entity.h"

// ��� ���� Ÿ��
enum class CB_TYPE : UINT
{
	TRANSFORM, COUNT_END
};

// ������Ʈ�� ��ġ,ũ��,ȸ���� �������
struct CB_Transform
{
	Vec4 pos;
};

// ��� ���� Ŭ����
class ConstBuffer final : public Entity
{
private:
	CB_TYPE type;
	ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

public:
	ConstBuffer(CB_TYPE type);
	~ConstBuffer();

public:
	void SetData(void* data, UINT dataSize = 0);

public:
	int Create(UINT bufferSize);
	void Bind();

// delete
private:
	ConstBuffer(const ConstBuffer&) = delete;
	ConstBuffer& operator=(const ConstBuffer&) = delete;
};