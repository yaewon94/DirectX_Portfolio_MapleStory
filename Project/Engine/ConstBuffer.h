#pragma once
#include "Entity.h"
#include "Render.h"

// ��� ���� Ŭ����
class ConstBuffer final : public Entity
{
	NO_COPY_ASSIGN(ConstBuffer);

private:
	const CB_TYPE Type;
	ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

public:
	ConstBuffer(const CB_TYPE Type);
	~ConstBuffer();

public:
	void SetData(void* data, UINT dataSize = 0);

public:
	int CreateOnGpu(UINT bufferSize);
	void BindOnGpu();
};