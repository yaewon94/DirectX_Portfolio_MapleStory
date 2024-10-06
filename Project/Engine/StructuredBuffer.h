#pragma once
#include "Entity.h"
#include "Render.h"

// ���� ConstBuffer�� ����(ũ�����, ũ������)�� �ذ�
// ConstBuffer ���ٴ� ������
class StructuredBuffer final : public Entity
{
	NO_COPY_ASSIGN(StructuredBuffer);

private:
	ComPtr<ID3D11Buffer> m_buffer;
	ComPtr<ID3D11ShaderResourceView> m_srv;
	D3D11_BUFFER_DESC m_desc;

	UINT m_elementCount;	// ��� ����
	UINT m_elementSize;		// ��Ҵ� ũ��

public:
	StructuredBuffer();
	~StructuredBuffer();

public:
	void SetData(void* sysMem, UINT elementCount);

public:
	int CreateOnGpu(UINT elementSize, UINT elementCount, void* sysMem = nullptr);
	void BindOnGpu(TEXTURE_PARAM registerNum);
};