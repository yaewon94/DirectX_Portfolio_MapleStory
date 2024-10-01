#pragma once
#include "Entity.h"

// ���� ConstBuffer�� ����(ũ�����, ũ������)�� �ذ�
// ConstBuffer ���ٴ� ������
class StructedBuffer final : public Entity
{
	NO_COPY_ASSIGN(StructedBuffer);

private:
	ComPtr<ID3D11Buffer> m_buffer;
	ComPtr<ID3D11ShaderResourceView> m_srv;
	D3D11_BUFFER_DESC m_desc;

	UINT m_elementCount;	// ��� ����
	UINT m_elementSize;		// ��Ҵ� ũ��

public:
	StructedBuffer();
	~StructedBuffer();

public:
	void SetData(void* sysMem, UINT elementCount);

public:
	int CreateOnGpu(UINT elementSize, UINT elementCount, void* sysMem = nullptr);
	void BindOnGpu(UINT registerNum);
};